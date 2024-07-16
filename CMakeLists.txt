# Setup > FetchContent import detection
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(NP_GOODIES_IS_MAIN TRUE)
else()
    set(NP_GOODIES_IS_MAIN FALSE)
endif()


# Setup > Vanity title
message("-- NibblePoker's Clang Goodies --")

# Setup > Debugging printout
if(NP_GOODIES_IS_MAIN)
    message("--> Context: Main project")
else()
    message("--> Context: Included in other project")
endif()

# Configuring CMake
message("--> Configuring CMake...")


# Configuring CMake > Checking minimum version
message("---> Checking CMake's version...")
message("----> Require 3.13")
message("----> Using ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.13)


# Configuring CMake > Preparing C revision and project itself...
if(NP_GOODIES_IS_MAIN)
    message("---> Setting language to \"C\" and revision to \"C99\" without extensions")
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_EXTENSIONS OFF)
endif()


# Project > Declaration
project("NibblePoker's Clang Goodies" C)


# Project > Options
message("---> Defining options...")
include(CMakeDependentOption)
option(NP_GOODIES_BUILD_EXAMPLES "Build the examples." OFF)
option(NP_GOODIES_BUILD_TESTS "Build the tests." OFF)
option(NP_GOODIES_BUILD_BENCHMARKS "Build the benchmarks." OFF)
option(NP_GOODIES_BUILD_WIN32_NODEFAULTLIB "Adds the 'NODEFAULTLIB' option for MSVC." OFF)

