# Install script for directory: /home/bep/workspace/reporter_messages

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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsepro-reporter-messagesx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/kecontrolapplication/application/control/config/sepro-reporter-messages.cfg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/kecontrolapplication/application/control/config" TYPE FILE FILES "/home/bep/workspace/reporter_messages/resources/sepro-reporter-messages.cfg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsepro-reporter-messagesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/kecontrolapplication/application/control/ccontrol" TYPE SHARED_LIBRARY FILES "/home/bep/workspace/reporter_messages/bin/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug")
  if(EXISTS "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so.0.0.1.RC-0.dev.debug")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsepro-reporter-messagesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/kecontrolapplication/application/control/ccontrol" TYPE SHARED_LIBRARY FILES "/home/bep/workspace/reporter_messages/bin/libsepro-reporter-messages.so")
  if(EXISTS "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/opt/kecontrolapplication/application/control/ccontrol/libsepro-reporter-messages.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/doc/sepro-reporter-messages/copyright")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/share/doc/sepro-reporter-messages" TYPE FILE FILES "/home/bep/workspace/reporter_messages/DEBIAN/copyright")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/bep/workspace/reporter_messages/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
