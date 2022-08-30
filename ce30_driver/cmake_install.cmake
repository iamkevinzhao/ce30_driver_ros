# Install script for directory: /home/jose/Programas/Benewake/ce30_driver/ce30_driver

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xshlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libce30_driver.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/libce30_driver.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libce30_driver.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xshlibx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/ce30_driver/utils.h;/usr/local/include/ce30_driver/udp_socket.h;/usr/local/include/ce30_driver/packet.h;/usr/local/include/ce30_driver/export.h;/usr/local/include/ce30_driver/ce30_driver.h;/usr/local/include/ce30_driver/data_types.h;/usr/local/include/ce30_driver/udp_server.h;/usr/local/include/ce30_driver/channel_type_widgets.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/ce30_driver" TYPE FILE FILES
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/utils.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/udp_socket.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/packet.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/export.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/ce30_driver.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/data_types.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/udp_server.h"
    "/home/jose/Programas/Benewake/ce30_driver/ce30_driver/channel_type_widgets.h"
    )
endif()

