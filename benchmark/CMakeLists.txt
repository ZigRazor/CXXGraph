option(BENCHMARK "Enable Benchmark" OFF)
if(BENCHMARK)

	include(FetchContent)

	FetchContent_Declare(
    	googlebenchmark
    	GIT_REPOSITORY https://github.com/google/benchmark.git
    	GIT_TAG origin/main
	)

	FetchContent_MakeAvailable(googlebenchmark)

	file (GLOB BENCHMARK_FILES "*.cpp" "*.hpp")
	add_executable(benchmark_exe ${BENCHMARK_FILES})

	target_compile_definitions(benchmark_exe 
		PUBLIC WITH_COMPRESSION
	)
	target_include_directories(benchmark_exe PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
	target_link_libraries(benchmark_exe
						benchmark::benchmark
					   pthread
					   ssl
					   crypto
					   z)
endif(BENCHMARK)