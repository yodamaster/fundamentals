cmake_minimum_required(VERSION 2.8)
project(tutorials)
include_directories(${tutorials_SOURCE_DIR}/include)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTI_THREADED ON)
find_package(Boost 1.48.0 REQUIRED unit_test_framework regex)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

# set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -g")
# set(LD_LIBRARY_PATH "/home/glynos/lib")
# set(RPATH "/home/glynos/lib")

set(EXAMPLES
  boost_range_algorithm
  bloom_filter
  lispic
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} examples/${example}.cpp)
  target_link_libraries(tutorials-${example} ${Boost_REGEX_LIBRARY})
endforeach(example)

add_executable(tutorials-rbtree examples/test_red_black_tree.c examples/red_black_tree.c examples/stack.c examples/misc.c)

add_subdirectory(examples)
enable_testing()
add_subdirectory(tests)
