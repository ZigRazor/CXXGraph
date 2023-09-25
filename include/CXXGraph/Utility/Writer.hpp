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

#ifndef __CXXGRAPH_WRITER_H__
#define __CXXGRAPH_WRITER_H__

#pragma once  // This is to make sure that this header is only included once

namespace CXXGraph {

template <typename T>
class Graph;

/*!
    Interface to implement for a custom writer.
    */

template <typename T>
class Writer {
 public:
  /**
   * \brief
   * Function performs the writing of the Graph to the file.
   *
   * @param graph The graph to be written.
   * @param file The output file to be written.
   * @returns a negative value if is impossible to write the graph from the
   * file, else 0 if the graph is write successfully.
   *
   */
  virtual int writeGraph(const Graph<T> &graph, std::ofstream &file) = 0;
};
}  // namespace CXXGraph

#endif  // __CXXGRAPH_WRITER_H__