option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

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

option(TEST "Enable Test" OFF)
if(TEST)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG origin/main
        #GIT_TAG        v1.13.0 # release-1.13.0
    )

    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.2.13
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    set(SAVE_CMAKE_POSITION_INDEPENDENT_CODE ${CMAKE_POSITION_INDEPENDENT_CODE})
    set(CMAKE_POSITION_INDEPENDENT_CODE True)
    FetchContent_MakeAvailable(zlib)
    set(CMAKE_POSITION_INDEPENDENT_CODE ${SAVE_CMAKE_POSITION_INDEPENDENT_CODE})

    file (GLOB TEST_FILES "*.cpp" "*.hpp")

    add_executable(test_exe ${TEST_FILES})

    target_compile_definitions(test_exe
        PUBLIC WITH_COMPRESSION
    )
    target_include_directories(test_exe
        PUBLIC "${PROJECT_SOURCE_DIR}/include"
        PUBLIC ${zlib_BINARY_DIR}
        PUBLIC ${zlib_SOURCE_DIR}
    )
    target_link_libraries(test_exe
        PUBLIC GTest::gtest_main
        PUBLIC zlibstatic
    )

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
    add_test(test_kosaraju test_exe --gtest_filter=TestKosaraju*)
    add_test(test_bestfirstsearch test_exe --gtest_filter=BestFirstSearch*)
    add_test(test_kahn test_exe --gtest_filter=Kahn*)
endif(TEST)