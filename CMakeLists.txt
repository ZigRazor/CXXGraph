cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(CXXGraph VERSION 4.1.0)
set(PROJECT_NAMESPACE ${PROJECT_NAME})
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

if (MSVC)
	add_compile_options(/bigobj)
else ()
	option(SANITIZE "Enable Sanitize" OFF)
	if(SANITIZE)
		add_compile_options(
			-fsanitize=address
			-fsanitize=leak
		)
		add_link_options(
			-fsanitize=address
			-fsanitize=leak
		)
	endif(SANITIZE)
  add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
  )
endif(MSVC)

# set up CPM.cmake
if(CPM_SOURCE_CACHE)
	set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
	set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM.cmake")
else()
	set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
	message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
	file(DOWNLOAD
    	https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
    	${CPM_DOWNLOAD_LOCATION}
	)
endif()

add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(examples)

configure_file(${PROJECT_SOURCE_DIR}/include/CXXGraph/version.h.in ${PROJECT_BINARY_DIR}/include/CXXGraph/version.h)

include(${CPM_DOWNLOAD_LOCATION})
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
#Main include dir
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> 
$<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
#Version include dir:
$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")

packageProject(
  # the name of the target to export
  NAME ${PROJECT_NAME}
  # the version of the target to export
  VERSION ${PROJECT_VERSION}
  # a temporary directory to create the config files
  BINARY_DIR ${PROJECT_BINARY_DIR}
  # location of the target's public headers
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  # should match the target's INSTALL_INTERFACE include directory
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  # (optional) option to install only header files with matching pattern
  INCLUDE_HEADER_PATTERN "*.h *.hpp"
  # semicolon separated list of the project's dependencies
  DEPENDENCIES ""
  # (optional) create a header containing the version info
  VERSION_HEADER "${PROJECT_NAME}/version.h"
  # (optional) create a export header using GenerateExportHeader module
  EXPORT_HEADER "${PROJECT_NAME}/export.h"
  # (optional) install your library with a namespace (Note: do NOT add extra '::')
  NAMESPACE ${PROJECT_NAMESPACE}
  # (optional) define the project's version compatibility, defaults to `AnyNewerVersion`
  # supported values: `AnyNewerVersion|SameMajorVersion|SameMinorVersion|ExactVersion`
  COMPATIBILITY AnyNewerVersion
  # (optional) option to disable the versioning of install destinations
  DISABLE_VERSION_SUFFIX YES
  # (optional) option to ignore target architecture for package resolution
  # defaults to YES for header only (i.e. INTERFACE) libraries
  ARCH_INDEPENDENT YES
  # (optional) option to generate CPack variables
  CPACK YES
  # (optional) relative install directory for runtimes: bins, libs, archives 
  # by default libs will be installed to <...>/lib/<packagename-version>/
  # / - means relative to <...>/lib, i.e. install libs to <...>/lib/, bins to <...>/bin/, etc
  RUNTIME_DESTINATION /
)
