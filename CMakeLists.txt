cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 0.2.0)

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

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE)
	message( "Code Coverage Enabled" )
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
		--coverage #set coverage flag
		-fprofile-arcs
		-ftest-coverage
		-fPIC
	)
	link_libraries(
		"gcov"
		"-fprofile-arcs"
		"--coverage"
	)

endif(CODE_COVERAGE)

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
						test/BellmanFordTest.cpp
						test/FWTest.cpp
						test/PrimTest.cpp
						test/BFSTest.cpp
						test/DFSTest.cpp
						test/CycleCheckTest.cpp
						test/RWOutputTest.cpp
						test/PartitionTest.cpp
						test/DialTest.cpp
						test/GraphSlicingTest.cpp
				)
target_include_directories(test_exe PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
target_link_libraries(test_exe
					   libgtest.a
					   libgtest_main.a
					   pthread
					   z)


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
add_test(test_dfs test_exe --gtest_filter=DFSTest*)
add_test(test_cycle_check test_exe --gtest_filter=CycleCheckTest*)
add_test(test_rw_output test_exe --gtest_filter=RWOutputTest*)
add_test(test_partition test_exe --gtest_filter=PartitionTest*)
add_test(test_dial test_exe --gtest_filter=DialTest*)

option(BENCHMARK "Enable Benchmark" OFF)
if(BENCHMARK)
	add_executable(benchmark 	benchmark/Utilities.hpp
							benchmark/Node_BM.cpp
							benchmark/Edge_BM.cpp
							benchmark/Graph_BM.cpp
				)
	target_include_directories(benchmark PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
	target_link_libraries(benchmark
					   libbenchmark.a
					   libbenchmark_main.a
					   pthread
					   z)
endif(BENCHMARK)

install(FILES include/Graph.hpp DESTINATION /usr/include)
