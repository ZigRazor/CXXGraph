cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 0.5.0)

configure_file(CXXGraphConfig.h.in ${PROJECT_SOURCE_DIR}/include/CXXGraphConfig.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

option(DEBUG "Enable Debug" OFF)
if(DEBUG)
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
	)

endif(DEBUG)

add_subdirectory(test)

add_subdirectory(benchmark)

add_subdirectory(examples)

#install(FILES include/Graph.hpp DESTINATION /usr/include)
