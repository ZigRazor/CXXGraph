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
/***	 License: AGPL v3.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__
#define __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__

#pragma once

#include <set>

#include "Record.hpp"
#include "Utility/Typedef.hpp"

namespace CXXGraph {
namespace Partitioning {

template <typename T>
class CoordinatedRecord : public Record<T> {
 private:
  std::set<int> partitions = {};
  std::mutex *lock = nullptr;
  int degree = 0;

 public:
  CoordinatedRecord();
  ~CoordinatedRecord();

  const std::set<int> &getPartitions() const override;
  void addPartition(const int m) override;
  bool hasReplicaInPartition(const int m) const override;
  bool getLock() override;
  bool releaseLock() override;
  int getReplicas() const override;
  int getDegree() const override;
  void incrementDegree() override;

  void addAll(const std::set<int> &set);
  std::set<int> partition_intersection(
      const std::shared_ptr<CoordinatedRecord> other) const;
  std::set<int> partition_union(
      const std::shared_ptr<CoordinatedRecord> other) const;
  std::set<int> partition_difference(
      const std::shared_ptr<CoordinatedRecord> other) const;
};
template <typename T>
std::set<int> CoordinatedRecord<T>::partition_intersection(
    std::shared_ptr<CoordinatedRecord> other) const {
  std::set<int> result;
  set_intersection(this->partitions.begin(), this->partitions.end(),
                   other->partitions.begin(), other->partitions.end(),
                   std::inserter(result, result.begin()));
  return result;
}
template <typename T>
std::set<int> CoordinatedRecord<T>::partition_union(
    std::shared_ptr<CoordinatedRecord> other) const {
  std::set<int> result;
  set_union(this->partitions.begin(), this->partitions.end(),
            other->partitions.begin(), other->partitions.end(),
            std::inserter(result, result.begin()));
  return result;
}
template <typename T>
std::set<int> CoordinatedRecord<T>::partition_difference(
    std::shared_ptr<CoordinatedRecord> other) const {
  std::set<int> result;
  set_difference(this->partitions.begin(), this->partitions.end(),
                 other->partitions.begin(), other->partitions.end(),
                 std::inserter(result, result.begin()));
  return result;
}
template <typename T>
CoordinatedRecord<T>::CoordinatedRecord() : partitions() {
  lock = new std::mutex();
  degree = 0;
}
template <typename T>
CoordinatedRecord<T>::~CoordinatedRecord() {
  // std::cout << "CoordinatedRecord<T>::~CoordinatedRecord()" << std::endl;
  // TODOOOOOOOO
  if (lock != nullptr) {
    delete lock;
  }
}
template <typename T>
const std::set<int> &CoordinatedRecord<T>::getPartitions() const {
  return partitions;
}
template <typename T>
void CoordinatedRecord<T>::addPartition(int m) {
  if (m == -1) {
    std::cout << "ERROR! record.addPartition(-1)" << std::endl;
    exit(-1);
  }
  partitions.insert(m);
}
template <typename T>
bool CoordinatedRecord<T>::hasReplicaInPartition(const int m) const {
  return partitions.find(m) != partitions.end();
}
template <typename T>
bool CoordinatedRecord<T>::getLock() {
  return lock->try_lock();
}
template <typename T>
bool CoordinatedRecord<T>::releaseLock() {
  lock->unlock();
  return true;
}
template <typename T>
int CoordinatedRecord<T>::getReplicas() const {
  return (int)partitions.size();
}
template <typename T>
int CoordinatedRecord<T>::getDegree() const {
  return degree;
}
template <typename T>
void CoordinatedRecord<T>::incrementDegree() {
  degree++;
}
template <typename T>
void CoordinatedRecord<T>::addAll(const std::set<int> &set) {
  partitions.insert(set.begin(), set.end());
}
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__