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

# ── Parallel execution backend ────────────────────────────────────────────────
option(WITH_OPENMP "Enable OpenMP parallel algorithm backend" OFF)
option(WITH_TBB "Enable TBB parallel algorithm backend" OFF)


if(WITH_OPENMP)
  find_package(OpenMP REQUIRED)
  if(OpenMP_CXX_FOUND)
    link_libraries(OpenMP::OpenMP_CXX)
    add_compile_definitions(CXXGRAPH_WITH_OPENMP)
    message(STATUS "CXXGraph: OpenMP parallel backend enabled")
  endif()
else()
    # std::execution::par_unseq needs TBB on Linux (GCC/Clang)
    find_package(TBB QUIET)
    if(TBB_FOUND)
      link_libraries(TBB::tbb)
      message(STATUS "CXXGraph: std::execution backend found TBB (recommended)")
    else()
      message(STATUS "CXXGraph: std::execution backend active (no TBB — sequential fallback on GCC)")
    endif()
endif()


if (MSVC)
	add_compile_options(/bigobj)
  add_compile_options(
    /WX
    /W4
    /w14254
    /w14263
    /w14265
    /w14296
    /w14311
    /w14545
    /w14546
    /w14547
    /w14549
    /w14555
    /w14619
    /w14640
    /w14905
    /w14906
    /w14928
    /we4289
    /permissive-
    /wd4127
    /wd4244
    /wd4456
    /wd4458
    /wd4459
  )
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
    -Wdouble-promotion
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
  )
endif(MSVC)

# set up CPM.cmake
set(CPM_VERSION "0.40.2")

# ── Resolve CPM_SOURCE_CACHE to an absolute path ──────────────────────────────
if(DEFINED ENV{CPM_SOURCE_CACHE})
  # Convert whatever the env var holds (including "~" on Unix) to an
  # absolute, normalised CMake path.  file(TO_CMAKE_PATH) converts slashes
  # but does NOT expand "~" — we do that manually first via GLOB.
  set(_raw_cache "$ENV{CPM_SOURCE_CACHE}")

  # Expand a leading "~" using CMake's own notion of the home directory.
  # (cmake_path NORMAL_PATH does not expand "~" either, but we can do it
  #  portably by asking the C runtime via a small trick.)
  if(_raw_cache MATCHES "^~(.*)")
    # $ENV{HOME} is set on Linux/macOS; on Windows use $ENV{USERPROFILE}.
    if(DEFINED ENV{HOME})
      set(_raw_cache "$ENV{HOME}${CMAKE_MATCH_1}")
    elseif(DEFINED ENV{USERPROFILE})
      set(_raw_cache "$ENV{USERPROFILE}${CMAKE_MATCH_1}")
    endif()
  endif()

  file(TO_CMAKE_PATH "${_raw_cache}" CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_VERSION}.cmake")
  message(STATUS "CXXGraph: CPM cache directory: ${CPM_SOURCE_CACHE}")
else()
  # No cache requested — download into the binary tree (never persisted).
  set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_VERSION}.cmake")
  message(STATUS "CXXGraph: CPM cache disabled (set CPM_SOURCE_CACHE to enable)")
endif()

# ── Download CPM if not already present ───────────────────────────────────────
if(NOT EXISTS "${CPM_DOWNLOAD_LOCATION}")
  get_filename_component(_cpm_dir "${CPM_DOWNLOAD_LOCATION}" DIRECTORY)
  file(MAKE_DIRECTORY "${_cpm_dir}")   # ensure parent dirs exist

  message(STATUS "CXXGraph: Downloading CPM.cmake ${CPM_VERSION} to ${CPM_DOWNLOAD_LOCATION}")
  file(
    DOWNLOAD
      "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_VERSION}/CPM.cmake"
      "${CPM_DOWNLOAD_LOCATION}"
    TLS_VERIFY ON
    STATUS _dl_status
  )
  list(GET _dl_status 0 _dl_code)
  if(NOT _dl_code EQUAL 0)
    list(GET _dl_status 1 _dl_msg)
    message(FATAL_ERROR "CXXGraph: Failed to download CPM.cmake: ${_dl_msg}")
  endif()
endif()

add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(examples)
add_subdirectory(python)

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
