cmake_minimum_required(VERSION 3.15)
project(CXXGraphPythonBindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.12.0
)
FetchContent_MakeAvailable(pybind11)


set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# # Add library target (header-only here)
# add_library(CXXGraphLib INTERFACE)
# target_include_directories(CXXGraphLib INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Add pybind11 module
pybind11_add_module(cxxgraph bindings.cpp)
