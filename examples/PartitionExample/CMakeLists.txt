cmake_minimum_required(VERSION 3.9)
project(PartitionExample)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

add_executable(partition_example partition_example.cpp)
target_include_directories(partition_example PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(partition_example
                        pthread
                        ssl
                        crypto
                        z)