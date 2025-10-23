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

#ifndef __CXXGRAPH_OUTPUTOPERATION_IMPL_H__
#define __CXXGRAPH_OUTPUTOPERATION_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
int Graph<T>::writeToFile(InputOutputFormat format,
                          const std::string &workingDir,
                          const std::string &OFileName, bool compress,
                          bool writeNodeFeat, bool writeEdgeWeight) const {
  int result = 0;

  // Open streams and write
  auto extSep = getExtenstionAndSeparator(format);
  if (!extSep) {
    std::cerr << "Unknown format\n";
    return -1;
  }
  auto &[extension, separator] = *extSep;

  std::ofstream ofileGraph;
  std::ofstream ofileNodeFeat;
  std::ofstream ofileEdgeWeight;

  std::string completePathToFileGraph =
      workingDir + "/" + OFileName + extension;
  ofileGraph.open(completePathToFileGraph);
  if (!ofileGraph.is_open()) {
    // ERROR File Not Open
    return -1;
  }

  if (writeNodeFeat) {
    std::string completePathToFileNodeFeat =
        workingDir + "/" + OFileName + "_NodeFeat" + extension;
    ofileNodeFeat.open(completePathToFileNodeFeat);
    if (!ofileNodeFeat.is_open()) {
      // ERROR File Not Open
      return -1;
    }
  }

  if (writeEdgeWeight) {
    std::string completePathToFileEdgeWeight =
        workingDir + "/" + OFileName + "_EdgeWeight" + extension;
    ofileEdgeWeight.open(completePathToFileEdgeWeight);
    if (!ofileEdgeWeight.is_open()) {
      // ERROR File Not Open
      std::cout << "ERROR File Not Open" << std::endl;
      return -1;
    }
  }

  writeGraphToStream(ofileGraph, ofileNodeFeat, ofileEdgeWeight, separator,
                     writeNodeFeat, writeEdgeWeight);

  // Cleanup from writing
  ofileGraph.close();
  if (writeNodeFeat) ofileNodeFeat.close();
  if (writeEdgeWeight) ofileEdgeWeight.close();

#ifdef WITH_COMPRESSION
  if (result == 0 && compress) {
    auto _compress = [this, &workingDir, &OFileName, &writeNodeFeat,
                      &writeEdgeWeight](const std::string &extension) {
      std::string completePathToFileGraph =
          workingDir + "/" + OFileName + extension;
      std::string completePathToFileGraphCompressed =
          workingDir + "/" + OFileName + extension + ".gz";
      int _result = compressFile(completePathToFileGraph,
                                 completePathToFileGraphCompressed);
      if (_result > 0) {
        _result = remove(completePathToFileGraph.c_str());
      }
      if (_result == 0) {
        if (writeNodeFeat) {
          std::string completePathToFileNodeFeat =
              workingDir + "/" + OFileName + "_NodeFeat" + extension;
          std::string completePathToFileNodeFeatCompressed =
              workingDir + "/" + OFileName + "_NodeFeat" + extension + ".gz";
          _result = compressFile(completePathToFileNodeFeat,
                                 completePathToFileNodeFeatCompressed);
          if (_result > 0) {
            _result = remove(completePathToFileNodeFeat.c_str());
          }
        }
      }
      if (_result == 0) {
        if (writeEdgeWeight) {
          std::string completePathToFileEdgeWeight =
              workingDir + "/" + OFileName + "_EdgeWeight" + extension;
          std::string completePathToFileEdgeWeightCompressed =
              workingDir + "/" + OFileName + "_EdgeWeight" + extension + ".gz";
          _result = compressFile(completePathToFileEdgeWeight,
                                 completePathToFileEdgeWeightCompressed);
          if (_result > 0) {
            _result = remove(completePathToFileEdgeWeight.c_str());
          }
        }
      }
      return _result;
    };
    if (format == InputOutputFormat::STANDARD_CSV) {
      result = _compress(".csv");
    } else if (format == InputOutputFormat::STANDARD_TSV) {
      result = _compress(".tsv");
    } else {
      // OUTPUT FORMAT NOT RECOGNIZED
      result = -1;
    }
  }
#endif

  return result;
}

