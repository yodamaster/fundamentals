cmake_minimum_required(VERSION 2.8)
project(tutorials)
include_directories(${tutorials_SOURCE_DIR}/include)

find_package(Boost 1.46.0 COMPONENTS unit_test_framework regex)
if (Boost_FOUND)
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTI_THREADED ON)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -g")
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

enable_testing()
set(TESTS
  list_tests
  stack_tests
  queue_tests
  binary_tree_tests
  hash_table_tests
  red_black_tree_tests
  concurrent_queue_tests
  )

foreach(test ${TESTS})
  add_executable(tutorials-${test} tests/${test}.cpp)
  target_link_libraries(tutorials-${test} ${Boost_LIBRARIES})
  add_test(tutorials-${test} tutorials-${test})
endforeach(test)
