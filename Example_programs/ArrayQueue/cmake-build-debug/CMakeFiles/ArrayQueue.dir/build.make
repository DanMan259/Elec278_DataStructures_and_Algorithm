# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniyal/school/Elec278/testing/ArrayQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ArrayQueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ArrayQueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ArrayQueue.dir/flags.make

CMakeFiles/ArrayQueue.dir/main.c.o: CMakeFiles/ArrayQueue.dir/flags.make
CMakeFiles/ArrayQueue.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ArrayQueue.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ArrayQueue.dir/main.c.o   -c /home/daniyal/school/Elec278/testing/ArrayQueue/main.c

CMakeFiles/ArrayQueue.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ArrayQueue.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/daniyal/school/Elec278/testing/ArrayQueue/main.c > CMakeFiles/ArrayQueue.dir/main.c.i

CMakeFiles/ArrayQueue.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ArrayQueue.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/daniyal/school/Elec278/testing/ArrayQueue/main.c -o CMakeFiles/ArrayQueue.dir/main.c.s

# Object files for target ArrayQueue
ArrayQueue_OBJECTS = \
"CMakeFiles/ArrayQueue.dir/main.c.o"

# External object files for target ArrayQueue
ArrayQueue_EXTERNAL_OBJECTS =

ArrayQueue: CMakeFiles/ArrayQueue.dir/main.c.o
ArrayQueue: CMakeFiles/ArrayQueue.dir/build.make
ArrayQueue: CMakeFiles/ArrayQueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ArrayQueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ArrayQueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ArrayQueue.dir/build: ArrayQueue

.PHONY : CMakeFiles/ArrayQueue.dir/build

CMakeFiles/ArrayQueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ArrayQueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ArrayQueue.dir/clean

CMakeFiles/ArrayQueue.dir/depend:
	cd /home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniyal/school/Elec278/testing/ArrayQueue /home/daniyal/school/Elec278/testing/ArrayQueue /home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug /home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug /home/daniyal/school/Elec278/testing/ArrayQueue/cmake-build-debug/CMakeFiles/ArrayQueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ArrayQueue.dir/depend
