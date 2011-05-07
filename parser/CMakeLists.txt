cmake_minimum_required(VERSION 2.8)
project(parser)
include_directories(${tutorials_SOURCE_DIR})

find_package(Boost 1.46.0)
if (Boost_FOUND)
  set(Boost_USE_MULTI_THREADED ON)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -g")

add_executable(parser parser.cpp)
add_executable(iter_pos_parser iter_pos_parser.cpp)
