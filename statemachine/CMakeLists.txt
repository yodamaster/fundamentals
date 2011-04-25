cmake_minimum_required(VERSION 2.8)
project(statemachine)
include_directories(${statemachine_SOURCE_DIR})

find_package(Qt 4.7 COMPONENTS Core Gui)
include_directories(${QT_INCLUDE_DIR})
qt4_add_resources(statemachine_RES statemachine.qrc)
add_executable(statemachine_example main.cpp ${statemachine_RES})
target_link_libraries(statemachine_example
  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
