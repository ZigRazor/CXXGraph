cmake_minimum_required(VERSION 3.9)
project(floydWarshallExample)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

add_executable(floyd_warshall floyd_warshall.cpp)
target_include_directories(floyd_warshall PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(floyd_warshall
                        pthread
                        ssl
                        crypto
                        z)