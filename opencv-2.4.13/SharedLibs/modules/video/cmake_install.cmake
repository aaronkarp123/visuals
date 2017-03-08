# Install script for directory: /Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/modules/video

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libs" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_video.2.4.13.dylib"
    "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_video.2.4.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.2.4.13.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.2.4.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libopencv_video.2.4.dylib"
        -change "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_core.2.4.dylib" "libopencv_core.2.4.dylib"
        -change "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_imgproc.2.4.dylib" "libopencv_imgproc.2.4.dylib"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/usr/local/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_video.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libopencv_video.2.4.dylib"
      -change "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_core.2.4.dylib" "libopencv_core.2.4.dylib"
      -change "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/SharedLibs/lib/libopencv_imgproc.2.4.dylib" "libopencv_imgproc.2.4.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopencv_video.dylib")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2" TYPE FILE FILES "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/modules/video/include/opencv2/video.hpp")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/video" TYPE FILE FILES "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/modules/video/include/opencv2/video/background_segm.hpp")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/video" TYPE FILE FILES "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/modules/video/include/opencv2/video/tracking.hpp")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/video" TYPE FILE FILES "/Users/aaronkarp/Documents/Research/Summer2016/GraphingPad/opencv-2.4.13/modules/video/include/opencv2/video/video.hpp")
endif()

