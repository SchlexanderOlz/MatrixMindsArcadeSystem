# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Code/MatrixMindsArcadeSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Code/MatrixMindsArcadeSystem

# Include any dependencies generated for this target.
include CMakeFiles/matrix_minds.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matrix_minds.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrix_minds.dir/flags.make

CMakeFiles/matrix_minds.dir/src/main.cpp.o: CMakeFiles/matrix_minds.dir/flags.make
CMakeFiles/matrix_minds.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Code/MatrixMindsArcadeSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matrix_minds.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matrix_minds.dir/src/main.cpp.o -c /home/pi/Code/MatrixMindsArcadeSystem/src/main.cpp

CMakeFiles/matrix_minds.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrix_minds.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Code/MatrixMindsArcadeSystem/src/main.cpp > CMakeFiles/matrix_minds.dir/src/main.cpp.i

CMakeFiles/matrix_minds.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrix_minds.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Code/MatrixMindsArcadeSystem/src/main.cpp -o CMakeFiles/matrix_minds.dir/src/main.cpp.s

# Object files for target matrix_minds
matrix_minds_OBJECTS = \
"CMakeFiles/matrix_minds.dir/src/main.cpp.o"

# External object files for target matrix_minds
matrix_minds_EXTERNAL_OBJECTS =

matrix_minds: CMakeFiles/matrix_minds.dir/src/main.cpp.o
matrix_minds: CMakeFiles/matrix_minds.dir/build.make
matrix_minds: CMakeFiles/matrix_minds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Code/MatrixMindsArcadeSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matrix_minds"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrix_minds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrix_minds.dir/build: matrix_minds

.PHONY : CMakeFiles/matrix_minds.dir/build

CMakeFiles/matrix_minds.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrix_minds.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrix_minds.dir/clean

CMakeFiles/matrix_minds.dir/depend:
	cd /home/pi/Code/MatrixMindsArcadeSystem && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Code/MatrixMindsArcadeSystem /home/pi/Code/MatrixMindsArcadeSystem /home/pi/Code/MatrixMindsArcadeSystem /home/pi/Code/MatrixMindsArcadeSystem /home/pi/Code/MatrixMindsArcadeSystem/CMakeFiles/matrix_minds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrix_minds.dir/depend
