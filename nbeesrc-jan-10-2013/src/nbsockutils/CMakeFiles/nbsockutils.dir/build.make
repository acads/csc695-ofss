# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src

# Include any dependencies generated for this target.
include nbsockutils/CMakeFiles/nbsockutils.dir/depend.make

# Include the progress variables for this target.
include nbsockutils/CMakeFiles/nbsockutils.dir/progress.make

# Include the compile flags for this target's objects.
include nbsockutils/CMakeFiles/nbsockutils.dir/flags.make

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o: nbsockutils/CMakeFiles/nbsockutils.dir/flags.make
nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o: nbee/globals/debug.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o   -c /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/debug.c

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.i"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/debug.c > CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.i

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.s"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/debug.c -o CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.s

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.requires:
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.requires

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.provides: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.requires
	$(MAKE) -f nbsockutils/CMakeFiles/nbsockutils.dir/build.make nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.provides.build
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.provides

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.provides.build: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o: nbsockutils/CMakeFiles/nbsockutils.dir/flags.make
nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o: nbee/globals/utils.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o   -c /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/utils.c

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.i"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/utils.c > CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.i

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.s"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbee/globals/utils.c -o CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.s

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.requires:
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.requires

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.provides: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.requires
	$(MAKE) -f nbsockutils/CMakeFiles/nbsockutils.dir/build.make nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.provides.build
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.provides

nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.provides.build: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o: nbsockutils/CMakeFiles/nbsockutils.dir/flags.make
nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o: nbsockutils/sockutils.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nbsockutils.dir/sockutils.c.o   -c /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils/sockutils.c

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nbsockutils.dir/sockutils.c.i"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils/sockutils.c > CMakeFiles/nbsockutils.dir/sockutils.c.i

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nbsockutils.dir/sockutils.c.s"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils/sockutils.c -o CMakeFiles/nbsockutils.dir/sockutils.c.s

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.requires:
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.requires

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.provides: nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.requires
	$(MAKE) -f nbsockutils/CMakeFiles/nbsockutils.dir/build.make nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.provides.build
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.provides

nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.provides.build: nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o

# Object files for target nbsockutils
nbsockutils_OBJECTS = \
"CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o" \
"CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o" \
"CMakeFiles/nbsockutils.dir/sockutils.c.o"

# External object files for target nbsockutils
nbsockutils_EXTERNAL_OBJECTS =

nbsockutils/libnbsockutils.so: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o
nbsockutils/libnbsockutils.so: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o
nbsockutils/libnbsockutils.so: nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o
nbsockutils/libnbsockutils.so: nbsockutils/CMakeFiles/nbsockutils.dir/build.make
nbsockutils/libnbsockutils.so: nbsockutils/CMakeFiles/nbsockutils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libnbsockutils.so"
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nbsockutils.dir/link.txt --verbose=$(VERBOSE)
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && cp ./libnbsockutils* ../../bin/.

# Rule to build all files generated by this target.
nbsockutils/CMakeFiles/nbsockutils.dir/build: nbsockutils/libnbsockutils.so
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/build

nbsockutils/CMakeFiles/nbsockutils.dir/requires: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/debug.c.o.requires
nbsockutils/CMakeFiles/nbsockutils.dir/requires: nbsockutils/CMakeFiles/nbsockutils.dir/__/nbee/globals/utils.c.o.requires
nbsockutils/CMakeFiles/nbsockutils.dir/requires: nbsockutils/CMakeFiles/nbsockutils.dir/sockutils.c.o.requires
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/requires

nbsockutils/CMakeFiles/nbsockutils.dir/clean:
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils && $(CMAKE_COMMAND) -P CMakeFiles/nbsockutils.dir/cmake_clean.cmake
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/clean

nbsockutils/CMakeFiles/nbsockutils.dir/depend:
	cd /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils /home/adhanas/695/csc695-ofss-dev/nbeesrc-jan-10-2013/src/nbsockutils/CMakeFiles/nbsockutils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : nbsockutils/CMakeFiles/nbsockutils.dir/depend

