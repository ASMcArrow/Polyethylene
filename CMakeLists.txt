CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

PROJECT(Polyethylene)

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(Geant4 REQUIRED ui_all vis_all)
IF(NOT Geant4_FOUND)
    MESSAGE(FATAL_ERROR "Geant4 not found!")
ENDIF(NOT Geant4_FOUND)


#FIND_PACKAGE(Qt4 REQUIRED)
#IF(NOT QT4_FOUND)
#    MESSAGE(FATAL_ERROR "Qt4 not found!")

#SET(QT_USE_QTOPENGL TRUE)
#SET(QT_USE_QTGUI TRUE)

#INCLUDE(${QT_USE_FILE})
INCLUDE(${Geant4_USE_FILE})

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR})


#SET(CopperGUI_SRCS
#    GUI/CopperWindow.cpp
#    External/qcustomplot.cpp
#)

#QT4_WRAP_CPP(QT_MOC_SRCS
#    GUI/CopperWindow.h
#    External/qcustomplot.h
#    Calculation/Geant4.hh
#    Calculation/Actions/CopperEventAction.hh
#)

#QT4_WRAP_UI(QT_UIC_SRCS
#    GUI/CopperWindow.ui
#)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(Polyethylene main.cc ${sources} ${headers})
target_link_libraries(Polyethylene ${Geant4_LIBRARIES})