template <typename T>
int Graph<T>::writeToDotFile(const std::string &workingDir,
                             const std::string &OFileName,
                             const std::string &graphName) const {
  return writeToDot(workingDir, OFileName, graphName);
}

template <typename T>
int Graph<T>::writeToMTXFile(const std::string &workingDir,
                             const std::string &OFileName,
                             char delimitier) const {
  // Get the full path and open the file
  const std::string completePathToFileGraph =
      workingDir + '/' + OFileName + ".mtx";
  std::ofstream iFile(completePathToFileGraph);

  // Write the header of the file
  std::string header = "%%MatrixMarket graph";
  // Check if the adjacency matrix is symmetric, i.e., if all the edges are
  // undirected
  bool symmetric = !std::any_of(edgeSet.begin(), edgeSet.end(), [](auto edge) {
    return (edge->isDirected().has_value() && edge->isDirected().value());
  });
  // Write in the header whether the adj matrix is symmetric or not
  if (symmetric) {
    header += " symmetric\n";
  } else {
    header += '\n';
  }
  iFile << header;

  // Write the line containing the number of nodes and edges
  const std::string firstLine =
      std::to_string(getNodeSet().size()) + delimitier +
      std::to_string(getNodeSet().size()) + delimitier +
      std::to_string(getEdgeSet().size()) + '\n';
  iFile << firstLine;

  // Construct the edges
  for (const auto &edgeIt : edgeSet) {
    std::string line;
    line += edgeIt->getNodePair().first->getUserId() + delimitier;
    line += edgeIt->getNodePair().second->getUserId() + delimitier;
    if (edgeIt->isWeighted().has_value() && edgeIt->isWeighted().value()) {
      line += std::to_string(edgeIt->isWeighted().value()) + '\n';
    } else {
      line += std::to_string(1.) + '\n';
    }
    iFile << line;
  }

  iFile.close();
  return 0;
}

template <typename T>
int Graph<T>::writeToBinaryFile(const std::string &workingDir,
                                const std::string &fileName,
                                bool writeNodeFeatures,
                                bool writeEdgeWeights) const {
  std::string filepath = workingDir + "/" + fileName + ".bin";
  return writeToBinary(filepath, writeNodeFeatures, writeEdgeWeights);
}

