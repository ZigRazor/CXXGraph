option(BENCHMARK "Enable Benchmark" OFF)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

if(BENCHMARK)
	include(${CPM_DOWNLOAD_LOCATION})


	# Always force Google Benchmark to build in Release mode
	set(BENCHMARK_BUILD_TYPE Release CACHE STRING "Build type for Google Benchmark" FORCE)

	# For multi-config generators (e.g., Visual Studio, Xcode), select Release configuration
	set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
	set(CMAKE_BUILD_TYPE ${BENCHMARK_BUILD_TYPE} CACHE STRING "" FORCE)

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
		OPTIONS
			"BENCHMARK_ENABLE_TESTING OFF"
			"CMAKE_BUILD_TYPE Release"
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
		PUBLIC ${zlib_BINARY_DIR}
		PUBLIC ${zlib_SOURCE_DIR}
	)
	target_link_libraries(benchmark_exe
		PUBLIC 
		GTest::gtest 
		benchmark::benchmark 
		zlibstatic
		${PROJECT_NAME}
	)
	
	# Ensure benchmark_exe itself is built in Release mode
	set_target_properties(benchmark_exe PROPERTIES
		CMAKE_BUILD_TYPE Release
	)
endif(BENCHMARK)