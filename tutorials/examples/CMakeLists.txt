set(EXAMPLES
  boost_range_algorithm
  parallel_for_each
  parallel_merge_sort
  async_test
  bloom_filter
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} ${example}.cpp)
  target_link_libraries(tutorials-${example} ${Boost_REGEX_LIBRARY})
endforeach(example)
