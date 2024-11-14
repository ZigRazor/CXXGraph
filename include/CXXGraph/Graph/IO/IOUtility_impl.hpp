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

#ifndef __CXXGRAPH_IOUTILITY_IMPL_H__
#define __CXXGRAPH_IOUTILITY_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
std::optional<std::pair<std::string, char>> Graph<T>::getExtenstionAndSeparator(
    InputOutputFormat format) const {
  if (format == InputOutputFormat::STANDARD_CSV) {
    return std::pair<std::string, char>(".csv", ',');
  } else if (format == InputOutputFormat::STANDARD_TSV) {
    return std::pair<std::string, char>(".tsv", '\t');
  } else {
    return std::nullopt;
  }
}

// This ctype facet classifies ',' and '\t' as whitespace
struct csv_whitespace : std::ctype<char> {
  static const mask *make_table() {
    // make a copy of the "C" locale table
    static std::vector<mask> v(classic_table(), classic_table() + table_size);
    v[','] |= space;  // comma will be classified as whitespace
    v['\t'] |= space;
    v[' '] &= ~space;  // space will not be classified as whitespace
    return &v[0];
  }
  explicit csv_whitespace(std::size_t refs = 0)
      : ctype(make_table(), false, refs) {}
};

#ifdef WITH_COMPRESSION
template <typename T>
int Graph<T>::compressFile(const std::string &inputFile,
                           const std::string &outputFile) const {
  std::ifstream ifs;
  ifs.open(inputFile);
  if (!ifs.is_open()) {
    // ERROR File Not Open
    return -1;
  }
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

  const char *content_ptr = content.c_str();
  gzFile outFileZ = gzopen(outputFile.c_str(), "wb");
  if (outFileZ == NULL) {
    // printf("Error: Failed to gzopen %s\n", outputFile.c_str());
    return -1;
  }

  unsigned int zippedBytes;
  zippedBytes =
      gzwrite(outFileZ, content_ptr, (unsigned int)strlen(content_ptr));

  ifs.close();
  gzclose(outFileZ);
  return zippedBytes;
}

template <typename T>
int Graph<T>::decompressFile(const std::string &inputFile,
                             const std::string &outputFile) const {
  gzFile inFileZ = gzopen(inputFile.c_str(), "rb");
  if (inFileZ == NULL) {
    // printf("Error: Failed to gzopen %s\n", inputFile.c_str());
    return -1;
  }
  unsigned char unzipBuffer[8192];
  std::vector<unsigned char> unzippedData;
  std::ofstream ofs;
  ofs.open(outputFile);
  if (!ofs.is_open()) {
    // ERROR File Not Open
    return -1;
  }
  while (true) {
    unsigned int unzippedBytes;
    unzippedBytes = gzread(inFileZ, unzipBuffer, 8192);
    if (unzippedBytes > 0) {
      unzippedData.insert(unzippedData.end(), unzipBuffer,
                          unzipBuffer + unzippedBytes);
    } else {
      break;
    }
  }
  for (const auto &c : unzippedData) {
    ofs << c;
  }
  ofs << std::endl;
  ofs.close();
  gzclose(inFileZ);
  return 0;
}
#endif

}  // namespace CXXGraph
#endif  // __CXXGRAPH_IOUTILITY_IMPL_H__