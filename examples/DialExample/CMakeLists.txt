cmake_minimum_required(VERSION 3.9)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(dial_example dial_example.cpp)

target_link_libraries(dial_example
                      ${PROJECT_NAME})
