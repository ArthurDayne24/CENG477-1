# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /opt/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sbk/CLionProjects/ceng477

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sbk/CLionProjects/ceng477/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ceng477.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ceng477.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ceng477.dir/flags.make

CMakeFiles/ceng477.dir/parser.cpp.o: CMakeFiles/ceng477.dir/flags.make
CMakeFiles/ceng477.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ceng477.dir/parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceng477.dir/parser.cpp.o -c /home/sbk/CLionProjects/ceng477/parser.cpp

CMakeFiles/ceng477.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceng477.dir/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sbk/CLionProjects/ceng477/parser.cpp > CMakeFiles/ceng477.dir/parser.cpp.i

CMakeFiles/ceng477.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceng477.dir/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sbk/CLionProjects/ceng477/parser.cpp -o CMakeFiles/ceng477.dir/parser.cpp.s

CMakeFiles/ceng477.dir/parser.cpp.o.requires:

.PHONY : CMakeFiles/ceng477.dir/parser.cpp.o.requires

CMakeFiles/ceng477.dir/parser.cpp.o.provides: CMakeFiles/ceng477.dir/parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/ceng477.dir/build.make CMakeFiles/ceng477.dir/parser.cpp.o.provides.build
.PHONY : CMakeFiles/ceng477.dir/parser.cpp.o.provides

CMakeFiles/ceng477.dir/parser.cpp.o.provides.build: CMakeFiles/ceng477.dir/parser.cpp.o


CMakeFiles/ceng477.dir/ppm.cpp.o: CMakeFiles/ceng477.dir/flags.make
CMakeFiles/ceng477.dir/ppm.cpp.o: ../ppm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ceng477.dir/ppm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceng477.dir/ppm.cpp.o -c /home/sbk/CLionProjects/ceng477/ppm.cpp

CMakeFiles/ceng477.dir/ppm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceng477.dir/ppm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sbk/CLionProjects/ceng477/ppm.cpp > CMakeFiles/ceng477.dir/ppm.cpp.i

CMakeFiles/ceng477.dir/ppm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceng477.dir/ppm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sbk/CLionProjects/ceng477/ppm.cpp -o CMakeFiles/ceng477.dir/ppm.cpp.s

CMakeFiles/ceng477.dir/ppm.cpp.o.requires:

.PHONY : CMakeFiles/ceng477.dir/ppm.cpp.o.requires

CMakeFiles/ceng477.dir/ppm.cpp.o.provides: CMakeFiles/ceng477.dir/ppm.cpp.o.requires
	$(MAKE) -f CMakeFiles/ceng477.dir/build.make CMakeFiles/ceng477.dir/ppm.cpp.o.provides.build
.PHONY : CMakeFiles/ceng477.dir/ppm.cpp.o.provides

CMakeFiles/ceng477.dir/ppm.cpp.o.provides.build: CMakeFiles/ceng477.dir/ppm.cpp.o


CMakeFiles/ceng477.dir/tinyxml2.cpp.o: CMakeFiles/ceng477.dir/flags.make
CMakeFiles/ceng477.dir/tinyxml2.cpp.o: ../tinyxml2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ceng477.dir/tinyxml2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceng477.dir/tinyxml2.cpp.o -c /home/sbk/CLionProjects/ceng477/tinyxml2.cpp

CMakeFiles/ceng477.dir/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceng477.dir/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sbk/CLionProjects/ceng477/tinyxml2.cpp > CMakeFiles/ceng477.dir/tinyxml2.cpp.i

CMakeFiles/ceng477.dir/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceng477.dir/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sbk/CLionProjects/ceng477/tinyxml2.cpp -o CMakeFiles/ceng477.dir/tinyxml2.cpp.s

CMakeFiles/ceng477.dir/tinyxml2.cpp.o.requires:

.PHONY : CMakeFiles/ceng477.dir/tinyxml2.cpp.o.requires

