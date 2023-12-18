cmake_minimum_required(VERSION 3.9)

project(PrimExample)

# specify the C++ standard

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

add_executable(prim_example prim_example.cpp)

target_include_directories(prim_example PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(prim_example
                        pthread
                        ssl
                        crypto
                        z)