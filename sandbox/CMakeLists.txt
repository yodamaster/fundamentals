cmake_minimum_required(VERSION 2.8)
project(sandbox)
include_directories(${sandbox_SOURCE_DIR}/include)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTI_THREADED ON)
find_package(Boost 1.54.0 REQUIRED unit_test_framework regex system chrono timer date_time locale)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

set(CMAKE_PREFIX_PATH "c:\\Qt\\5.1.1\\msvc2012\\")
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

find_package(Threads)

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  set(CMAKE_CXX_FLAGS "-std=c++11 -g")
endif()
add_definitions(-DBOOST_CHRONO_INLINED)

add_subdirectory(examples)
