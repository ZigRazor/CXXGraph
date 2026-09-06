cmake_minimum_required(VERSION 3.9)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(floyd_warshall floyd_warshall.cpp)

target_link_libraries(floyd_warshall
                      ${PROJECT_NAME})
