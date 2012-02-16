find_package(Boost 1.48.0 REQUIRED unit_test_framework)

if (Boost_FOUND)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_MULTI_THREADED ON)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

set(TESTS
  list_tests
  stack_tests
  queue_tests
  binary_tree_tests
  hash_table_tests
  red_black_tree_tests
  generic_tree_tests
  threadsafe_queue_tests
  threadsafe_stack_tests
  threadsafe_hash_table_tests
  )

foreach(test ${TESTS})
  add_executable(tutorials-${test} ${test}.cpp)
  target_link_libraries(tutorials-${test} ${Boost_LIBRARIES})
  add_test(tutorials-${test} tutorials-${test})
endforeach(test)
