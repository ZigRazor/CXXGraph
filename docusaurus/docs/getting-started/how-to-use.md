---
id: how-to-use-cxxgraph
title: 'How to Use CXXGraph'
tags: ['introduction', 'how to use', 'getting started']
---
### How do I put CXXGraph on my project?

To use CXXGraph in your project, simply put the header file `CXXGraph.hpp` where you need it, and include the following in your header:

```
include "CXXGraph.hpp"

using namespace CXXGRAPH;
```

It's that easy!

### Using CPM
Older versions of CXXGraph and some machines will not support the intended method. [CPM](https://github.com/cpm-cmake/CPM.cmake) is a reliable alternative method of adding CXXGraph to your project.

After adding CPM to your project's `cmake` directory, use the following code to include CXXGraph directly from the remote repository.

```
CPMAddPackage("gh:ZigRazor/CXXGraph")
if (CXXGraph_ADDED)
    add_library(CXXGraph INTERFACE IMPORTED GLOBAL)
    target_include_directories(CXXGraph INTERFACE "${CXXGraph_SOURCE_DIR}/include")
endif()
```
