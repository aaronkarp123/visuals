How to Run Programs:

To set up environment:
http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/

CMakeLists.txt:
cmake_minimum_required(VERSION 2.8)
project( BlurImage )
find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( BlurImage BlurImage.cpp )
target_link_libraries( BlurImage ${OpenCV_LIBS} )

To Compile:
/Applications/CMake.app/Contents/bin/cmake .
make

To Run: 
./BlurImage image.jpg
