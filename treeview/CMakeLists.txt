cmake_minimum_required(VERSION 2.8)
project(treeview)
include_directories(${treeview_SOURCE_DIR})

find_package(Qt 4.7 COMPONENTS Core Gui Treeview Svg)
include_directories(${QT_INCLUDE_DIR})
add_executable(treeview_example
  main.cpp GlynView.cpp GlynModel.cpp GlynView.h GlynModel.h)
target_link_libraries(treeview_example
  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
