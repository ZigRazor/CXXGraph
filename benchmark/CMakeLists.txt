option(BENCHMARK "Enable Benchmark" OFF)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

if(BENCHMARK)
	include(${CPM_DOWNLOAD_LOCATION})

	CPMAddPackage(
		NAME googletest
		GITHUB_REPOSITORY google/googletest
		GIT_TAG origin/main
		OPTIONS "gtest_forced_shared_crt ON CACHE BOOL FORCE"
	)

	CPMAddPackage(
		NAME googlebenchmark
		GITHUB_REPOSITORY google/benchmark
		GIT_TAG origin/main
	)

	CPMAddPackage(
		NAME zlib
		GITHUB_REPOSITORY madler/zlib
		VERSION 1.2.13
		OPTIONS "CMAKE_POSITION_INDEPENDENT_CODE True"
	)

	file (GLOB BENCHMARK_FILES "*.cpp" "*.hpp")
	add_executable(benchmark_exe ${BENCHMARK_FILES})

	target_compile_definitions(benchmark_exe 
		PUBLIC WITH_COMPRESSION
	)
	target_include_directories(benchmark_exe PUBLIC
		PUBLIC ${PROJECT_SOURCE_DIR}/include
		PUBLIC ${zlib_BINARY_DIR}
		PUBLIC ${zlib_SOURCE_DIR}
	)
	target_link_libraries(benchmark_exe
		PUBLIC GTest::gtest
		PUBLIC benchmark::benchmark
		PUBLIC zlibstatic
	)
endif(BENCHMARK)