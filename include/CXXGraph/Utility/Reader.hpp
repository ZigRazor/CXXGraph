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

#ifndef __CXXGRAPH_READER_H__
#define __CXXGRAPH_READER_H__

#pragma once  // This is to make sure that this header is only included once

namespace CXXGraph {
/*!
    Interface to implement for a custom reader.
    */
template <typename T>
class Reader {
  /**
   * \brief
   * Function performs the writing of the Graph to the file.
   *
   * @param graph The graph to be filled.
   * @param file The input file to be read.
   * @returns a negative value if is impossible to read the graph from the file,
   * else 0 if the graph is read successfully.
   *
   */
  virtual int ReadGraph(Graph<T> &graph, std::ifstream &file) = 0;
};
}  // namespace CXXGraph

#endif  // __CXXGRAPH_READER_H__