cmake_minimum_required(VERSION 3.20)

# Project definition
project(x_core DESCRIPTION Core LANGUAGES CXX)

# Set default compilers if not specified
if (NOT DEFINED CMAKE_CXX_COMPILER)
    find_program(CLANG_CPP_COMPILER NAMES clang++)

    if (CLANG_CPP_COMPILER)
        set(CMAKE_CXX_COMPILER ${CLANG_CPP_COMPILER})
    else ()
        find_program(GCC_CPP_COMPILER NAMES g++)
        if (GCC_CPP_COMPILER)
            set(CMAKE_CXX_COMPILER ${GCC_CPP_COMPILER})
        else ()
            message(FATAL_ERROR "No suitable C++ compiler found (Clang++ or g++).")
        endif ()
    endif ()
endif ()

# Set C++ standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Current source directory
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Check if VCPKG_ROOT is defined
if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else ()
    message(WARNING "VCPKG_ROOT is not defined in the environment. Proceeding without VCPKG.")
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Create the executable
add_executable(x_core 5gfi6gdi9/main.cc)

set_target_properties(x_core PROPERTIES
        OUTPUT_NAME "xcore"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Find and link libraries
find_package(CURL REQUIRED)
target_link_libraries(x_core PUBLIC CURL::libcurl)


find_package(fmt CONFIG QUIET)
if (fmt_FOUND)
    target_link_libraries(x_core PUBLIC fmt::fmt-header-only)
    target_compile_definitions(x_core PUBLIC USE_FMT)
    message(STATUS "fmt library added.")
else ()
    message(WARNING "fmt library not found.")
endif ()


find_package(OpenMP QUIET)
if (OpenMP_CXX_FOUND)
    target_link_libraries(x_core PUBLIC OpenMP::OpenMP_CXX)
    target_compile_definitions(x_core PUBLIC USE_OPENMP)
    message(STATUS "OpenMP library added.")
else ()
    message(WARNING "OpenMP library not found.")
endif ()


# find_package(jsoncpp REQUIRED)
# target_link_libraries(x_core PUBLIC jsoncpp_lib)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
# add_executable(myprogram myprogram.cpp)
target_link_libraries(x_core PUBLIC ${JSONCPP_LIBRARIES})

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Compiler options for GNU and Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(x_core PRIVATE
            -O3                     # Maximum optimization
            -march=native           # Optimize for the current architecture
            -mtune=native           # Tune for the current architecture
            -flto                   # Enable Link Time Optimization
    )
endif ()

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Enable Link Time Optimization (LTO) for Release builds
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()
