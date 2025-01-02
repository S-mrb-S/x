cmake_minimum_required(VERSION 3.20)

# Set default compilers if not specified
if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "clang++")
endif()

if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "clang")
endif()

project(x_core LANGUAGES CXX C)

############################################################
## Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

############################################################
## Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

############################################################
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

############################################################
## Check if VCPKG_ROOT is defined
if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "Using VCPKG_ROOT from environment: ${VCPKG_ROOT}")

    # Include vcpkg build system
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else ()
    message(WARNING "VCPKG_ROOT is not defined in the environment. Proceeding without VCPKG.")
endif ()

############################################################
## Create the executable from src/main.cc
add_executable(x_core src/main.cc)

############################################################
## Find and link libraries
find_package(fmt CONFIG)
target_link_libraries(x_core PUBLIC fmt::fmt-header-only)

#find_package(bsoncxx CONFIG REQUIRED)
#target_link_libraries(x_core PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

#find_package(mongocxx CONFIG REQUIRED)
#target_link_libraries(x_core PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

option(ENABLE_OPENMP "Enable OpenMP support" ON)
find_package(OpenMP)

if(ENABLE_OPENMP AND (OpenMP_C_FOUND OR OpenMP_CXX_FOUND))
    message(STATUS "OpenMP found, enabling OpenMP support.")
    add_definitions(-DENABLE_OPENMP)
else()
    if(ENABLE_OPENMP)
        message(WARNING "OpenMP not found. Disabling OpenMP support.")
    else()
        message(STATUS "OpenMP support disabled by user.")
    endif()
endif()

if(OpenMP_CXX_FOUND)
    target_link_libraries(x_core PUBLIC OpenMP::OpenMP_CXX)
endif()

if(OpenMP_C_FOUND)
    target_link_libraries(x_core PUBLIC OpenMP::OpenMP_C)
endif()

############################################################
## Compiler options for GCC
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(x_core PRIVATE
            -O3                     # Maximum optimization
            -march=native           # Optimize for the current architecture
            -mtune=native           # Tune for the current architecture
            -flto                   # Enable Link Time Optimization
#            -fomit-frame-pointer     # Omit frame pointer for optimization
#            -fno-exceptions         # Disable exceptions if not needed
#            -fno-rtti               # Disable RTTI if not needed
    )
endif ()

############################################################
# Enable Link Time Optimization (LTO) for Release builds
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()
