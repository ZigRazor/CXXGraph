cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 0.0.1)

configure_file(CXXGraphConfig.h.in CXXGraphConfig.h)

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
						   
add_executable(test_exe test/main.cpp test/test1.cpp)
target_include_directories(test_exe PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
target_link_libraries(test_exe 
					   libgtest.a 
					   libgtest_main.a 
					   pthread )

