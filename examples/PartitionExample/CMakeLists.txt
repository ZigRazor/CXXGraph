cmake_minimum_required(VERSION 3.9)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(partition_example partition_example.cpp)

target_link_libraries(partition_example
                      ${PROJECT_NAME})
