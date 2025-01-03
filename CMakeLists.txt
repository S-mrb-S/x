cmake_minimum_required(VERSION 3.20)

# Project definition
project(x_core LANGUAGES CXX C)

# Set default compilers if not specified
if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "clang++")
endif()

if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "clang")
endif()

# Set C++ and C standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Current source directory
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Check if VCPKG_ROOT is defined
if(DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else()
    message(WARNING "VCPKG_ROOT is not defined in the environment. Proceeding without VCPKG.")
endif()

# Create the executable
add_executable(x_core src/main.cc)

# Find and link libraries
find_package(CURL REQUIRED)
target_link_libraries(x_core PUBLIC CURL::libcurl)

find_package(fmt CONFIG QUIET)
if(fmt_FOUND)
    target_link_libraries(x_core PUBLIC fmt::fmt-header-only)
    target_compile_definitions(x_core PUBLIC USE_FMT)
    message(STATUS "fmt library added.")
else()
    message(WARNING "fmt library not found.")
endif()

find_package(OpenMP QUIET)
if(OpenMP_CXX_FOUND)
    target_link_libraries(x_core PUBLIC OpenMP::OpenMP_CXX)
    target_compile_definitions(x_core PUBLIC USE_OPENMP)
    message(STATUS "OpenMP library added.")
else()
    message(WARNING "OpenMP library not found.")
endif()

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(x_core PUBLIC JsonCpp::JsonCpp)

# Compiler options for GNU and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(x_core PRIVATE
        -O3                     # Maximum optimization
        -march=native           # Optimize for the current architecture
        -mtune=native           # Tune for the current architecture
        -flto                   # Enable Link Time Optimization
    )
endif()

# Enable Link Time Optimization (LTO) for Release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
