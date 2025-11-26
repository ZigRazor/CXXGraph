/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: MPL v2.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_BESTFIRSTSEARCH_IMPL_H__
#define __CXXGRAPH_BESTFIRSTSEARCH_IMPL_H__

#pragma once

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include "CXXGraph/Graph/Graph_decl.h"
#include "CXXGraph/Utility/ConstString.hpp"

namespace CXXGraph {
template <typename T>
BestFirstSearchResult<T> Graph<T>::best_first_search(
    const Node<T> &source, const Node<T> &target) const {
  BestFirstSearchResult<T> result;
  auto &nodeSet = Graph<T>::getNodeSet();
  using pq_type = std::pair<double, shared<const Node<T>>>;

  auto source_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&source](auto node) { return node->getUserId() == source.getUserId(); });
  if (source_node_it == nodeSet.end()) {
    result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
    return result;
  }

  auto target_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&target](auto node) { return node->getUserId() == target.getUserId(); });
  if (target_node_it == nodeSet.end()) {
    result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
    return result;
  }

  std::priority_queue<pq_type, std::vector<pq_type>, std::greater<pq_type>> pq;

  std::vector<Node<T>> visited;
  visited.push_back(source);
  pq.push(std::make_pair(0.0, *source_node_it));

  while (!pq.empty()) {
    shared<const Node<T>> currentNode = pq.top().second;
    pq.pop();
    result.nodesInBestSearchOrder.push_back(*currentNode);

    if (*currentNode == target) {
      break;
    }
    if (cachedAdjListOut->find(currentNode) != cachedAdjListOut->end()) {
      for (const auto &elem : cachedAdjListOut->at(currentNode)) {
        if (elem.second->isWeighted().has_value()) {
          if (elem.second->isDirected().has_value()) {
            shared<const DirectedWeightedEdge<T>> dw_edge =
                std::static_pointer_cast<const DirectedWeightedEdge<T>>(
                    elem.second);
            if (std::find(visited.begin(), visited.end(), *(elem.first)) ==
                visited.end()) {
              visited.push_back(*(elem.first));
              pq.push(std::make_pair(dw_edge->getWeight(), elem.first));
            }
          } else {
            shared<const UndirectedWeightedEdge<T>> dw_edge =
                std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                    elem.second);
            if (std::find(visited.begin(), visited.end(), *(elem.first)) ==
                visited.end()) {
              visited.push_back(*(elem.first));
              pq.push(std::make_pair(dw_edge->getWeight(), elem.first));
            }
          }
        } else {
          result.errorMessage = ERR_NO_WEIGHTED_EDGE;
          result.nodesInBestSearchOrder.clear();
          return result;
        }
      }
    }
  }

  result.success = true;
  return result;
}

