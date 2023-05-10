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

#ifndef __CXXGRAPH_THREADSAFE_H__
#define __CXXGRAPH_THREADSAFE_H__

#pragma once

#include <mutex>

namespace CXXGraph {
class ThreadSafe {
 public:
  void getLock() const;
  void releaseLock() const;

 protected:
  mutable std::mutex mutex;
};
// inline because the implementation of non-template function in header file
inline void ThreadSafe::getLock() const { mutex.lock(); }
// inline because the implementation of non-template function in header file
inline void ThreadSafe::releaseLock() const { mutex.unlock(); }
}  // namespace CXXGraph

#endif  // __CXXGRAPH_THREADSAFE_H__