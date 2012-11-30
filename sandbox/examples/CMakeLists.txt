set(EXAMPLES
  wstring_encoding
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} ${example}.cpp)
  target_link_libraries(tutorials-${example}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_TIMER_LIBRARY}
    ${Boost_LOCALE_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )
endforeach(example)
