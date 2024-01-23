cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 3.1.0)

configure_file(CXXGraphConfig.h.in ${PROJECT_SOURCE_DIR}/include/CXXGraph/CXXGraphConfig.h)

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

# set up CPM.cmake
if(CPM_SOURCE_CACHE)
	set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
	set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM.cmake")
else()
	set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
	message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
	file(DOWNLOAD
    	https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
    	${CPM_DOWNLOAD_LOCATION}
	)
endif()

add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(examples)

#install(FILES include/Graph.hpp DESTINATION /usr/include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