CMakeFiles/ceng477.dir/tinyxml2.cpp.o.provides: CMakeFiles/ceng477.dir/tinyxml2.cpp.o.requires
	$(MAKE) -f CMakeFiles/ceng477.dir/build.make CMakeFiles/ceng477.dir/tinyxml2.cpp.o.provides.build
.PHONY : CMakeFiles/ceng477.dir/tinyxml2.cpp.o.provides

CMakeFiles/ceng477.dir/tinyxml2.cpp.o.provides.build: CMakeFiles/ceng477.dir/tinyxml2.cpp.o


CMakeFiles/ceng477.dir/raytracer.cpp.o: CMakeFiles/ceng477.dir/flags.make
CMakeFiles/ceng477.dir/raytracer.cpp.o: ../raytracer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ceng477.dir/raytracer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceng477.dir/raytracer.cpp.o -c /home/sbk/CLionProjects/ceng477/raytracer.cpp

CMakeFiles/ceng477.dir/raytracer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceng477.dir/raytracer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sbk/CLionProjects/ceng477/raytracer.cpp > CMakeFiles/ceng477.dir/raytracer.cpp.i

CMakeFiles/ceng477.dir/raytracer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceng477.dir/raytracer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sbk/CLionProjects/ceng477/raytracer.cpp -o CMakeFiles/ceng477.dir/raytracer.cpp.s

CMakeFiles/ceng477.dir/raytracer.cpp.o.requires:

.PHONY : CMakeFiles/ceng477.dir/raytracer.cpp.o.requires

CMakeFiles/ceng477.dir/raytracer.cpp.o.provides: CMakeFiles/ceng477.dir/raytracer.cpp.o.requires
	$(MAKE) -f CMakeFiles/ceng477.dir/build.make CMakeFiles/ceng477.dir/raytracer.cpp.o.provides.build
.PHONY : CMakeFiles/ceng477.dir/raytracer.cpp.o.provides

CMakeFiles/ceng477.dir/raytracer.cpp.o.provides.build: CMakeFiles/ceng477.dir/raytracer.cpp.o


# Object files for target ceng477
ceng477_OBJECTS = \
"CMakeFiles/ceng477.dir/parser.cpp.o" \
"CMakeFiles/ceng477.dir/ppm.cpp.o" \
"CMakeFiles/ceng477.dir/tinyxml2.cpp.o" \
"CMakeFiles/ceng477.dir/raytracer.cpp.o"

# External object files for target ceng477
ceng477_EXTERNAL_OBJECTS =

ceng477: CMakeFiles/ceng477.dir/parser.cpp.o
ceng477: CMakeFiles/ceng477.dir/ppm.cpp.o
ceng477: CMakeFiles/ceng477.dir/tinyxml2.cpp.o
ceng477: CMakeFiles/ceng477.dir/raytracer.cpp.o
ceng477: CMakeFiles/ceng477.dir/build.make
ceng477: CMakeFiles/ceng477.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ceng477"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ceng477.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ceng477.dir/build: ceng477

.PHONY : CMakeFiles/ceng477.dir/build

CMakeFiles/ceng477.dir/requires: CMakeFiles/ceng477.dir/parser.cpp.o.requires
CMakeFiles/ceng477.dir/requires: CMakeFiles/ceng477.dir/ppm.cpp.o.requires
CMakeFiles/ceng477.dir/requires: CMakeFiles/ceng477.dir/tinyxml2.cpp.o.requires
CMakeFiles/ceng477.dir/requires: CMakeFiles/ceng477.dir/raytracer.cpp.o.requires

.PHONY : CMakeFiles/ceng477.dir/requires

CMakeFiles/ceng477.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ceng477.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ceng477.dir/clean

CMakeFiles/ceng477.dir/depend:
	cd /home/sbk/CLionProjects/ceng477/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sbk/CLionProjects/ceng477 /home/sbk/CLionProjects/ceng477 /home/sbk/CLionProjects/ceng477/cmake-build-debug /home/sbk/CLionProjects/ceng477/cmake-build-debug /home/sbk/CLionProjects/ceng477/cmake-build-debug/CMakeFiles/ceng477.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ceng477.dir/depend

