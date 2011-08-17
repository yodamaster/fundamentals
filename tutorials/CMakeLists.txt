cmake_minimum_required(VERSION 2.8)
project(tutorials)
include_directories(${tutorials_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -g")

add_subdirectory(examples)
enable_testing()
add_subdirectory(tests)
