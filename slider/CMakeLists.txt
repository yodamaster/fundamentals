cmake_minimum_required(VERSION 2.8)
project(opengl)
include_directories(${opengl_SOURCE_DIR})

find_package(Qt 4.7 COMPONENTS Core Gui Svg)
include_directories(${QT_INCLUDE_DIR})
qt4_wrap_cpp(slider_MOC CustomSlider.h)
# qt4_add_resources(slider_RES Glyn.qrc)
add_executable(slider_example main.cpp CustomSlider.cpp CustomSlider.h ${slider_MOC})
target_link_libraries(slider_example
  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY})
