option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

# Force dynamic linking since MSVC now links C runtimes dynamically by default
set(gtest_force_shared_crt on)

if (NOT MSVC)
    option(CODE_COVERAGE "Enable coverage reporting" OFF)
    if(CODE_COVERAGE)
        message( "Code Coverage Enabled" )
        add_compile_options(
            -O0  #no optimization
            -g   #generate debug info
            --coverage #set coverage flag
            -fprofile-arcs
            -ftest-coverage
            -fprofile-update=atomic
            -fPIC
        )
        link_libraries(
            "gcov"
            "-fprofile-arcs"
            "-fprofile-update=atomic"
            "--coverage"
        )

    endif(CODE_COVERAGE)
endif(NOT MSVC)

option(TCMALLOC "Enable TCMalloc Optimization" OFF)
if(TCMALLOC)
    link_libraries(
            "-ltcmalloc"
        )
    message( "TCMalloc Enabled" )
endif(TCMALLOC)

option(TEST "Enable Test" OFF)
if(TEST)
    include(${CPM_DOWNLOAD_LOCATION})
	if (NOT MSVC)
        add_compile_options(
        -Wall
        -Wextra
        )
    endif(NOT MSVC)

    CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG origin/main
        OPTIONS "gtest_forced_shared_crt ON CACHE BOOL FORCE"
    )

    CPMAddPackage(
        NAME zlib
        GITHUB_REPOSITORY madler/zlib
        VERSION 1.3.1
        OPTIONS "CMAKE_POSITION_INDEPENDENT_CODE True"
    )

    file (GLOB TEST_FILES "*.cpp" "*.hpp" "*.h")
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

    if(NOT gtest_disable_pthreads)
        target_link_libraries(test_exe PUBLIC pthread)
    endif(NOT gtest_disable_pthreads)

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
    add_test(test_DOT test_exe --gtest_filter=DOTTest*)

    add_test(test_bellmanford test_exe --gtest_filter=BellmanFord*)
    add_test(test_boruvka test_exe --gtest_filter=Boruvka*)
    add_test(test_bron_kerbosch test_exe --gtest_filter=BronKerbosch*)
    add_test(test_connectivity test_exe --gtest_filter=Connectivity*)
    add_test(test_euler_path test_exe --gtest_filter=EulerPath*)
    add_test(test_fordfulkerson test_exe --gtest_filter=FordFulkerson*)
    add_test(test_fw test_exe --gtest_filter=FW*)
    add_test(test_graph_slicing test_exe --gtest_filter=GraphSlicing*)
    add_test(test_hopcroft_karp test_exe --gtest_filter=HopcroftKarp*)
    add_test(test_kruskal test_exe --gtest_filter=Kruskal*)
    add_test(test_mtx test_exe --gtest_filter=MTX*)
    add_test(test_prim test_exe --gtest_filter=Prim*)
    add_test(test_tarjan test_exe --gtest_filter=Tarjan*)
    add_test(test_topological_sort test_exe --gtest_filter=TopologicalSort*)
    add_test(test_transitive_reductiono test_exe --gtest_filter=TransitiveReduction*)
    add_test(test_union_find test_exe --gtest_filter=UnionFind*)
    add_test(test_floyd_warshall test_exe --gtest_filter=FloydWarshall*)
    add_test(test_welsh_powell_coloring test_exe --gtest_filter=welshPowellColoring*)
endif(TEST)