if(NP_GOODIES_IS_MAIN)
    message("----> Non-imported context autoconfig")
    set(NP_GOODIES_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
    set(NP_GOODIES_BUILD_TESTS ON CACHE BOOL "" FORCE)
    set(NP_GOODIES_BUILD_BENCHMARKS ON CACHE BOOL "" FORCE)
    set(NP_GOODIES_BUILD_WIN32_NODEFAULTLIB OFF CACHE BOOL "")
endif()


# Project > CTest
if(NP_GOODIES_BUILD_TESTS)
    message("---> Including CTest...")
    include(CTest)
    enable_testing()
endif()


# Compiler > Config
if(NP_GOODIES_IS_MAIN)
    message("--> Compiler configuration in non-imported context")
    if(MSVC)
        message("---> Detected MSVC compiler, adding custom flags to compiler and linker...")

        # /TC - Specifies all source files are C.
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Gy /Oy /TC")

        # /Od -> Disables optimization.
        # /Ot -> Favors fast code.
        # /Os -> Favors small code.
        set(CMAKE_C_FLAGS_DEBUG "/Od ${CMAKE_C_FLAGS_DEBUG}")
        set(CMAKE_C_FLAGS_RELEASE "/Ot ${CMAKE_C_FLAGS_RELEASE}")
        set(CMAKE_C_FLAGS_MINSIZEREL "/Os ${CMAKE_C_FLAGS_MINSIZEREL}")
        set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ot ${CMAKE_C_FLAGS_RELWITHDEBINFO}")

        if(NOT _MSVC_C_ARCHITECTURE_FAMILY STREQUAL "ARM")
            message("----> Adding some flags that only work on non generic ARM platforms...")
            # /ALIGN:x     -> Align final executable's section to multiples of x bytes.
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ALIGN:128")
        endif()

        # /FILEALIGN:x -> Forces section alignment to multiples of x bytes.
        # /OPT:REF     -> Eliminates functions and data that are never referenced.
        # /OPT:ICF=x   -> Performs x iterations of COMDAT folding.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FILEALIGN:16 /OPT:REF /OPT:ICF=9")

        # /CGTHREADS:x -> Makes 'cl.exe' use x thread(s).
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /CGTHREADS:8")

        # /GUARD:CF       -> Enables Control Flow Guard protection.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /GUARD:CF")

        # /RELEASE -> Sets the Checksum in the header of final executable.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /RELEASE")

        # /RELEASE -> Enables link-time code generation/optimizations.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG")
        # No real size difference seen.

        if(NP_GOODIES_BUILD_WIN32_NODEFAULTLIB)
            message("----> Adding the '/NODEFAULTLIB' flag...")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")
        endif()
    endif()

    if(MINGW)
        message("---> Detected MinGW compiler, adding custom flags to compiler and linker...")

        set(CMAKE_C_FLAGS_DEBUG "-O0 -g -std=c99")

        set(CMAKE_C_FLAGS_RELEASE "-Ofast -DNDEBUG -std=c99 -fno-exceptions -ffunction-sections -fdata-sections")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -static-libgcc -ffunction-sections -fdata-sections -Wl,--gc-sections")

        set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG -std=c99 -fno-exceptions -ffunction-sections -fdata-sections")
        set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s -static-libgcc -ffunction-sections -fdata-sections -Wl,--gc-sections")

        set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Og -g -std=c99")

        # Could also use -Oz on CLang

        # See "C:\cygwin64\bin\strip.exe" about reducing size
        # MinGW just bloats the final DLL to shit with sections and junk
        # Tested: Went from 120Kb to 70kb in an instant...
        # There's still like 50 copies of "GCC: (GNU) 13.1.0" throughout tho...

        # The worst are idiots that spout shit like this:
        # - "A good toolchain [GCC] will not need to be told that [it needs to strip its shit from the executable], though."
        # Namely: "https://stackoverflow.com/a/200776"
        # Eat a bowl of dicks and choke on it.
    endif()

    if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
        message("---> Detected TinyCC, adding custom flags to compiler and linker...")

        # See: https://bellard.org/tcc/tcc-doc.html

        # CMAKE_C_FLAGS is set via 'cmake' in the CLI
        #set(CMAKE_C_FLAGS "-m32")
        #if(WIN32)
        #    message("----> Adding '-mms-bitfields' to stay compatible with MSVC and not GCC on Win32...")
        #    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mms-bitfields")
        #endif()

        #    target_compile_options(test_win32_registry_doesKeyExist PRIVATE "-ladvapi32")
        #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ladvapi32")

        set(CMAKE_C_FLAGS_DEBUG "-g")
        set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG")
        set(CMAKE_C_FLAGS_MINSIZEREL "-DNDEBUG")
        set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -DNDEBUG")

        message("MAKE_C_LINK_EXECUTABLE => ${MAKE_C_LINK_EXECUTABLE}")

        #message("CMAKE_EXE_LINKER_FLAGS => ${CMAKE_EXE_LINKER_FLAGS}")
        #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L./rsc -ladvapi32")
        #message("CMAKE_EXE_LINKER_FLAGS => ${CMAKE_EXE_LINKER_FLAGS}")
    endif()
endif()


# Targets
message("--> Preparing targets and related resources...")


# Targets > Sources
# FIXME: Revamp this section to be dependant on 'NP_GOODIES_IS_MAIN'.
file(GLOB src_np_clang_goodies_commons CONFIGURE_DEPENDS "src/debug.h" "src/platform.h")

file(GLOB src_np_clang_goodies_llist_base CONFIGURE_DEPENDS "src/lists/*.c" "src/lists/*.h" ${src_np_clang_goodies_commons})
file(GLOB src_dllist CONFIGURE_DEPENDS "src/lists/double/*.h" "src/lists/double/*.c" "src/lists/*.c" "src/lists/*.h" ${src_np_clang_goodies_commons})
file(GLOB src_sllist CONFIGURE_DEPENDS "src/lists/single/*.h" "src/lists/single/*.c" "src/lists/*.c" "src/lists/*.h" ${src_np_clang_goodies_commons})
file(GLOB_RECURSE src_llist CONFIGURE_DEPENDS "src/lists/*.h" "src/lists/*.c" ${src_np_clang_goodies_commons})

file(GLOB src_text CONFIGURE_DEPENDS "src/text.h" "src/text.c" ${src_np_clang_goodies_commons})

file(GLOB src_args CONFIGURE_DEPENDS ${src_llist} "src/text.c" "src/text.h" "src/arguments/*.h" "src/arguments/*.c" ${src_np_clang_goodies_commons})

file(GLOB_RECURSE src_hashmap CONFIGURE_DEPENDS "src/hashmaps/*.c" "src/hashmaps/*.h" ${src_llist} ${src_np_clang_goodies_commons})

file(GLOB src_uuid CONFIGURE_DEPENDS "src/uuid/*.h" "src/uuid/*.c" ${src_np_clang_goodies_commons})
file(GLOB_RECURSE src_hash CONFIGURE_DEPENDS "src/hash/*.h" "src/hash/*.c" ${src_np_clang_goodies_commons})

#file(GLOB_RECURSE src_ini CONFIGURE_DEPENDS "src/ini/*.h" "src/ini/*.c" ${src_text} ${src_hash} ${src_hashmap} ${src_llist} ${src_np_clang_goodies_commons})

# Was this a test for TCC or the registry's APIs ?
#if(WIN32)
#    file(GLOB_RECURSE src_win32 CONFIGURE_DEPENDS "src/win32/*.h" "src/win32/*.c")
#    # "rsc/advapi32.def"
#endif()

file(GLOB_RECURSE src_all CONFIGURE_DEPENDS "src/*.h" "src/*.c")

file(GLOB src_test_utils CONFIGURE_DEPENDS "tests/assert.h" "tests/memutils.c" "tests/memutils.h" "src/platform.h")

# Targets > Debugging Printouts
if(NP_GOODIES_IS_MAIN)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("---> Enabling debug logging for 'Debug' builds...")
        add_compile_definitions(NP_DEBUG_LOGGING)
    endif()
endif()


# Targets > DLLs
if(NP_GOODIES_IS_MAIN)
    # Targets > DLLs > Dynamic
    add_library(np_clang_goodies_dll_dynamic SHARED ${src_all} rsc/np_clang_goodies.rc)
    target_compile_definitions(np_clang_goodies_dll_dynamic PUBLIC NP_GOODIES_EXPORT_ALL)
    set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES OUTPUT_NAME np_clang_goodies)
    set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
    set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_dynamic/")
    set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_dynamic/")
    set_target_properties(np_clang_goodies_dll_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_dynamic/")

    # Targets > DLLs > Static
    add_library(np_clang_goodies_dll_static STATIC ${src_all} rsc/np_clang_goodies.rc)
    target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_GOODIES_EXPORT_ALL)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES OUTPUT_NAME np_clang_goodies)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_static/")
    set_target_properties(np_clang_goodies_dll_static PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_static/")
    set_target_properties(np_clang_goodies_dll_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_static/")

    # Targets > Dummy > MSVCRT Headers
    file(GLOB_RECURSE src_msvcrt_dummy CONFIGURE_DEPENDS "msvcrt/main.cmakesilencer.c" "msvcrt/src/*.h" "msvcrt/src/*.c")
    add_library(np_clang_goodies_msvcrt_dummy STATIC ${src_msvcrt_dummy})
else()
    # Targets > DLLs > External Project
    add_library(lib_np_clang_goodies SHARED ${src_all} ./rsc/np_clang_goodies.rc)
    set_target_properties(lib_np_clang_goodies PROPERTIES OUTPUT_NAME np_clang_goodies)

    # Exporting everything
    # TODO: Make it use the proper definitions !
    target_compile_definitions(lib_np_clang_goodies PUBLIC NP_GOODIES_EXPORT_ALL)

    # Forcing dynamic DLL
    if(WIN32)
        set_target_properties(lib_np_clang_goodies PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
    endif()

    # Allowing easier imports
    target_include_directories(lib_np_clang_goodies PUBLIC ./src)

    # Unsure if required
    # TODO: Test this a bit more

    #set_target_properties(lib_np_clang_goodies PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_dynamic/")
    #set_target_properties(lib_np_clang_goodies PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_dynamic/")
    #set_target_properties(lib_np_clang_goodies PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_dynamic/")

    install(TARGETS lib_np_clang_goodies
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    # TODO: Implement mechanisms to make it static and potentially not a DLL !
endif()


# Targets > Examples
if(NP_GOODIES_BUILD_EXAMPLES)
    message("---> Adding examples targets...")

    add_executable(example_arguments_basic_char examples/arguments_basic.c ${src_args})
    add_executable(example_arguments_basic_wchar examples/arguments_basic.c ${src_args})
    target_compile_definitions(example_arguments_basic_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

    add_executable(example_dllist_basic examples/dllist_basic.c ${src_dllist} ${src_text})
    add_executable(example_dllist_custom_free examples/dllist_custom_free.c ${src_dllist} ${src_text})
    add_executable(example_dllist_custom_node examples/dllist_custom_node.c ${src_dllist} ${src_text})
    add_executable(example_dllist_specific examples/dllist_specific.c ${src_dllist} ${src_text})
    add_executable(example_uuid_all examples/uuid_all.c ${src_uuid})
    add_executable(example_crc32 examples/crc32.c ${src_hash})

    add_executable(example_debug_logging_off examples/debug_logging.c ${src_np_clang_goodies_commons})
    add_executable(example_debug_logging_on  examples/debug_logging.c ${src_np_clang_goodies_commons})
    target_compile_definitions(example_debug_logging_on PUBLIC NP_DEBUG_LOGGING)

    add_executable(example_hashmap_chained_basic examples/hashmap_chained_basic.c ${src_hashmap} ${src_hash} ${src_text})

    if(WIN32)
        if(NOT CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
            add_executable(example_uuid_win32 examples/uuid_win32.c ${src_uuid})
        endif()
    endif()
else()
    message("---> Skipping examples targets...")
endif()


# Targets > Tests
if(NP_GOODIES_BUILD_TESTS)
    message("---> Adding test targets...")

    # Targets > Tests > Templates
    #target_compile_definitions(target_name_here PUBLIC NP_DEBUG_LOGGING)
    #target_compile_definitions(target_name_here PUBLIC NP_GOODIES_ADD_C11_OPTIMIZATIONS)

    # Targets > Tests > Arguments > Char
    add_executable(test_args_options tests/arguments/test_options.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_options COMMAND test_args_options)

    add_executable(test_verb_registration tests/arguments/test_verb_registration.c ${src_args} ${src_test_utils})
    add_test(NAME test_verb_registration COMMAND test_verb_registration)

    add_executable(test_args_parsing_basic tests/arguments/test_args_parsing_basic.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_parsing_basic COMMAND test_args_parsing_basic)

    add_executable(test_args_required_children_option tests/arguments/test_args_required_children_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_children_option COMMAND test_args_required_children_option)

    add_executable(test_args_required_option tests/arguments/test_args_required_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_option COMMAND test_args_required_option)

    add_executable(test_args_default_option tests/arguments/test_args_default_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_default_option COMMAND test_args_default_option)

    # Targets > Tests > Arguments > WChar
    add_executable(test_args_options_wchar tests/arguments/test_options.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_options_wchar COMMAND test_args_options_wchar)
    target_compile_definitions(test_args_options_wchar PUBLIC UNICODE)

    add_executable(test_verb_registration_wchar tests/arguments/test_verb_registration.c ${src_args} ${src_test_utils})
    add_test(NAME test_verb_registration_wchar COMMAND test_verb_registration_wchar)
    target_compile_definitions(test_verb_registration_wchar PUBLIC UNICODE)

    add_executable(test_args_parsing_basic_wchar tests/arguments/test_args_parsing_basic.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_parsing_basic_wchar COMMAND test_args_parsing_basic_wchar)
    target_compile_definitions(test_args_parsing_basic_wchar PUBLIC UNICODE)

    add_executable(test_args_required_children_option_wchar tests/arguments/test_args_required_children_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_children_option_wchar COMMAND test_args_required_children_option)
    target_compile_definitions(test_args_required_children_option_wchar PUBLIC UNICODE)

    add_executable(test_args_required_option_wchar tests/arguments/test_args_required_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_option_wchar COMMAND test_args_required_option_wchar)
    target_compile_definitions(test_args_required_option_wchar PUBLIC UNICODE)

    add_executable(test_args_default_option_wchar tests/arguments/test_args_default_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_default_option_wchar COMMAND test_args_default_option_wchar)
    target_compile_definitions(test_args_default_option_wchar PUBLIC UNICODE)

    # Targets > Tests > Lists
    add_executable(test_llist_default_node_size tests/lists/test_llist_default_node_size.c ${src_llist} ${src_test_utils})
    add_test(NAME test_llist_default_node_size COMMAND test_llist_default_node_size)

    add_executable(test_sllist_insertion tests/lists/test_sllist_insertion.c ${src_sllist} ${src_test_utils})
    add_test(NAME test_sllist_insertion COMMAND test_sllist_insertion)
    add_executable(test_dllist_insertion tests/lists/test_dllist_insertion.c ${src_dllist} ${src_test_utils})
    add_test(NAME test_dllist_insertion COMMAND test_dllist_insertion)

    add_executable(test_sllist_node_navigation tests/lists/test_sllist_node_navigation.c ${src_sllist} ${src_test_utils})
    add_test(NAME test_sllist_node_navigation COMMAND test_sllist_node_navigation)
    add_executable(test_dllist_node_navigation tests/lists/test_dllist_node_navigation.c ${src_dllist} ${src_test_utils})
    add_test(NAME test_dllist_node_navigation COMMAND test_dllist_node_navigation)

    add_executable(test_sllist_removal tests/lists/test_sllist_removal.c ${src_sllist} ${src_test_utils})
    add_test(NAME test_sllist_removal COMMAND test_sllist_removal)
    add_executable(test_dllist_removal tests/lists/test_dllist_removal.c ${src_dllist} ${src_test_utils})
    add_test(NAME test_dllist_removal COMMAND test_dllist_removal)

    # Targets > Tests > Chained HashMaps
    add_executable(test_hashmap_chained_creation tests/hashmap_chained/test_hashmap_chained_creation.c ${src_hashmap} ${src_test_utils})
    add_test(NAME test_hashmap_chained_creation COMMAND test_hashmap_chained_creation)

    add_executable(test_hashmap_chained_add_get tests/hashmap_chained/test_hashmap_chained_add_get.c ${src_hashmap} ${src_test_utils})
    add_test(NAME test_hashmap_chained_add_get COMMAND test_hashmap_chained_add_get)

    add_executable(test_hashmap_chained_deletion tests/hashmap_chained/test_hashmap_chained_deletion.c ${src_hashmap} ${src_test_utils})
    add_test(NAME test_hashmap_chained_deletion COMMAND test_hashmap_chained_deletion)

    # Targets > Tests > Text
    add_executable(test_text_copyLine tests/text/test_text_copyLine.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copyLine COMMAND test_text_copyLine)
    add_executable(test_text_copyLineW tests/text/test_text_copyLine.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copyLineW COMMAND test_text_copyLineW)
    target_compile_definitions(test_text_copyLineW PUBLIC UNICODE)

    add_executable(test_text_copy tests/text/test_text_copy.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copy COMMAND test_text_copy)
    add_executable(test_text_copyW tests/text/test_text_copy.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copyW COMMAND test_text_copyW)
    target_compile_definitions(test_text_copyW PUBLIC UNICODE)

    add_executable(test_text_startsWith tests/text/test_text_startsWith.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_startsWith COMMAND test_text_startsWith)
    add_executable(test_text_startsWithW tests/text/test_text_startsWith.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_startsWithW COMMAND test_text_startsWithW)
    target_compile_definitions(test_text_startsWithW PUBLIC UNICODE)

    add_executable(test_text_isEmpty tests/text/test_text_isEmpty.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_isEmpty COMMAND test_text_isEmpty)
    add_executable(test_text_isEmptyW tests/text/test_text_isEmpty.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_isEmptyW COMMAND test_text_isEmptyW)
    target_compile_definitions(test_text_isEmptyW PUBLIC UNICODE)

    add_executable(test_text_nextSpaceIndex tests/text/test_text_nextSpaceIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_nextSpaceIndex COMMAND test_text_nextSpaceIndex)
    add_executable(test_text_nextSpaceIndexW tests/text/test_text_nextSpaceIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_nextSpaceIndexW COMMAND test_text_nextSpaceIndexW)
    target_compile_definitions(test_text_nextSpaceIndexW PUBLIC UNICODE)

    add_executable(test_text_firstDifferentIndex tests/text/test_text_firstDifferentIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_firstDifferentIndex COMMAND test_text_firstDifferentIndex)
    add_executable(test_text_firstDifferentIndexW tests/text/test_text_firstDifferentIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_firstDifferentIndexW COMMAND test_text_firstDifferentIndexW)
    target_compile_definitions(test_text_firstDifferentIndexW PUBLIC UNICODE)

    add_executable(test_text_lastDifferentIndex tests/text/test_text_lastDifferentIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_lastDifferentIndex COMMAND test_text_firstDifferentIndex)
    add_executable(test_text_lastDifferentIndexW tests/text/test_text_lastDifferentIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_lastDifferentIndexW COMMAND test_text_lastDifferentIndexW)
    target_compile_definitions(test_text_lastDifferentIndexW PUBLIC UNICODE)

    add_executable(test_text_trim tests/text/test_text_trim.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_trim COMMAND test_text_trim)
    add_executable(test_text_trimW tests/text/test_text_trim.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_trimW COMMAND test_text_trimW)
    target_compile_definitions(test_text_trimW PUBLIC UNICODE)

    add_executable(test_text_charToWChar tests/text/test_text_charToWChar.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_charToWChar COMMAND test_text_charToWChar)
    #target_compile_definitions(test_text_charToWChar PUBLIC NP_GOODIES_ADD_C11_OPTIMIZATIONS)

    # Targets > Tests > Win32
    #if(WIN32)
    #    add_executable(test_win32_registry_doesKeyExist tests/win32/registry/test_win32_registry_doesKeyExist.c ${src_win32} ${src_test_utils})
    #    add_test(NAME test_win32_registry_doesKeyExist COMMAND test_win32_registry_doesKeyExist)
    #    if(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
    #        target_link_libraries(test_win32_registry_doesKeyExist PRIVATE "advapi32.lib")
    #        target_link_options(test_win32_registry_doesKeyExist PRIVATE "-L./rsc -ladvapi32")
    #        target_compile_options(test_win32_registry_doesKeyExist PRIVATE "-L./rsc -ladvapi32")
    #    endif()
    #endif()

    # Targets > Tests > Misc
    add_executable(test_platform tests/misc/test_platform.c "tests/assert.h" "src/platform.h")
    add_test(NAME test_platform COMMAND test_platform)
else()
    message("---> Skipping test targets...")
endif()

if(NP_GOODIES_BUILD_BENCHMARKS)
    message("---> Adding benchmark targets...")

    # See: https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html

    add_executable(bm_crc32_implementations benchmarks/bm_crc32_implementations.c)

    add_executable(bm_square_of_two_mask benchmarks/bm_square_of_two_mask.c)

    if(WIN32)
        # FIXME: pow() appears to be missing on GNUC, that's odd...
        add_executable(bm_powers_of_two benchmarks/bm_powers_of_two.c)
    endif()
else()
    message("---> Skipping benchmark targets...")
endif()

# Commands
# FIXME: Expose the path as a variable !
#unset(EXECUTABLE_CYGWIN_STRIP CACHE)

#find_program(
#        EXECUTABLE_CYGWIN_STRIP
#        NAMES "C:\\cygwin64\\bin\\strip.exe"
#)

# Doesn't work for ARM !!!
#if(EXECUTABLE_CYGWIN_STRIP)
#    message("----> Found 'strip.exe', adding 'POST_BUILD' executable stripping step...")
#
#    # https://cmake.org/cmake/help/v2.8.12/cmake.html#command:add_custom_command
#    # FIXME: strip may cause issues on ARM or another specific target, got bit a while ago, can't remember how and why...
#    add_custom_command(
#            TARGET np_clang_goodies_dll_dynamic
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND}
#            ARGS -E echo "Running 'strip.exe' on '$<TARGET_FILE:np_clang_goodies_dll_dynamic>'"
#    )
#    add_custom_command(
#            TARGET np_clang_goodies_dll_dynamic
#            POST_BUILD
#            COMMAND "C:\\cygwin64\\bin\\strip.exe"
#            ARGS -s "$<TARGET_FILE:np_clang_goodies_dll_dynamic>"
#    )
#else()
#    message("----> Unable to find 'strip.exe' in PATH, final executable won't be stripping !")
#endif()

# End
message("--> Done :)")
