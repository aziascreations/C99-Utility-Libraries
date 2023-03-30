# Configuring CMake
message("--> Configuring CMake...")

# Configuring CMake > Checking minimum version
message("---> Checking CMake's version...")
message("----> Require 3.16")
message("----> Using ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.16)

# Configuring CMake > Selecting compiler
message("---> Checking OS type...")
if (UNIX)
    message("----> Found UNIX system, requiring gcc compiler")
    set(CMAKE_C_COMPILER "gcc")
else ()
    message("----> Found non-UNIX system, letting CMake autodetect compiler")
endif (UNIX)
message("----> Compiler: ${CMAKE_C_COMPILER}")

# Configuring CMake > Preparing C revision and project itself...
message("---> Setting language to \"C\" and revision to \"C99\" without extensions")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

# Setting up the CMake project itself
project("NibblePoker's Clang Goodies" C)

# Adding CTest in order to be able to run tests
message("---> Including CTest...")
include(CTest)

# Getting some info
message("--> System's debugging info printout:")
message("---> System: ${CMAKE_SYSTEM_NAME}")
message("---> Version: ${CMAKE_SYSTEM_VERSION}")
message("---> Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message("---> Compiler: ${CMAKE_C_COMPILER}")
message("---> Build type: ${CMAKE_BUILD_TYPE}")
message("---> build types: ${CMAKE_CONFIGURATION_TYPES}")

message("--> Project's debugging info printout:")
message("---> MSCV version: ${MSVC_VERSION}")
message("---> MSCV toolset version: ${MSVC_TOOLSET_VERSION}")
message("---> C Standard version: ${CMAKE_C_STANDARD}")

# Configuring the compilers > Debugging info printout
message("---> Compiler's debugging info printout:")
message("----> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message("----> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("----> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message("----> CMAKE_C_FLAGS_MINSIZEREL: ${CMAKE_C_FLAGS_MINSIZEREL}")
message("----> CMAKE_C_FLAGS_RELWITHDEBINFO: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message("----> CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message("----> CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
message("----> CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}")
message("----> CMAKE_STATIC_LINKER_FLAGS: ${CMAKE_STATIC_LINKER_FLAGS}")

message("--> Checking for platform-specific arguments for the compiler")
if (CYGWIN)
    # Does not work !
    # See: https://cygwin.com/faq/faq.html#faq.programming.static-linking
    message("---> Detected Cygwin, adding \"-static\" to \"CMAKE_C_FLAGS\"")
    #set(CMAKE_C_FLAGS "-static ${CMAKE_C_FLAGS}")
elseif (MSVC)
    message("---> Detected MSVC compiler, adding custom flags")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Gy /Oy")
    # /Zl seems to affect the implicitly included .lib
    set(CMAKE_C_FLAGS_RELEASE "/Ot ${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os ${CMAKE_C_FLAGS_MINSIZEREL}")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ot ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    #string(REPLACE "/O2" "/O3" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
    # /MD doesn't affect it !

    # /OPT:NOWIN98 is not documented, but referenced by official doc, but doesn't work.
    # Align apparently cannot be lower than 128 :/
    # Going from 256 to 128 and 16 shaved off 1.5KB roughly
    # Warning: According to the doc, this MAY cause issue on non-driver subsystems.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ALIGN:128 /FILEALIGN:16 /OPT:REF")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG /CGTHREADS:8")

    # Adds some extra protection for indirect calls such as the ones used when freeing lists.
    # Adds around .2KB (16->16.2)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /GUARD:CF /DYNAMICBASE")

    # See:
    #  * https://learn.microsoft.com/en-us/cpp/build/reference/subsystem-specify-subsystem?view=msvc-170
    #  * https://learn.microsoft.com/en-us/cpp/build/reference/release-set-the-checksum?view=msvc-170
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /RELEASE /SUBSYSTEM:CONSOLE")

    # The /STUB:<filename> could be fun to play around with
    # https://learn.microsoft.com/en-us/cpp/build/reference/stub-ms-dos-stub-file-name?view=msvc-170

    # The /VERSION
    # https://learn.microsoft.com/en-us/cpp/build/reference/version-version-information?view=msvc-170

    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /WX")

    # One or both of these options triggers some AV on VirusTotal:
    # Rising: HackTool.CoinMiner!8.F154 (TFE:1:avQASvlVVsP)
    # SecureAge: Malicious
    # https://www.virustotal.com/gui/file/27b1fc390c1ef5b27351e0c7c752329ee9206329bcbff2bacfae629df60e9c04?nocache=1
    # Welp, it also seems to make it unable to use the app on Windows 10 64bits, bruh...
    # The gains were half a KB anyway.
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MERGE:.rdata=.data /MERGE:.text=.data")
    # /MERGE:.reloc=.data
else ()
    message("---> No actions taken")
endif ()

message("---> Final compiler's debugging info printout:")
message("----> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message("----> CMAKE_C_FLAGS_RELEASE_INIT: ${CMAKE_C_FLAGS_RELEASE_INIT}")
message("----> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("----> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message("----> CMAKE_C_FLAGS_MINSIZEREL: ${CMAKE_C_FLAGS_MINSIZEREL}")
message("----> CMAKE_C_FLAGS_RELWITHDEBINFO: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message("----> CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message("----> CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
message("----> CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}")
message("----> CMAKE_STATIC_LINKER_FLAGS: ${CMAKE_STATIC_LINKER_FLAGS}")

# Preparing targets
file(GLOB src_dllist CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/debug.h")
file(GLOB src_args CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/text.c" "src/text.h" "src/arguments/*.h" "src/arguments/*.c" "src/debug.h")
file(GLOB_RECURSE src_all CONFIGURE_DEPENDS "src/*.h" "src/*.c")

# Preparing targets > DoubleLinkedLists (TMP, for internal tests)
#add_library(lib_dllist_dynamic SHARED ${src_dllist})
#set_target_properties(lib_dllist_dynamic PROPERTIES OUTPUT_NAME npdllist)
#set_target_properties(lib_dllist_dynamic PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
#set_target_properties(lib_dllist_dynamic PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dynamic/npdllist/")
#set_target_properties(lib_dllist_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dynamic/npdllist/")
#set_target_properties(lib_dllist_dynamic PROPERTIES C_STANDARD 99)
#target_compile_definitions(lib_dllist_dynamic PUBLIC NP_DLLIST_EXPORT)
#target_compile_definitions(lib_dllist_dynamic PUBLIC NP_DLLIST_NO_MODULE)
#
#add_library(lib_dllist_static STATIC ${src_dllist})
#set_target_properties(lib_dllist_static PROPERTIES OUTPUT_NAME npdllist)
#set_target_properties(lib_dllist_static PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded)
#set_target_properties(lib_dllist_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "static/npdllist/")
#set_target_properties(lib_dllist_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "static/npdllist/")
#set_target_properties(lib_dllist_static PROPERTIES C_STANDARD 99)
#target_compile_definitions(lib_dllist_static PUBLIC NP_DLLIST_EXPORT)
#target_compile_definitions(lib_dllist_static PUBLIC NP_DLLIST_NO_MODULE)

#target_compile_definitions(lib_dllist_static PUBLIC NP_ARGUMENTS_EXPORT)

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
