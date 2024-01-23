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

#ifndef __CXXGRAPH_INPUTOPERATION_IMPL_H__
#define __CXXGRAPH_INPUTOPERATION_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
int Graph<T>::readFromFile(InputOutputFormat format,
                           const std::string &workingDir,
                           const std::string &OFileName, bool compress,
                           bool readNodeFeat, bool readEdgeWeight) {
  int result = 0;

#ifdef WITH_COMPRESSION
  if (compress) {
    auto decompress = [this, &workingDir, &OFileName, &readNodeFeat,
                       &readEdgeWeight](const std::string &extension) {
      std::string completePathToFileGraph =
          workingDir + "/" + OFileName + extension;
      std::string completePathToFileGraphCompressed =
          workingDir + "/" + OFileName + extension + ".gz";
      int _result = decompressFile(completePathToFileGraphCompressed,
                                   completePathToFileGraph);
      if (_result == 0) {
        if (readNodeFeat) {
          std::string completePathToFileNodeFeat =
              workingDir + "/" + OFileName + "_NodeFeat" + extension;
          std::string completePathToFileNodeFeatCompressed =
              workingDir + "/" + OFileName + "_NodeFeat" + extension + ".gz";
          _result = decompressFile(completePathToFileNodeFeatCompressed,
                                   completePathToFileNodeFeat);
        }
      }
      if (_result == 0) {
        if (readEdgeWeight) {
          std::string completePathToFileEdgeWeight =
              workingDir + "/" + OFileName + "_EdgeWeight" + extension;
          std::string completePathToFileEdgeWeightCompressed =
              workingDir + "/" + OFileName + "_EdgeWeight" + extension + ".gz";
          _result = decompressFile(completePathToFileEdgeWeightCompressed,
                                   completePathToFileEdgeWeight);
        }
      }
      return _result;
    };
    if (format == InputOutputFormat::STANDARD_CSV) {
      result = decompress(".csv");
    } else if (format == InputOutputFormat::STANDARD_TSV) {
      result = decompress(".tsv");
    } else {
      // INPUT FORMAT NOT RECOGNIZED
      result = -1;
    }

    if (result != 0) {
      return result;
    }
  }
#endif
  // Open streams and read
  auto extSep = getExtenstionAndSeparator(format);
  if (!extSep) {
    std::cerr << "Unknown format\n";
    return -1;
  }
  auto &[extension, separator] = *extSep;

  std::string completePathToFileGraph =
      workingDir + "/" + OFileName + extension;
  std::string completePathToFileNodeFeat;
  std::string completePathToFileEdgeWeight;

  std::ifstream ifileGraph;
  std::ifstream ifileNodeFeat;
  std::ifstream ifileEdgeWeight;

  ifileGraph.open(completePathToFileGraph);
  if (!ifileGraph.is_open()) {
    // ERROR File Not Open
    // std::cout << "ERROR File Not Open : " << completePathToFileGraph <<
    // std::endl;
    return -1;
  }
  ifileGraph.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));

  if (readNodeFeat) {
    completePathToFileNodeFeat =
        workingDir + "/" + OFileName + "_NodeFeat" + extension;
    ifileNodeFeat.open(completePathToFileNodeFeat);
    if (!ifileNodeFeat.is_open()) {
      // ERROR File Not Open
      // std::cout << "ERROR File Not Open" << std::endl;
      return -1;
    }
    ifileNodeFeat.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));
  }

  if (readEdgeWeight) {
    completePathToFileEdgeWeight =
        workingDir + "/" + OFileName + "_EdgeWeight" + extension;
    ifileEdgeWeight.open(completePathToFileEdgeWeight);
    if (!ifileEdgeWeight.is_open()) {
      // ERROR File Not Open
      // std::cout << "ERROR File Not Open" << std::endl;
      return -1;
    }
    ifileEdgeWeight.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));
  }

  readGraphFromStream(ifileGraph, ifileNodeFeat, ifileEdgeWeight, readNodeFeat,
                      readEdgeWeight);

  // Cleanup
  ifileGraph.close();
#ifdef WITH_COMPRESSION
  if (compress) remove(completePathToFileGraph.c_str());
#endif

  if (readNodeFeat) {
    ifileNodeFeat.close();
#ifdef WITH_COMPRESSION
    if (compress) remove(completePathToFileNodeFeat.c_str());
#endif
  }

  if (readEdgeWeight) {
    ifileEdgeWeight.close();
#ifdef WITH_COMPRESSION
    if (compress) remove(completePathToFileEdgeWeight.c_str());
#endif
  }

  return result;
}

template <typename T>
int Graph<T>::readFromDotFile(const std::string &workingDir,
                              const std::string &fileName) {
  return readFromDot(workingDir, fileName);
}

