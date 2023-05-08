option(BENCHMARK "Enable Benchmark" OFF)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

if(BENCHMARK)

	include(FetchContent)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG origin/main
		#GIT_TAG        v1.13.0 # release-1.13.0
	)

	FetchContent_Declare(
		googlebenchmark
		GIT_REPOSITORY https://github.com/google/benchmark.git
		GIT_TAG origin/main
	)

	FetchContent_Declare(
		zlib
		GIT_REPOSITORY https://github.com/madler/zlib.git
		GIT_TAG v1.2.13
	)

	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
	FetchContent_MakeAvailable(googlebenchmark)

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