template <typename T>
int Graph<T>::writeToBinary(const std::string &filepath, bool writeNodeFeatures,
                            bool writeEdgeWeights) const {
  std::ofstream out(filepath, std::ios::binary);
  if (!out.is_open()) {
    return -1;
  }

  try {
    // Write header
    out.write(reinterpret_cast<const char *>(&BINARY_MAGIC_NUMBER),
              sizeof(BINARY_MAGIC_NUMBER));
    out.write(reinterpret_cast<const char *>(&BINARY_VERSION),
              sizeof(BINARY_VERSION));

    auto nodeSet = this->getNodeSet();
    auto edgeSet = this->getEdgeSet();

    uint64_t numNodes = nodeSet.size();
    uint64_t numEdges = edgeSet.size();
    uint64_t flags = 0;

    if (writeNodeFeatures) flags |= BINARY_FLAG_HAS_NODE_FEATURES;
    if (writeEdgeWeights) flags |= BINARY_FLAG_HAS_EDGE_WEIGHTS;

    out.write(reinterpret_cast<const char *>(&numNodes), sizeof(numNodes));
    out.write(reinterpret_cast<const char *>(&numEdges), sizeof(numEdges));
    out.write(reinterpret_cast<const char *>(&flags), sizeof(flags));

    // Write nodes
    for (const auto &node : nodeSet) {
      writeBinaryString(out, node->getUserId());

      if (writeNodeFeatures) {
        // For trivially copyable types, write directly
        if constexpr (is_binary_serializable<T>::value) {
          uint32_t dataSize = sizeof(T);
          out.write(reinterpret_cast<const char *>(&dataSize),
                    sizeof(dataSize));
          const T &data = node->getData();
          out.write(reinterpret_cast<const char *>(&data), sizeof(T));
        } else {
          // For non-trivially copyable types, write 0 size
          uint32_t dataSize = 0;
          out.write(reinterpret_cast<const char *>(&dataSize),
                    sizeof(dataSize));
        }
      } else {
        uint32_t dataSize = 0;
        out.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
      }
    }

    // Write edges
    for (const auto &edge : edgeSet) {
      writeBinaryString(out, edge->getUserId());
      writeBinaryString(out, edge->getNodePair().first->getUserId());
      writeBinaryString(out, edge->getNodePair().second->getUserId());

      uint8_t edgeFlags = 0;
      if (edge->isDirected().has_value() && edge->isDirected().value()) {
        edgeFlags |= 0x01;
      }
      if (edge->isWeighted().has_value() && edge->isWeighted().value()) {
        edgeFlags |= 0x02;
      }
      out.write(reinterpret_cast<const char *>(&edgeFlags), sizeof(edgeFlags));

      // Write weight if edge is weighted and we're saving weights
      if (writeEdgeWeights && (edgeFlags & 0x02)) {
        double weight =
            std::dynamic_pointer_cast<const Weighted>(edge)->getWeight();
        out.write(reinterpret_cast<const char *>(&weight), sizeof(weight));
      }
    }

    out.close();
    return 0;

  } catch (const std::exception &e) {
    out.close();
    return -2;
  }
}

template <typename T>
int Graph<T>::writeToDot(const std::string &workingDir,
                         const std::string &OFileName,
                         const std::string &graphName) const {
  const std::string linkSymbol = "--";
  const std::string directedLinkSymbol = "->";

  const std::string completePathToFileGraph =
      workingDir + '/' + OFileName + ".dot";
  std::ofstream ofileGraph;
  ofileGraph.open(completePathToFileGraph);
  if (!ofileGraph.is_open()) {
    // ERROR File Not Open
    return -1;
  }

  // Write the header of the DOT file
  std::string headerLine;
  if (this->isDirectedGraph()) {
    headerLine = "digraph " + graphName + " {\n";
  } else {
    headerLine = "graph " + graphName + " {\n";
  }
  ofileGraph << headerLine;

  for (auto const &edgePtr : edgeSet) {
    std::string edgeLine = "";
    if (edgePtr->isDirected().has_value() && edgePtr->isDirected().value()) {
      auto directedPtr =
          std::static_pointer_cast<const DirectedEdge<T>>(edgePtr);
      edgeLine += '\t' + directedPtr->getFrom().getUserId() + ' ';
      edgeLine += directedLinkSymbol + ' ';
      edgeLine += directedPtr->getTo().getUserId();
    } else {
      edgeLine += '\t' + edgePtr->getNodePair().first->getUserId() + ' ';
      edgeLine += linkSymbol + ' ';
      edgeLine += edgePtr->getNodePair().second->getUserId();
    }
    if (edgePtr->isWeighted().has_value() && edgePtr->isWeighted().value()) {
      // Weights in dot files must be integers
      edgeLine += " [weight=" +
                  std::to_string(static_cast<int>(
                      std::dynamic_pointer_cast<const Weighted>(edgePtr)
                          ->getWeight())) +
                  ']';
    }
    edgeLine += ";\n";
    ofileGraph << edgeLine;
  }
  ofileGraph << '}';
  ofileGraph.close();

  return 0;
}

