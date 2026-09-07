cmake_minimum_required(VERSION 3.9)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(prim_example prim_example.cpp)

target_link_libraries(prim_example
                      ${PROJECT_NAME})
