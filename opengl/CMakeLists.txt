cmake_minimum_required(VERSION 2.8)
project(opengl)
include_directories(${opengl_SOURCE_DIR})

find_package(Qt 4.7 COMPONENTS Core Gui OpenGL Svg)
include_directories(${QT_INCLUDE_DIR})
qt4_wrap_cpp(opengl_MOC GlynWidget.h)
qt4_add_resources(opengl_RES Glyn.qrc)
add_executable(opengl_example main.cpp GlynWidget.cpp GlynWidget.h ${opengl_MOC} ${opengl_RES})
target_link_libraries(opengl_example
  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${QT_QTSVG_LIBRARY})