template <typename T>
void Graph<T>::writeGraphToStream(std::ostream &oGraph, std::ostream &oNodeFeat,
                                  std::ostream &oEdgeWeight, const char &sep,
                                  bool writeNodeFeat,
                                  bool writeEdgeWeight) const {
  for (const auto &edge : edgeSet) {
    oGraph << edge->getUserId() << sep << edge->getNodePair().first->getUserId()
           << sep << edge->getNodePair().second->getUserId() << sep
           << ((edge->isDirected().has_value() && edge->isDirected().value())
                   ? 1
                   : 0)
           << std::endl;
  }

  if (writeNodeFeat) {
    auto nodeSet = getNodeSet();
    for (const auto &node : nodeSet) {
      oNodeFeat << node->getUserId() << sep << node->getData() << std::endl;
    }
  }

  if (writeEdgeWeight) {
    for (const auto &edge : edgeSet) {
      oEdgeWeight
          << edge->getUserId() << sep
          << (edge->isWeighted().has_value() && edge->isWeighted().value()
                  ? (std::dynamic_pointer_cast<const Weighted>(edge))
                        ->getWeight()
                  : 0.0)
          << sep
          << (edge->isWeighted().has_value() && edge->isWeighted().value() ? 1
                                                                           : 0)
          << std::endl;
    }
  }
}

// Helper function to write string with length prefix
template <typename T>
void Graph<T>::writeBinaryString(std::ofstream &out,
                                 const std::string &str) const {
  uint32_t len = static_cast<uint32_t>(str.length());
  out.write(reinterpret_cast<const char *>(&len), sizeof(len));
  out.write(str.c_str(), len);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
  os << "Graph:\n";
  auto edgeList = graph.getEdgeSet();
  for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
    if (!(*it)->isDirected().has_value() && !(*it)->isWeighted().has_value()) {
      // Edge Case
      os << **it << "\n";
    } else if (((*it)->isDirected().has_value() &&
                (*it)->isDirected().value()) &&
               ((*it)->isWeighted().has_value() &&
                (*it)->isWeighted().value())) {
      os << *std::static_pointer_cast<const DirectedWeightedEdge<T>>(*it)
         << "\n";
    } else if (((*it)->isDirected().has_value() &&
                (*it)->isDirected().value()) &&
               !((*it)->isWeighted().has_value() &&
                 (*it)->isWeighted().value())) {
      os << *std::static_pointer_cast<const DirectedEdge<T>>(*it) << "\n";
    } else if (!((*it)->isDirected().has_value() &&
                 (*it)->isDirected().value()) &&
               ((*it)->isWeighted().has_value() &&
                (*it)->isWeighted().value())) {
      os << *std::static_pointer_cast<const UndirectedWeightedEdge<T>>(*it)
         << "\n";
    } else if (!((*it)->isDirected().has_value() &&
                 (*it)->isDirected().value()) &&
               !((*it)->isWeighted().has_value() &&
                 (*it)->isWeighted().value())) {
      os << *std::static_pointer_cast<const UndirectedEdge<T>>(*it) << "\n";
    } else {
      os << *it << "\n";
    }
  }
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const AdjacencyList<T> &adj) {
  os << "Adjacency Matrix:\n";
  unsigned long max_column = 0;
  for (const auto &it : adj) {
    if (it.second.size() > max_column) {
      max_column = (unsigned long)it.second.size();
    }
  }
  if (max_column == 0) {
    os << "ERROR in Print\n";
    return os;
  } else {
    os << "|--|";
    for (unsigned long i = 0; i < max_column; ++i) {
      os << "-----|";
    }
    os << "\n";
    for (const auto &it : adj) {
      os << "|N" << it.first->getId() << "|";
      for (const auto &it2 : it.second) {
        os << "N" << it2.first->getId() << ",E" << it2.second->getId() << "|";
      }
      os << "\n|--|";
      for (unsigned long i = 0; i < max_column; ++i) {
        os << "-----|";
      }
      os << "\n";
    }
  }
  return os;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_OUTPUTOPERATION_IMPL_H__