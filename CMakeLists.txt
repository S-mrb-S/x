cmake_minimum_required(VERSION 3.20)

project(t1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Check if VCPKG_ROOT is defined
if(DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")
else()
    message(FATAL_ERROR "VCPKG_ROOT is not defined in the environment.")
endif()

# Include vcpkg build system
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Create the executable from src/core.cc
add_executable(core src/core.cc)

# Include the header directory for the executable
target_include_directories(core PRIVATE include)

# Find and link libraries
find_package(fmt CONFIG REQUIRED)
target_link_libraries(core PRIVATE fmt::fmt)

find_package(Taskflow CONFIG REQUIRED)
target_link_libraries(core PRIVATE Taskflow::Taskflow)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(core PRIVATE spdlog::spdlog)

if(MSVC)
    target_compile_options(core PRIVATE /O2 /arch:AVX2)
else()
    target_compile_options(core PRIVATE -O3 -march=native)
    target_compile_options(core PRIVATE -flto)
endif()
