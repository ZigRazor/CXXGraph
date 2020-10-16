cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 0.0.3)

configure_file(CXXGraphConfig.h.in ${PROJECT_SOURCE_DIR}/include/CXXGraphConfig.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(DEBUG "Enable Debug" OFF)
if(DEBUG)
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
	)
	
endif(DEBUG)	

# add the library
						   
add_executable(test_exe test/main.cpp 
						test/NodeTest.cpp
						test/EdgeTest.cpp
						test/DirectedEdgeTest.cpp
						test/UndirectedEdgeTest.cpp
						test/DirectedWeightedEdgeTest.cpp
						test/UndirectedWeightedEdgeTest.cpp
						test/GraphTest.cpp
						test/DijkstraTest.cpp
						test/BFSTest.cpp
				)
target_include_directories(test_exe PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
target_link_libraries(test_exe 
					   libgtest.a 
					   libgtest_main.a 
					   pthread )


enable_testing()

add_test(test_node test_exe --gtest_filter=NodeTest*)
add_test(test_edge test_exe --gtest_filter=EdgeTest*)
add_test(test_directededge test_exe --gtest_filter=DirectedEdgeTest*)
add_test(test_undirectededge test_exe --gtest_filter=UndirectedEdgeTest*)
add_test(test_directedweightededge test_exe --gtest_filter=DirectedWeightedEdgeTest*)
add_test(test_undirectedweightededge test_exe --gtest_filter=UndirectedWeightedEdgeTest*)
add_test(test_graph test_exe --gtest_filter=GraphTest*)
add_test(test_dijkstra test_exe --gtest_filter=DijkstraTest*)
add_test(test_bfs test_exe --gtest_filter=BFSTest*)

