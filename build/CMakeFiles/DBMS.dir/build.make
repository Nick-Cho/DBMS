# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nickcho/Desktop/Coding/DBMS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nickcho/Desktop/Coding/DBMS/build

# Include any dependencies generated for this target.
include CMakeFiles/DBMS.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DBMS.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DBMS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DBMS.dir/flags.make

CMakeFiles/DBMS.dir/src/main.cpp.o: CMakeFiles/DBMS.dir/flags.make
CMakeFiles/DBMS.dir/src/main.cpp.o: /Users/nickcho/Desktop/Coding/DBMS/src/main.cpp
CMakeFiles/DBMS.dir/src/main.cpp.o: CMakeFiles/DBMS.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nickcho/Desktop/Coding/DBMS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DBMS.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DBMS.dir/src/main.cpp.o -MF CMakeFiles/DBMS.dir/src/main.cpp.o.d -o CMakeFiles/DBMS.dir/src/main.cpp.o -c /Users/nickcho/Desktop/Coding/DBMS/src/main.cpp

CMakeFiles/DBMS.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DBMS.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nickcho/Desktop/Coding/DBMS/src/main.cpp > CMakeFiles/DBMS.dir/src/main.cpp.i

CMakeFiles/DBMS.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DBMS.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nickcho/Desktop/Coding/DBMS/src/main.cpp -o CMakeFiles/DBMS.dir/src/main.cpp.s

# Object files for target DBMS
DBMS_OBJECTS = \
"CMakeFiles/DBMS.dir/src/main.cpp.o"

# External object files for target DBMS
DBMS_EXTERNAL_OBJECTS =

DBMS: CMakeFiles/DBMS.dir/src/main.cpp.o
DBMS: CMakeFiles/DBMS.dir/build.make
DBMS: libstatement.a
DBMS: libinputBuffer.a
DBMS: librow.a
DBMS: libtable.a
DBMS: libpager.a
DBMS: libcursor.a
DBMS: libnode.a
DBMS: librow.a
DBMS: libtable.a
DBMS: libpager.a
DBMS: libcursor.a
DBMS: libnode.a
DBMS: CMakeFiles/DBMS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nickcho/Desktop/Coding/DBMS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DBMS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DBMS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DBMS.dir/build: DBMS
.PHONY : CMakeFiles/DBMS.dir/build

CMakeFiles/DBMS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DBMS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DBMS.dir/clean

CMakeFiles/DBMS.dir/depend:
	cd /Users/nickcho/Desktop/Coding/DBMS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nickcho/Desktop/Coding/DBMS /Users/nickcho/Desktop/Coding/DBMS /Users/nickcho/Desktop/Coding/DBMS/build /Users/nickcho/Desktop/Coding/DBMS/build /Users/nickcho/Desktop/Coding/DBMS/build/CMakeFiles/DBMS.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DBMS.dir/depend

