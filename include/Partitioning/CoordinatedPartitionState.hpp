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
/***     Author: ZigRazor			     			     ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0							     ***/
/***********************************************************/

#ifndef __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__
#define __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__

#pragma once

#include "Record.hpp"
#include "Edge/Edge.hpp"
#include "Partitioning/Utility/Globals.hpp"
#include "PartitionState.hpp"
#include "CoordinatedRecord.hpp"
#include <memory>
#include <mutex>
#include <vector>
#include <set>

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
        class CoordinatedPartitionState : public PartitionState<T>
        {
        private:
            std::map<int, CoordinatedRecord<T> *> record_map;
            std::vector<int> machines_load_edges;
            std::vector<int> machines_load_vertices;
            PartitionMap<T> partition_map;
            Globals GLOBALS;
            int MAX_LOAD;
            std::shared_ptr<std::mutex> machines_load_edges_mutex = nullptr;
            std::shared_ptr<std::mutex> machines_load_vertices_mutex = nullptr;
            std::shared_ptr<std::mutex> record_map_mutex = nullptr;
            //DatWriter out; //to print the final partition of each edge
        public:
            CoordinatedPartitionState(Globals &G);
            ~CoordinatedPartitionState();

            Record<T> *getRecord(int x);
            int getMachineLoad(int m);
            int getMachineLoadVertices(int m);
            void incrementMachineLoad(int m, const Edge<T> *e);
            int getMinLoad();
            int getMaxLoad();
            std::vector<int> getMachines_load();
            int getTotalReplicas();
            int getNumVertices();
            std::set<int> getVertexIds();

            void incrementMachineLoadVertices(int m);
            std::vector<int> getMachines_loadVertices();
            const PartitionMap<T> &getPartitionMap();
        };
        template <typename T>
        CoordinatedPartitionState<T>::CoordinatedPartitionState(Globals &G) : record_map(), GLOBALS(G), machines_load_edges_mutex(std::make_shared<std::mutex>()), machines_load_vertices_mutex(std::make_shared<std::mutex>()), record_map_mutex(std::make_shared<std::mutex>())
        {
            for (int i = 0; i < GLOBALS.numberOfPartition; ++i)
            {
                machines_load_edges.push_back(0);
                machines_load_vertices.push_back(0);
                partition_map[i] = new PARTITIONING::Partition<T>(i);
            }
            MAX_LOAD = 0;
        }
        template <typename T>
        CoordinatedPartitionState<T>::~CoordinatedPartitionState()
        {
        }
        template <typename T>
        Record<T> *CoordinatedPartitionState<T>::getRecord(int x)
        {
            std::lock_guard<std::mutex> lock(*record_map_mutex);
            if (record_map.find(x) == record_map.end())
            {
                record_map[x] = new CoordinatedRecord<T>();
            }
            return record_map.at(x);
        }

        template <typename T>
        int CoordinatedPartitionState<T>::getMachineLoad(int m)
        {
            std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
            return machines_load_edges.at(m);
        }

        template <typename T>
        int CoordinatedPartitionState<T>::getMachineLoadVertices(int m)
        {
            std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
            return machines_load_vertices.at(m);
        }
        template <typename T>
        void CoordinatedPartitionState<T>::incrementMachineLoad(int m, const Edge<T> *e)
        {
            std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
            machines_load_edges[m] = machines_load_edges[m] + 1;
            int new_value = machines_load_edges.at(m);
            if (new_value > MAX_LOAD)
            {
                MAX_LOAD = new_value;
            }
            partition_map[m]->addEdge(e);
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getMinLoad()
        {
            std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
            int MIN_LOAD = std::numeric_limits<int>::max();
            for (const auto &machines_load_edges_it : machines_load_edges)
            {
                int loadi = machines_load_edges_it;
                if (loadi < MIN_LOAD)
                {
                    MIN_LOAD = loadi;
                }
            }
            return MIN_LOAD;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getMaxLoad()
        {
            return MAX_LOAD;
        }
        template <typename T>
        std::vector<int> CoordinatedPartitionState<T>::getMachines_load()
        {
            std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
            std::vector<int> result;
            for (const auto &machines_load_edges_it : machines_load_edges)
            {
                result.push_back(machines_load_edges_it);
            }
            return result;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getTotalReplicas()
        {
            //TODO
            std::lock_guard<std::mutex> lock(*record_map_mutex);
            int result = 0;
            for (const auto &record_map_it : record_map)
            {
                int r = record_map_it.second->getReplicas();
                if (r > 0)
                {
                    result += r;
                }
                else
                {
                    result++;
                }
            }
            return result;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getNumVertices()
        {
            std::lock_guard<std::mutex> lock(*record_map_mutex);
            return record_map.size();
        }
        template <typename T>
        std::set<int> CoordinatedPartitionState<T>::getVertexIds()
        {
            std::lock_guard<std::mutex> lock(*record_map_mutex);
            //if (GLOBALS.OUTPUT_FILE_NAME!=null){ out.close(); }
            std::set<int> result;
            for (const auto &record_map_it : record_map)
            {
                result.insert(record_map_it.first);
            }
            return result;
        }
        template <typename T>
        void CoordinatedPartitionState<T>::incrementMachineLoadVertices(int m)
        {
            std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
            machines_load_vertices[m] = machines_load_vertices[m] + 1;
        }
        template <typename T>
        std::vector<int> CoordinatedPartitionState<T>::getMachines_loadVertices()
        {
            std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
            std::vector<int> result;
            for (const auto &machines_load_vertices_it : machines_load_vertices)
            {
                result.push_back(machines_load_vertices_it);
            }
            return result;
        }

        template <typename T>
        const PartitionMap<T> &CoordinatedPartitionState<T>::getPartitionMap()
        {
            return partition_map;
        }
    }
}

#endif // __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__