template <typename T>
const std::vector<Node<T>> Graph<T>::concurrency_breadth_first_search(
    const Node<T> &start, size_t num_threads) const {
  std::vector<Node<T>> bfs_result;
  // check is exist node in the graph
  auto &nodeSet = Graph<T>::getNodeSet();
  auto start_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&start](auto node) { return node->getUserId() == start.getUserId(); });
  if (start_node_it == nodeSet.end()) {
    return bfs_result;
  }

  std::unordered_map<shared<const Node<T>>, size_t, nodeHash<T>> node_to_index;
  for (const auto &node : nodeSet) {
    node_to_index[node] = node_to_index.size();
  }
  std::vector<size_t> visited(nodeSet.size(), 0);

  // parameter limitations
  if (num_threads <= 0) {
    std::cout << "Error: number of threads should be greater than 0"
              << std::endl;
    num_threads = 2;
  }

  // vector that stores vertices to be visit
  std::vector<shared<const Node<T>>> level_tracker, next_level_tracker;
  level_tracker.reserve(static_cast<int>(1.0 * nodeSet.size()));
  next_level_tracker.reserve(static_cast<int>(1.0 * nodeSet.size()));

  // mark the starting node as visited
  visited[node_to_index[*start_node_it]] = 1;
  level_tracker.push_back(*start_node_it);

  // a worker is assigned a small part of tasks for each time
  // assignments of tasks in current level and updates of tasks in next
  // level are inclusive
  std::mutex tracker_mutex;
  std::mutex next_tracker_mutex;
  std::atomic<int> assigned_tasks = 0;
  int num_tasks = 1;
  // unit of task assignment, which mean assign block_size tasks to a
  // worker each time
  int block_size = 1;
  int level = 1;

  auto extract_tasks = [&assigned_tasks, &num_tasks,
                        &block_size]() -> std::pair<int, int> {
    /*
    std::lock_guard<std::mutex> tracker_guard(tracker_mutex);
    int task_block_size = std::min(num_tasks - assigned_tasks,
    block_size); std::pair<int,int> task_block{assigned_tasks,
    assigned_tasks + task_block_size}; assigned_tasks += task_block_size;
    return task_block;
    */
    int start = assigned_tasks.fetch_add(block_size);
    int end = std::min(num_tasks, start + block_size);
    return {start, end};
  };

  auto submit_result =
      [&next_level_tracker, &next_tracker_mutex](
          std::vector<shared<const Node<T>>> &submission) -> void {
    std::lock_guard<std::mutex> tracker_guard(next_tracker_mutex);
    next_level_tracker.insert(std::end(next_level_tracker),
                              std::begin(submission), std::end(submission));
  };

  // worker thread sleep until it begin to search nodes of next level
  std::mutex next_level_mutex;
  std::condition_variable next_level_cond;
  std::atomic<int> waiting_workers = 0;

  auto bfs_worker = [&]() -> void {
    // algorithm is not done
    while (!level_tracker.empty()) {
      // search for nodes in a level is not done
      std::vector<shared<const Node<T>>> local_tracker;
      while (true) {
        auto [start_index, end_index] = extract_tasks();
        if (start_index >= end_index) {
          break;
        }

        for (int i = start_index; i < end_index; ++i) {
          if (cachedAdjListOut->count(level_tracker[i])) {
            for (const auto &elem : cachedAdjListOut->at(level_tracker[i])) {
              int index = (int)node_to_index[elem.first];
              if (visited[index] == 0) {
                visited[index] = 1;
                local_tracker.push_back(elem.first);
              }
            }
          }
        }
      }

      // submit local result to global result
      if (!local_tracker.empty()) {
        submit_result(local_tracker);
      }

      // last worker need to do preparation for the next iteration
      int cur_level = level;
      if (num_threads == 1u + waiting_workers.fetch_add(1u)) {
        swap(level_tracker, next_level_tracker);
        next_level_tracker.clear();

        // adjust block_size according to number of nodes in next level
        block_size = 4;
        if (level_tracker.size() <= num_threads * 4) {
          block_size = std::max(
              1, static_cast<int>(std::ceil(
                     static_cast<double>(level_tracker.size()) / num_threads)));
        } else if (level_tracker.size() >= num_threads * 64) {
          block_size = 16;
        }

        num_tasks = (int)level_tracker.size();
        waiting_workers = 0;
        assigned_tasks = 0;
        level = level + 1;
        next_level_cond.notify_all();
      } else {
        // not to wait if last worker reachs last statement before notify
        // all or even further
        std::unique_lock<std::mutex> next_level_lock(next_level_mutex);
        next_level_cond.wait(next_level_lock, [&level, cur_level]() {
          return level != cur_level;
        });
      }
    }
  };

  std::vector<std::thread> workers;
  for (size_t i = 0; i < num_threads - 1; ++i) {
    workers.emplace_back(std::thread(bfs_worker));
  }
  bfs_worker();

  for (auto &worker : workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }

  for (const auto &visited_node : nodeSet) {
    if (visited[node_to_index[visited_node]] != 0) {
      bfs_result.push_back(*visited_node);
    }
  }

  return bfs_result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_BESTFIRSTSEARCH_IMPL_H__
