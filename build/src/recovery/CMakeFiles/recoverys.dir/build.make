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
include src/recovery/CMakeFiles/recoverys.dir/depend.make

# Include the progress variables for this target.
include src/recovery/CMakeFiles/recoverys.dir/progress.make

# Include the compile flags for this target's objects.
include src/recovery/CMakeFiles/recoverys.dir/flags.make

src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.o: src/recovery/CMakeFiles/recoverys.dir/flags.make
src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.o: ../src/recovery/log_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.o"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/recoverys.dir/log_manager.cpp.o -c /home/albert/rucbase-lab/src/recovery/log_manager.cpp

src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recoverys.dir/log_manager.cpp.i"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albert/rucbase-lab/src/recovery/log_manager.cpp > CMakeFiles/recoverys.dir/log_manager.cpp.i

src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recoverys.dir/log_manager.cpp.s"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albert/rucbase-lab/src/recovery/log_manager.cpp -o CMakeFiles/recoverys.dir/log_manager.cpp.s

src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.o: src/recovery/CMakeFiles/recoverys.dir/flags.make
src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.o: ../src/recovery/log_recovery.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.o"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/recoverys.dir/log_recovery.cpp.o -c /home/albert/rucbase-lab/src/recovery/log_recovery.cpp

src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recoverys.dir/log_recovery.cpp.i"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albert/rucbase-lab/src/recovery/log_recovery.cpp > CMakeFiles/recoverys.dir/log_recovery.cpp.i

src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recoverys.dir/log_recovery.cpp.s"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albert/rucbase-lab/src/recovery/log_recovery.cpp -o CMakeFiles/recoverys.dir/log_recovery.cpp.s

src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.o: src/recovery/CMakeFiles/recoverys.dir/flags.make
src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.o: ../src/recovery/checkpoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.o"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/recoverys.dir/checkpoint.cpp.o -c /home/albert/rucbase-lab/src/recovery/checkpoint.cpp

src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recoverys.dir/checkpoint.cpp.i"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albert/rucbase-lab/src/recovery/checkpoint.cpp > CMakeFiles/recoverys.dir/checkpoint.cpp.i

src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recoverys.dir/checkpoint.cpp.s"
	cd /home/albert/rucbase-lab/build/src/recovery && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albert/rucbase-lab/src/recovery/checkpoint.cpp -o CMakeFiles/recoverys.dir/checkpoint.cpp.s

# Object files for target recoverys
recoverys_OBJECTS = \
"CMakeFiles/recoverys.dir/log_manager.cpp.o" \
"CMakeFiles/recoverys.dir/log_recovery.cpp.o" \
"CMakeFiles/recoverys.dir/checkpoint.cpp.o"

# External object files for target recoverys
recoverys_EXTERNAL_OBJECTS =

lib/librecoverys.so: src/recovery/CMakeFiles/recoverys.dir/log_manager.cpp.o
lib/librecoverys.so: src/recovery/CMakeFiles/recoverys.dir/log_recovery.cpp.o
lib/librecoverys.so: src/recovery/CMakeFiles/recoverys.dir/checkpoint.cpp.o
lib/librecoverys.so: src/recovery/CMakeFiles/recoverys.dir/build.make
lib/librecoverys.so: src/recovery/CMakeFiles/recoverys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/albert/rucbase-lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../../lib/librecoverys.so"
	cd /home/albert/rucbase-lab/build/src/recovery && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/recoverys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/recovery/CMakeFiles/recoverys.dir/build: lib/librecoverys.so

.PHONY : src/recovery/CMakeFiles/recoverys.dir/build

src/recovery/CMakeFiles/recoverys.dir/clean:
	cd /home/albert/rucbase-lab/build/src/recovery && $(CMAKE_COMMAND) -P CMakeFiles/recoverys.dir/cmake_clean.cmake
.PHONY : src/recovery/CMakeFiles/recoverys.dir/clean

src/recovery/CMakeFiles/recoverys.dir/depend:
	cd /home/albert/rucbase-lab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/albert/rucbase-lab /home/albert/rucbase-lab/src/recovery /home/albert/rucbase-lab/build /home/albert/rucbase-lab/build/src/recovery /home/albert/rucbase-lab/build/src/recovery/CMakeFiles/recoverys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/recovery/CMakeFiles/recoverys.dir/depend
