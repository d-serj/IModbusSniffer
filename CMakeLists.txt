cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME "iModSniffer")

project(${TARGET_NAME} C CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include(GNUInstallDirs)

set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

set(Boost_DEBUG 1)
find_package(Boost REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/source/third_party/fmt)
add_subdirectory(${CMAKE_SOURCE_DIR}/source/third_party/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/source/third_party/modbus-parser)
add_subdirectory(${CMAKE_SOURCE_DIR}/source)
