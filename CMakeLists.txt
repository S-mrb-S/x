cmake_minimum_required(VERSION 3.20)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_VERBOSE_MAKEFILE ON)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set(CORE_NAME xcore)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Project definition
project(${CORE_NAME} DESCRIPTION "The Core" LANGUAGES CXX)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Set C++ standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Clang++ (llvm)
find_program(CLANG_CPP_COMPILER NAMES clang++)

if (CLANG_CPP_COMPILER)
    set(CMAKE_CXX_COMPILER ${CLANG_CPP_COMPILER})
else ()
    # G++
    find_program(GCC_CPP_COMPILER NAMES g++)
    if (GCC_CPP_COMPILER)
        set(CMAKE_CXX_COMPILER ${GCC_CPP_COMPILER})
    else ()
        # MSVC
        if (MSVC)
            set(CMAKE_CXX_COMPILER "cl.exe")
        else ()
            message(FATAL_ERROR "No suitable C++ compiler found (Clang++, g++, or MSVC).")
        endif ()
    endif ()
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif ()

message(STATUS "< ============================== >")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Check if VCPKG_ROOT is defined
if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")
    message(STATUS "< ============================== >")
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else ()
    message(WARNING "VCPKG_ROOT is not defined in the environment. Proceeding without VCPKG.")
    message(STATUS "< ============================== >")
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Create the executable
add_executable(${CORE_NAME} 5gfi6gdi9/main.cc)

set_target_properties(${CORE_NAME} PROPERTIES
        OUTPUT_NAME ${CORE_NAME}
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
message(STATUS "< ============================== >")

# Find and link libraries
find_package(CURL REQUIRED)
target_link_libraries(${CORE_NAME} PUBLIC CURL::libcurl)

find_package(fmt CONFIG QUIET)
if (fmt_FOUND)
    target_link_libraries(${CORE_NAME} PUBLIC fmt::fmt-header-only)
    target_compile_definitions(${CORE_NAME} PUBLIC USE_FMT)
    message(STATUS "fmt library added.")
else ()
    message(WARNING "fmt library not found.")
endif ()


find_package(OpenMP QUIET)
if (OpenMP_CXX_FOUND)
    target_link_libraries(${CORE_NAME} PUBLIC OpenMP::OpenMP_CXX)
    target_compile_definitions(${CORE_NAME} PUBLIC USE_OPENMP)
    message(STATUS "OpenMP library added.")
else ()
    message(WARNING "OpenMP library not found.")
endif ()


find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${CORE_NAME} PUBLIC JsonCpp::JsonCpp)

message(STATUS "< ============================== >")
# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG") # force debug msg and asserts
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Compiler options for GNU and Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CORE_NAME} PRIVATE
            -O3                     # Maximum optimization
            -march=native           # Optimize for the current architecture
            -mtune=native           # Tune for the current architecture
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${CORE_NAME} PRIVATE
            /O2                     # Maximum optimization
            /arch:NATIVE            # Optimize for the current architecture
    )
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Enable Link Time Optimization (LTO) for Release builds
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
