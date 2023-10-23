cmake_minimum_required(VERSION 3.9)
project(NetworkDynamicsExample)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

add_executable(network_dynamics_example network_dynamics_example.cpp)
target_include_directories(network_dynamics_example PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(network_dynamics_example
                        pthread
                        ssl
                        crypto
                        z)