# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/cmake-3.15.7-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.15.7-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/TINY

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/TINY/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TINY.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TINY.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TINY.dir/flags.make

CMakeFiles/TINY.dir/main.c.o: CMakeFiles/TINY.dir/flags.make
CMakeFiles/TINY.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/TINY/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TINY.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TINY.dir/main.c.o   -c /mnt/d/TINY/main.c

CMakeFiles/TINY.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TINY.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/TINY/main.c > CMakeFiles/TINY.dir/main.c.i

CMakeFiles/TINY.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TINY.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/TINY/main.c -o CMakeFiles/TINY.dir/main.c.s

# Object files for target TINY
TINY_OBJECTS = \
"CMakeFiles/TINY.dir/main.c.o"

# External object files for target TINY
TINY_EXTERNAL_OBJECTS =

TINY: CMakeFiles/TINY.dir/main.c.o
TINY: CMakeFiles/TINY.dir/build.make
TINY: CMakeFiles/TINY.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/TINY/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TINY"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TINY.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TINY.dir/build: TINY

.PHONY : CMakeFiles/TINY.dir/build

CMakeFiles/TINY.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TINY.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TINY.dir/clean

CMakeFiles/TINY.dir/depend:
	cd /mnt/d/TINY/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/TINY /mnt/d/TINY /mnt/d/TINY/cmake-build-debug /mnt/d/TINY/cmake-build-debug /mnt/d/TINY/cmake-build-debug/CMakeFiles/TINY.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TINY.dir/depend

