set(EXAMPLES
  #boost_range_algorithm
  merge_sort
  quick_sort
  #merge_sort_test
  #quick_sort_test
  parallel_for_each
  parallel_count
  parallel_count_if
  parallel_find
  producer_consumer
  #parallel_merge_sort
  #parallel_merge_sort_test
  async_test
  #bloom_filter
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} ${example}.cpp)
  target_link_libraries(tutorials-${example}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_TIMER_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})
endforeach(example)
