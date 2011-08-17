find_package(Boost 1.46.0 COMPONENTS regex)
if (Boost_FOUND)
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTI_THREADED ON)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR " Unable to locate Boost.")
endif()

set(EXAMPLES
  boost_range_algorithm
  bloom_filter
  )

foreach(example ${EXAMPLES})
  add_executable(tutorials-${example} ${example}.cpp)
  target_link_libraries(tutorials-${example} ${Boost_REGEX_LIBRARY})
endforeach(example)
