set(EXAMPLES
  boost_range_algorithm
  merge_sort
  quick_sort
  parallel_for_each
  parallel_count
  parallel_count_if
  parallel_merge_sort
  async_test
  bloom_filter
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} ${example}.cpp)
  target_link_libraries(tutorials-${example}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_TIMER_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    -lrt)
endforeach(example)
