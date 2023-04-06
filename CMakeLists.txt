# Configuring CMake
message("--> Configuring CMake...")

# Configuring CMake > Checking minimum version
message("---> Checking CMake's version...")
message("----> Require 3.16")
message("----> Using ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.16)

# Configuring CMake > Preparing C revision and project itself...
message("---> Setting language to \"C\" and revision to \"C99\" without extensions")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

# Setting up the CMake project itself
project("NibblePoker's Clang Goodies" C)

# Adding CTest in order to be able to run tests
message("---> Including CTest...")
include(CTest)

# Feature constants
message("--> Setting up constants")

if(WIN32)
    message("---> Defining 'NP_WIN32' and 'NP_ARGS_WCHAR'")

    # Enables some wchar_t related functions
    add_definitions(-DNP_WIN32)

    # This constant changes the args_* functions and related structs to use wchar_t instead of char strings.
    # You can comment it if you need char strings on windows.
    add_definitions(-DNP_ARGS_WCHAR)
endif()

# Preparing targets
file(GLOB src_dllist CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/debug.h")
file(GLOB src_args CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/text.c" "src/text.h" "src/arguments/*.h" "src/arguments/*.c" "src/debug.h")
file(GLOB_RECURSE src_all CONFIGURE_DEPENDS "src/*.h" "src/*.c")

# Preparing targets > Others
add_executable(manual_testing manual_testing.c ${src_all})
set_target_properties(manual_testing PROPERTIES C_STANDARD 99)
target_compile_definitions(manual_testing PUBLIC NP_DEBUG_LOGGING)

add_executable(test_args_options tests/arguments/test_options.c ${src_args} tests/assert.h)
add_test(NAME test_args_options COMMAND test_args_options)
target_compile_definitions(test_args_options PUBLIC NP_DEBUG_LOGGING)

add_executable(test_args_verbs tests/arguments/test_verb.c ${src_args} tests/assert.h)
add_test(NAME test_args_verbs COMMAND test_args_verbs)
target_compile_definitions(test_args_verbs PUBLIC NP_DEBUG_LOGGING)
