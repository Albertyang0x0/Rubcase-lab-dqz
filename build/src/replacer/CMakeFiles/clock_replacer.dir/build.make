# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/albert/rucbase-lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/albert/rucbase-lab/build

# Include any dependencies generated for this target.
include src/replacer/CMakeFiles/clock_replacer.dir/depend.make

# Include the progress variables for this target.
include src/replacer/CMakeFiles/clock_replacer.dir/progress.make

# Include the compile flags for this target's objects.
include src/replacer/CMakeFiles/clock_replacer.dir/flags.make

src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o: src/replacer/CMakeFiles/clock_replacer.dir/flags.make
src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o: ../src/replacer/lru_replacer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o -c /home/albert/rucbase-lab/src/replacer/lru_replacer.cpp

src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clock_replacer.dir/lru_replacer.cpp.i"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albert/rucbase-lab/src/replacer/lru_replacer.cpp > CMakeFiles/clock_replacer.dir/lru_replacer.cpp.i

src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clock_replacer.dir/lru_replacer.cpp.s"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albert/rucbase-lab/src/replacer/lru_replacer.cpp -o CMakeFiles/clock_replacer.dir/lru_replacer.cpp.s

src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o: src/replacer/CMakeFiles/clock_replacer.dir/flags.make
src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o: ../src/replacer/clock_replacer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o -c /home/albert/rucbase-lab/src/replacer/clock_replacer.cpp

src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clock_replacer.dir/clock_replacer.cpp.i"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albert/rucbase-lab/src/replacer/clock_replacer.cpp > CMakeFiles/clock_replacer.dir/clock_replacer.cpp.i

src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clock_replacer.dir/clock_replacer.cpp.s"
	cd /home/albert/rucbase-lab/build/src/replacer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albert/rucbase-lab/src/replacer/clock_replacer.cpp -o CMakeFiles/clock_replacer.dir/clock_replacer.cpp.s

# Object files for target clock_replacer
clock_replacer_OBJECTS = \
"CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o" \
"CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o"

# External object files for target clock_replacer
clock_replacer_EXTERNAL_OBJECTS =

lib/libclock_replacer.a: src/replacer/CMakeFiles/clock_replacer.dir/lru_replacer.cpp.o
lib/libclock_replacer.a: src/replacer/CMakeFiles/clock_replacer.dir/clock_replacer.cpp.o
lib/libclock_replacer.a: src/replacer/CMakeFiles/clock_replacer.dir/build.make
lib/libclock_replacer.a: src/replacer/CMakeFiles/clock_replacer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../../lib/libclock_replacer.a"
	cd /home/albert/rucbase-lab/build/src/replacer && $(CMAKE_COMMAND) -P CMakeFiles/clock_replacer.dir/cmake_clean_target.cmake
	cd /home/albert/rucbase-lab/build/src/replacer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clock_replacer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/replacer/CMakeFiles/clock_replacer.dir/build: lib/libclock_replacer.a

.PHONY : src/replacer/CMakeFiles/clock_replacer.dir/build

src/replacer/CMakeFiles/clock_replacer.dir/clean:
	cd /home/albert/rucbase-lab/build/src/replacer && $(CMAKE_COMMAND) -P CMakeFiles/clock_replacer.dir/cmake_clean.cmake
.PHONY : src/replacer/CMakeFiles/clock_replacer.dir/clean

src/replacer/CMakeFiles/clock_replacer.dir/depend:
	cd /home/albert/rucbase-lab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/albert/rucbase-lab /home/albert/rucbase-lab/src/replacer /home/albert/rucbase-lab/build /home/albert/rucbase-lab/build/src/replacer /home/albert/rucbase-lab/build/src/replacer/CMakeFiles/clock_replacer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/replacer/CMakeFiles/clock_replacer.dir/depend
