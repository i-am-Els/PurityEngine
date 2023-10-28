# Install script for directory: C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Police_n_Thief")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2023.2.1/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/global.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/input.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/input_def.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/log.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/entity.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/transform.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/vector2.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/pnt.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/renderer.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/eglew.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/glew.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/glxew.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/wglew.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/glfw3.h;C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include/glfw3native.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/shared/include" TYPE FILE FILES
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/global.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/input.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/input_def.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/log.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/math/entity.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/math/transform.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/math/vector2.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/pnt.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/include/renderer/renderer.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLEW/include/eglew.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLEW/include/glew.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLEW/include/glxew.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLEW/include/wglew.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLFW/include/glfw3.h"
    "C:/Users/Eniola Olawale/Documents/Els/Dev/Git/Police_n_Thief/PnT/vendors/GLFW/include/glfw3native.h"
    )
endif()

