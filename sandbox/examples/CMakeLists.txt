set(EXAMPLES
  #codecvt_test
  wstring_encoding
  endianness
  resolver
  mergesort
  quicksort
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

include_directories(TinyThread/include)
include_directories(TinyThread/include/TinyThread)
add_executable(sandbox-ThreadPool
  TinyThread/source/Timer
  TinyThread/source/Tinythread
  SK/ThreadPool.cpp
  SK/ThreadPool.h
  SK/ThreadSafeQueue.h
  SK/ThreadPoolTest.cpp)
target_link_libraries(sandbox-ThreadPool
  ${CMAKE_THREAD_LIBS_INIT}
  )
