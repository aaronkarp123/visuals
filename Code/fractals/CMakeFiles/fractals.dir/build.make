# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aaronkarp/Documents/visual/Code/fractals

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aaronkarp/Documents/visual/Code/fractals

# Include any dependencies generated for this target.
include CMakeFiles/fractals.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fractals.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fractals.dir/flags.make

CMakeFiles/fractals.dir/fractals.cpp.o: CMakeFiles/fractals.dir/flags.make
CMakeFiles/fractals.dir/fractals.cpp.o: fractals.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aaronkarp/Documents/visual/Code/fractals/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fractals.dir/fractals.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fractals.dir/fractals.cpp.o -c /Users/aaronkarp/Documents/visual/Code/fractals/fractals.cpp

CMakeFiles/fractals.dir/fractals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fractals.dir/fractals.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aaronkarp/Documents/visual/Code/fractals/fractals.cpp > CMakeFiles/fractals.dir/fractals.cpp.i

CMakeFiles/fractals.dir/fractals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fractals.dir/fractals.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aaronkarp/Documents/visual/Code/fractals/fractals.cpp -o CMakeFiles/fractals.dir/fractals.cpp.s

CMakeFiles/fractals.dir/fractals.cpp.o.requires:

.PHONY : CMakeFiles/fractals.dir/fractals.cpp.o.requires

CMakeFiles/fractals.dir/fractals.cpp.o.provides: CMakeFiles/fractals.dir/fractals.cpp.o.requires
	$(MAKE) -f CMakeFiles/fractals.dir/build.make CMakeFiles/fractals.dir/fractals.cpp.o.provides.build
.PHONY : CMakeFiles/fractals.dir/fractals.cpp.o.provides

CMakeFiles/fractals.dir/fractals.cpp.o.provides.build: CMakeFiles/fractals.dir/fractals.cpp.o


# Object files for target fractals
fractals_OBJECTS = \
"CMakeFiles/fractals.dir/fractals.cpp.o"

# External object files for target fractals
fractals_EXTERNAL_OBJECTS =

fractals: CMakeFiles/fractals.dir/fractals.cpp.o
fractals: CMakeFiles/fractals.dir/build.make
fractals: /usr/local/lib/libopencv_videostab.2.4.13.dylib
fractals: /usr/local/lib/libopencv_ts.a
fractals: /usr/local/lib/libopencv_superres.2.4.13.dylib
fractals: /usr/local/lib/libopencv_stitching.2.4.13.dylib
fractals: /usr/local/lib/libopencv_contrib.2.4.13.dylib
fractals: /usr/local/lib/libopencv_nonfree.2.4.13.dylib
fractals: /usr/local/lib/libopencv_ocl.2.4.13.dylib
fractals: /usr/local/lib/libopencv_gpu.2.4.13.dylib
fractals: /usr/local/lib/libopencv_photo.2.4.13.dylib
fractals: /usr/local/lib/libopencv_objdetect.2.4.13.dylib
fractals: /usr/local/lib/libopencv_legacy.2.4.13.dylib
fractals: /usr/local/lib/libopencv_video.2.4.13.dylib
fractals: /usr/local/lib/libopencv_ml.2.4.13.dylib
fractals: /usr/local/lib/libopencv_calib3d.2.4.13.dylib
fractals: /usr/local/lib/libopencv_features2d.2.4.13.dylib
fractals: /usr/local/lib/libopencv_highgui.2.4.13.dylib
fractals: /usr/local/lib/libopencv_imgproc.2.4.13.dylib
fractals: /usr/local/lib/libopencv_flann.2.4.13.dylib
fractals: /usr/local/lib/libopencv_core.2.4.13.dylib
fractals: CMakeFiles/fractals.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aaronkarp/Documents/visual/Code/fractals/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fractals"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fractals.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fractals.dir/build: fractals

.PHONY : CMakeFiles/fractals.dir/build

CMakeFiles/fractals.dir/requires: CMakeFiles/fractals.dir/fractals.cpp.o.requires

.PHONY : CMakeFiles/fractals.dir/requires

CMakeFiles/fractals.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fractals.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fractals.dir/clean

CMakeFiles/fractals.dir/depend:
	cd /Users/aaronkarp/Documents/visual/Code/fractals && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aaronkarp/Documents/visual/Code/fractals /Users/aaronkarp/Documents/visual/Code/fractals /Users/aaronkarp/Documents/visual/Code/fractals /Users/aaronkarp/Documents/visual/Code/fractals /Users/aaronkarp/Documents/visual/Code/fractals/CMakeFiles/fractals.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fractals.dir/depend

