cmake_minimum_required(VERSION 2.8)
project(CellCounter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(wxWidgets COMPONENTS core base gl REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

add_library(lib
    CellCounterApp.cpp
    CellCounterApp.h
    CellCounter.cpp
    CellCounter.h
    Defines.h
    OpenGLPanZoom.cpp
    OpenGLPanZoom.h)

add_executable(cellcounter CellCounterMain.cpp CellCounterMain.h)

include("${wxWidgets_USE_FILE}" )
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(cellcounter lib ${OPENGL_LIBRARIES} ${wxWidgets_LIBRARIES} ${OpenCV_LIBS})
