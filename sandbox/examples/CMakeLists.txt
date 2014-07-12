set(EXAMPLES
  #codecvt_test
  wstring_encoding
  #endianness
  resolver
  daytime_client
  daytime_server
  mergesort
  quicksort
  #graph
  make_heap
  binary_heap
  uri_parser
  uri_parser_2
  )

foreach(example ${EXAMPLES})
  add_executable(sandbox-${example} ${example}.cpp)
  target_link_libraries(sandbox-${example}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_TIMER_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_LOCALE_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )
endforeach(example)
