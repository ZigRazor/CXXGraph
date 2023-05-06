option(BENCHMARK "Enable Benchmark" OFF)
if(BENCHMARK)

	include(FetchContent)

	FetchContent_Declare(
    	googlebenchmark
    	GIT_REPOSITORY https://github.com/google/benchmark.git
    	GIT_TAG origin/main
	)

	FetchContent_Declare(
    openssl
    GIT_REPOSITORY https://github.com/janbar/openssl-cmake.git
    GIT_TAG origin/master
    OPTIONS "WITH_APPS OFF"
    )

    FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.2.13
    OPTIONS "CMAKE_POSITION_INDEPENDENT_CODE True"
    )

	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    set(WITH_APPS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(openssl)

    set(SAVE_CMAKE_POSITION_INDEPENDENT_CODE ${CMAKE_POSITION_INDEPENDENT_CODE})
    set(CMAKE_POSITION_INDEPENDENT_CODE True)
    FetchContent_MakeAvailable(zlib)
    set(CMAKE_POSITION_INDEPENDENT_CODE ${SAVE_CMAKE_POSITION_INDEPENDENT_CODE})

	file (GLOB BENCHMARK_FILES "*.cpp" "*.hpp")
	add_executable(benchmark_exe ${BENCHMARK_FILES})

	target_compile_definitions(benchmark_exe 
		PUBLIC WITH_COMPRESSION
	)
	target_include_directories(benchmark_exe PUBLIC
		PUBLIC "${PROJECT_SOURCE_DIR}/include"
		PUBLIC ${zlib_BINARY_DIR}
		PUBLIC ${zlib_SOURCE_DIR}
		PUBLIC ${openssl_SOURCE_DIR}/include
	)
	target_link_libraries(benchmark_exe
		PUBLIC benchmark::benchmark
		PUBLIC pthread
		PUBLIC ssl
		PUBLIC crypto
		PUBLIC zlibstatic)
endif(BENCHMARK)