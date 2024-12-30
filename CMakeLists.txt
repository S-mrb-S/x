cmake_minimum_required(VERSION 3.20)

project(x_core LANGUAGES CXX C)

############################################################
## Standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

############################################################
## Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

############################################################
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

############################################################
## Check if VCPKG_ROOT is defined
if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")
else ()
    message(FATAL_ERROR "VCPKG_ROOT is not defined in the environment.")
endif ()

# Include vcpkg build system
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

############################################################
## Create the executable from src/main.cc
add_executable(x_core src/main.cc)

############################################################
## Include the header directory for the executable
target_include_directories(x_core PRIVATE include)

############################################################
## Find and link libraries
find_package(fmt CONFIG REQUIRED)
target_link_libraries(x_core PRIVATE fmt::fmt-header-only)

find_package(Taskflow CONFIG REQUIRED)
target_link_libraries(x_core PRIVATE Taskflow::Taskflow)

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(x_core PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(x_core PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

## Threads (POSIX)
find_package(Threads REQUIRED)

target_link_libraries(x_core PRIVATE ${CMAKE_THREAD_LIBS_INIT})
############################################################
## Compiler options
if (MSVC)
    target_compile_options(x_core PRIVATE /O2 /arch:AVX2)
else ()
    target_compile_options(x_core PRIVATE -O2 -march=native -flto)
endif ()

############################################################
# Enable Link Time Optimization (LTO) for Release builds
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()