template <typename T>
int Graph<T>::readFromMTXFile(const std::string &workingDir,
                              const std::string &fileName) {
  // Define the edge maps
  std::unordered_map<CXXGraph::id_t, std::pair<std::string, std::string>>
      edgeMap;
  std::unordered_map<std::string, T> nodeFeatMap;
  std::unordered_map<CXXGraph::id_t, bool> edgeDirectedMap;
  std::unordered_map<CXXGraph::id_t, double> edgeWeightMap;

  // Get full path to the file and open it
  const std::string completePathToFileGraph =
      workingDir + '/' + fileName + ".mtx";
  std::ifstream iFile(completePathToFileGraph);
  // Check that the file is open
  if (!iFile.is_open()) {
    return -1;
  }

  // Define the number of columns and rows in the matrix
  int n_cols, n_rows;
  int n_edges;
  bool undirected = false;

  // From the first line of the file read the number of rows, columns and edges
  std::string row_content;
  getline(iFile, row_content);
  if (row_content.find("symmetric") != std::string::npos) {
    undirected = true;
  }

  // Get rid of any commented lines between the header and the size line
  while (row_content.find('%') != std::string::npos) {
    getline(iFile, row_content);
  }

  // From the size line of the file read the number of rows, columns and edges
  std::stringstream header_stream(row_content);
  std::string value;
  getline(header_stream, value, ' ');
  n_rows = std::stoi(value);
  getline(header_stream, value, ' ');
  n_cols = std::stoi(value);
  getline(header_stream, value, ' ');
  n_edges = std::stoi(value);

  // Since the matrix represents the adjacency matrix, it must be square
  if (n_rows != n_cols) {
    return -1;
  }

  // Read the content of each line
  std::string node1;
  std::string node2;
  std::string edge_weight;
  CXXGraph::id_t edge_id = 0;
  while (getline(iFile, row_content)) {
    std::stringstream row_stream(row_content);

    // Read the content of the node ids and the weight into strings
    getline(row_stream, node1, ' ');
    getline(row_stream, node2, ' ');
    getline(row_stream, edge_weight);

    edgeMap[edge_id] = std::pair<std::string, std::string>(node1, node2);
    edgeWeightMap[edge_id] = std::stod(edge_weight);
    edgeDirectedMap[edge_id] = !undirected;

    // If the edge is a self-link, it must be undirected
    if (node1 == node2) {
      edgeDirectedMap[edge_id] = false;
    }

    // Increase the edge id
    ++edge_id;
  }

  if (n_edges != edgeMap.size()) {
    std::cout << "Error: The number of edges does not match the value provided "
                 "in the size line.\n";
    return -1;
  }

  iFile.close();
  recreateGraph(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
  return 0;
}

template <typename T>
int Graph<T>::readFromDot(const std::string &workingDir,
                          const std::string &fileName) {
  // Define the edge maps
  std::unordered_map<CXXGraph::id_t, std::pair<std::string, std::string>>
      edgeMap;
  std::unordered_map<std::string, T> nodeFeatMap;
  std::unordered_map<CXXGraph::id_t, bool> edgeDirectedMap;
  std::unordered_map<CXXGraph::id_t, double> edgeWeightMap;

  // Define the node strings and the "garbage collector" temp string
  std::string node1;
  std::string node2;
  std::string temp;

  // Get full path to the file and open it
  const std::string completePathToFileGraph =
      workingDir + '/' + fileName + ".dot";

  // Check if the graph is directed
  bool directed = false;
  std::ifstream fileContentStream(completePathToFileGraph);
  std::string fileContent(std::istreambuf_iterator<char>{fileContentStream},
                          {});
  if (fileContent.find("->") != std::string::npos) {
    directed = true;
  }
  // Check if the graph is weighted
  bool weighted = false;
  if (fileContent.find("weight") != std::string::npos) {
    weighted = true;
  }
  fileContentStream.close();

  std::ifstream iFile(completePathToFileGraph);
  // Write the header of the DOT file in the temp string
  getline(iFile, temp);

  CXXGraph::id_t edgeId = 0;
  std::string fileRow;
  while (getline(iFile, fileRow)) {
    // If you've reached the end of the file, stop
    if (fileRow == "}") {
      break;
    }

    // Remove the whitespaces before the definition of the edge
    while (*fileRow.begin() == ' ' || *fileRow.begin() == '\t') {
      fileRow.erase(fileRow.begin());
    }

    std::stringstream row_stream(fileRow);
    getline(row_stream, node1, ' ');
    // Store the symbol representing the edge inside temp
    getline(row_stream, temp, ' ');
    if (weighted) {
      getline(row_stream, node2, '[');
      // Remove any whitespaces or tabs from the node string
      node2.erase(std::remove(node2.begin(), node2.end(), ' '), node2.end());
      node2.erase(std::remove(node2.begin(), node2.end(), '\t'), node2.end());

      getline(row_stream, temp, '=');
      std::string weight;
      getline(row_stream, weight, ']');
      // Erase any whitespaces
      weight.erase(std::remove(weight.begin(), weight.end(), ' '),
                   weight.end());
      edgeWeightMap[edgeId] = std::stod(weight);
    } else {
      getline(row_stream, node2, ';');
    }

    // Save the edge and increment the edge counter
    edgeMap[edgeId] = std::pair<std::string, std::string>(node1, node2);
    edgeDirectedMap[edgeId] = directed;
    ++edgeId;
  }
  iFile.close();

  recreateGraph(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
  return 0;
}

template <typename T>
void Graph<T>::readGraphFromStream(std::istream &iGraph,
                                   std::istream &iNodeFeat,
                                   std::istream &iEdgeWeight, bool readNodeFeat,
                                   bool readEdgeWeight) {
  std::unordered_map<CXXGraph::id_t, std::pair<std::string, std::string>>
      edgeMap;
  std::unordered_map<CXXGraph::id_t, bool> edgeDirectedMap;
  std::unordered_map<std::string, T> nodeFeatMap;
  std::unordered_map<CXXGraph::id_t, double> edgeWeightMap;

  CXXGraph::id_t edgeId;
  std::string nodeId1;
  std::string nodeId2;
  bool directed;
  while (iGraph >> edgeId >> nodeId1 >> nodeId2 >>
         directed) { /* loop continually */
    edgeMap[edgeId] = std::pair<std::string, std::string>(nodeId1, nodeId2);
    edgeDirectedMap[edgeId] = directed;
  }

  if (readNodeFeat) {
    std::string nodeId;
    T nodeFeat;
    while (iNodeFeat >> nodeId >> nodeFeat) {
      nodeFeatMap[nodeId] = nodeFeat;
    }
  }

  if (readEdgeWeight) {
    CXXGraph::id_t edgeId;
    double weight;
    bool weighted;
    while (iEdgeWeight >> edgeId >> weight >> weighted) { /* loop continually */
      if (weighted) {
        edgeWeightMap[edgeId] = weight;
      }
    }
  }

  recreateGraph(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
}

template <typename T>
void Graph<T>::recreateGraph(
    std::unordered_map<CXXGraph::id_t, std::pair<std::string, std::string>>
        &edgeMap,
    std::unordered_map<CXXGraph::id_t, bool> &edgeDirectedMap,
    std::unordered_map<std::string, T> &nodeFeatMap,
    std::unordered_map<CXXGraph::id_t, double> &edgeWeightMap) {
  std::unordered_map<std::string, shared<Node<T>>> nodeMap;
  for (const auto &edgeIt : edgeMap) {
    shared<Node<T>> node1(nullptr);
    shared<Node<T>> node2(nullptr);
    if (nodeMap.find(edgeIt.second.first) == nodeMap.end()) {
      // Create new Node
      T feat;
      if (nodeFeatMap.find(edgeIt.second.first) != nodeFeatMap.end()) {
        feat = std::move(nodeFeatMap.at(edgeIt.second.first));
      }
      node1 = make_shared<Node<T>>(edgeIt.second.first, feat);
      nodeMap[edgeIt.second.first] = node1;
    } else {
      node1 = nodeMap.at(edgeIt.second.first);
    }
    if (nodeMap.find(edgeIt.second.second) == nodeMap.end()) {
      // Create new Node
      T feat;
      if (nodeFeatMap.find(edgeIt.second.second) != nodeFeatMap.end()) {
        feat = std::move(nodeFeatMap.at(edgeIt.second.second));
      }
      node2 = make_shared<Node<T>>(edgeIt.second.second, feat);
      nodeMap[edgeIt.second.second] = node2;
    } else {
      node2 = nodeMap.at(edgeIt.second.second);
    }

    if (edgeWeightMap.find(edgeIt.first) != edgeWeightMap.end()) {
      if (edgeDirectedMap.find(edgeIt.first) != edgeDirectedMap.end() &&
          edgeDirectedMap.at(edgeIt.first)) {
        auto edge = make_shared<DirectedWeightedEdge<T>>(
            edgeIt.first, node1, node2, edgeWeightMap.at(edgeIt.first));
        addEdge(edge);
      } else {
        auto edge = make_shared<UndirectedWeightedEdge<T>>(
            edgeIt.first, node1, node2, edgeWeightMap.at(edgeIt.first));
        addEdge(edge);
      }
    } else {
      if (edgeDirectedMap.find(edgeIt.first) != edgeDirectedMap.end() &&
          edgeDirectedMap.at(edgeIt.first)) {
        auto edge = make_shared<DirectedEdge<T>>(edgeIt.first, node1, node2);
        addEdge(edge);
      } else {
        auto edge = make_shared<UndirectedEdge<T>>(edgeIt.first, node1, node2);
        addEdge(edge);
      }
    }
  }
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_INPUTOPERATION_IMPL_H__