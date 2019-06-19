cmake_minimum_required(VERSION 3.11)
project(cpp-pipedream VERSION 0.1)

set(BUILD_EXAMPLES ON CACHE BOOL "Enable examples")
set(BUILD_TESTING OFF CACHE BOOL "Enable tests")
set(INSTALL_INCLUDE_DIR "include" CACHE PATH "Headers will be installed here")
set(INSTALL_LIB_DIR "lib" CACHE PATH "CMake config will fall under this")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  include(Setup)
endif()

add_library(pipedream INTERFACE)
target_include_directories(pipedream INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
export(PACKAGE pipedream)

include(install)
include(docs)

if(BUILD_TESTING)
    message(STATUS "Testing enabled")
    enable_testing()
    add_subdirectory(t)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  SetupPost()
endif()
