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

# Compiler stuff
# See: https://github.com/aziascreations/C99-Win32-Wifi-Utility/blob/master/CMakeLists.txt
if(MSVC)
    message("---> Detected MSVC compiler, adding custom flags to compiler and linker...")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Gy /Oy")

    # Adds around 1kb to the final DLL, it is worth it ?
    # Source: https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /sdl")

    # /Zl seems to affect the implicitly included .lib
    set(CMAKE_C_FLAGS_RELEASE "/Ot ${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os ${CMAKE_C_FLAGS_MINSIZEREL}")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ot ${CMAKE_C_FLAGS_RELWITHDEBINFO}")

    # Warning: According to the doc, this MAY cause issue on non-driver subsystems.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ALIGN:128 /FILEALIGN:16 /OPT:REF")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG /CGTHREADS:8")

    # Adds some extra protection for indirect calls such as the ones used when freeing lists.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /GUARD:CF /DYNAMICBASE")

    # See:
    #  * https://learn.microsoft.com/en-us/cpp/build/reference/subsystem-specify-subsystem?view=msvc-170
    #  * https://learn.microsoft.com/en-us/cpp/build/reference/release-set-the-checksum?view=msvc-170
    # Check the per-target properties for the /SUBSYSTEM option.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /RELEASE")
endif()

# Preparing targets
file(GLOB src_dllist CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/lists/*.c" "src/lists/*.h" "src/debug.h")
file(GLOB src_sllist CONFIGURE_DEPENDS "src/lists/simple/*.h" "src/lists/simple/*.c" "src/lists/*.c" "src/lists/*.h" "src/debug.h")
file(GLOB src_args CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/text.c" "src/text.h" "src/arguments/*.h" "src/arguments/*.c" "src/debug.h")
file(GLOB src_uuid CONFIGURE_DEPENDS "src/uuid/*.h" "src/uuid/*.c")
file(GLOB src_text CONFIGURE_DEPENDS "src/text.h" "src/text.c")
file(GLOB_RECURSE src_hash CONFIGURE_DEPENDS "src/hash/*.h" "src/hash/*.c")
file(GLOB_RECURSE src_all CONFIGURE_DEPENDS "src/*.h" "src/*.c")

# Preparing targets > Dynamic DLL
add_library(np_clang_goodies_dll_dynamic SHARED ${src_all} rsc/np_clang_goodies.rc)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_ARGUMENTS_EXPORT)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_DLLIST_EXPORT)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_UUID4_EXPORT)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_TEXT_EXPORT)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_GOODIES_EXPORT_SLLIST)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_GOODIES_EXPORT_HASHMAP_ALL)
target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_GOODIES_EXPORT_CRC32)
set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES OUTPUT_NAME NibblePoker.Library.ClangGoodies)
set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_dynamic/")
set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_dynamic/")
set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_dynamic/")

# Preparing targets > Static DLL
add_library(np_clang_goodies_dll_static SHARED ${src_all} rsc/np_clang_goodies.rc)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_ARGUMENTS_EXPORT)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_DLLIST_EXPORT)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_UUID4_EXPORT)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_TEXT_EXPORT)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_GOODIES_EXPORT_SLLIST)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_GOODIES_EXPORT_HASHMAP_ALL)
target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_GOODIES_EXPORT_CRC32)
set_target_properties(np_clang_goodies_dll_static PROPERTIES OUTPUT_NAME NibblePoker.Library.ClangGoodies)
set_target_properties(np_clang_goodies_dll_static PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded)
set_target_properties(np_clang_goodies_dll_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_static/")
set_target_properties(np_clang_goodies_dll_static PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_static/")
set_target_properties(np_clang_goodies_dll_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_static/")

# Preparing targets > Dev tester
add_executable(manual_testing manual_testing.c ${src_all})
set_target_properties(manual_testing PROPERTIES C_STANDARD 99)
target_compile_definitions(manual_testing PUBLIC NP_DEBUG_LOGGING)

# Preparing targets > Examples
add_executable(example_dllist_basic examples/dllist_basic.c ${src_dllist} ${src_text})
add_executable(example_dllist_custom_free examples/dllist_custom_free.c ${src_dllist} ${src_text})
add_executable(example_uuid_all examples/uuid_all.c ${src_uuid})
add_executable(example_crc32 examples/crc32.c ${src_hash})

# Preparing targets > Tests
add_executable(test_args_options tests/arguments/test_options.c ${src_args} tests/assert.h)
add_test(NAME test_args_options COMMAND test_args_options)
#target_compile_definitions(test_args_options PUBLIC NP_DEBUG_LOGGING)

add_executable(test_verb_registration tests/arguments/test_verb_registration.c ${src_args} tests/assert.h)
add_test(NAME test_verb_registration COMMAND test_verb_registration)
#target_compile_definitions(test_verb_registration PUBLIC NP_DEBUG_LOGGING)

add_executable(test_args_parsing_basic tests/arguments/test_args_parsing_basic.c ${src_args} tests/assert.h)
add_test(NAME test_args_parsing_basic COMMAND test_args_parsing_basic)
#target_compile_definitions(test_args_parsing_basic PUBLIC NP_DEBUG_LOGGING)

add_executable(test_args_required_option tests/arguments/test_args_required_option.c ${src_args} tests/assert.h)
add_test(NAME test_args_required_option COMMAND test_args_required_option)
#target_compile_definitions(test_args_required_option PUBLIC NP_DEBUG_LOGGING)

add_executable(test_args_default_option tests/arguments/test_args_default_option.c ${src_args} tests/assert.h)
add_test(NAME test_args_default_option COMMAND test_args_default_option)
#target_compile_definitions(test_args_default_option PUBLIC NP_DEBUG_LOGGING)

# Documentation
# TODO: Add custom target for it.

#message(${CMAKE_SYSTEM_PROCESSOR})
