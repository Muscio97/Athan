# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2016.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2016.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS\cmake-build-debug

# Utility rule file for flash.

# Include the progress variables for this target.
include CMakeFiles/flash.dir/progress.make

CMakeFiles/flash:
	stty 1200 -F /dev/ttyACM0
	"C:\Program Files (x86)\Bossa\bossac.exe" -p ttyACM0 -U false -e -w -v -b gas.bin -R

flash: CMakeFiles/flash
flash: CMakeFiles/flash.dir/build.make

.PHONY : flash

# Rule to build all files generated by this target.
CMakeFiles/flash.dir/build: flash

.PHONY : CMakeFiles/flash.dir/build

CMakeFiles/flash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\flash.dir\cmake_clean.cmake
.PHONY : CMakeFiles/flash.dir/clean

CMakeFiles/flash.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS\cmake-build-debug C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS\cmake-build-debug C:\Users\MuscioCraft\ClionProjects\R2D2-2017\modules\GAS\cmake-build-debug\CMakeFiles\flash.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flash.dir/depend

