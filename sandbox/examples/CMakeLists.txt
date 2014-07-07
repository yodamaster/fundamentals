set(EXAMPLES
  #codecvt_test
  wstring_encoding
  #endianness
  resolver
  daytime_client
  daytime_server
  mergesort
  quicksort
  graph
  make_heap
  binary_heap
  uri_parser
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

include_directories(.)
include_directories(TinyThread/include)
include_directories(TinyThread/include/TinyThread)
add_executable(sandbox-ThreadPool
  TinyThread/source/Timer.cpp
  TinyThread/source/Tinythread.cpp
  TinyThread/include/TinyThread/Fast_mutex.h
  TinyThread/include/TinyThread/Timer.h
  TinyThread/include/TinyThread/Tinythread.h
  SK/Concurrency/Task.h
  SK/Concurrency/ThreadSafeQueue.h
  SK/Concurrency/WorkStealingQueue.h
  SK/Concurrency/ThreadPool.h
  SK/Concurrency/WorkStealingThreadPool.h
  SK/ThreadPoolTest.cpp)
target_link_libraries(sandbox-ThreadPool
  ${CMAKE_THREAD_LIBS_INIT}
  )

#add_executable(sandbox-qtnetwork-client
#  qtnetwork/client.h
#  qtnetwork/client.cpp
#  qtnetwork/main.cpp
#  )
#
#qt5_use_modules(sandbox-qtnetwork-client Core Network)
#qt5_use_modules(sandbox-qtnetwork-httpwindow Core Widgets Network)
