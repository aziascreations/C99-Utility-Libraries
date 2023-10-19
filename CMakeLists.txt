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

if(NP_GOODIES_IS_MAIN)
    message("----> Non-imported context autoconfig")
    set(NP_GOODIES_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
    set(NP_GOODIES_BUILD_TESTS ON CACHE BOOL "" FORCE)
    set(NP_GOODIES_BUILD_BENCHMARKS ON CACHE BOOL "" FORCE)
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
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FILEALIGN:16 /OPT:REF")

        # /CGTHREADS:x -> Makes 'cl.exe' use x thread(s).
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /CGTHREADS:8")

        # /GUARD:CF       -> Enables Control Flow Guard protection.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /GUARD:CF")

        # /RELEASE -> Sets the Checksum in the header of final executable.
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /RELEASE")
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
file(GLOB_RECURSE src_all CONFIGURE_DEPENDS "src/*.h" "src/*.c")

file(GLOB src_test_utils CONFIGURE_DEPENDS "tests/assert.h" "tests/memutils.c" "tests/memutils.h" "src/platform.h")


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
    # FIXME: Doesn't appear to work properly since the updates to Visual Studio...
    add_library(np_clang_goodies_dll_static SHARED ${src_all} rsc/np_clang_goodies.rc)
    target_compile_definitions(np_clang_goodies_dll_static PUBLIC NP_GOODIES_EXPORT_ALL)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES OUTPUT_NAME np_clang_goodies)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded)
    set_target_properties(np_clang_goodies_dll_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "dll_static/")
    set_target_properties(np_clang_goodies_dll_static PROPERTIES LIBRARY_OUTPUT_DIRECTORY "dll_static/")
    set_target_properties(np_clang_goodies_dll_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "dll_static/")
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

    add_executable(example_dllist_basic examples/dllist_basic.c ${src_dllist} ${src_text})
    add_executable(example_dllist_custom_free examples/dllist_custom_free.c ${src_dllist} ${src_text})
    add_executable(example_dllist_custom_node examples/dllist_custom_node.c ${src_dllist} ${src_text})
    add_executable(example_dllist_specific examples/dllist_specific.c ${src_dllist} ${src_text})
    add_executable(example_uuid_all examples/uuid_all.c ${src_uuid})
    add_executable(example_crc32 examples/crc32.c ${src_hash})

    if(WIN32)
        add_executable(example_uuid_win32 examples/uuid_win32.c ${src_uuid})
    endif()
else()
    message("---> Skipping examples targets...")
endif()


# Targets > Tests
if(NP_GOODIES_BUILD_TESTS)
    message("---> Adding test targets...")

    # Targets > Tests > Templates
    #target_compile_definitions(target_name_here PUBLIC NP_DEBUG_LOGGING)

    # Targets > Tests > Arguments > Char
    add_executable(test_args_options tests/arguments/test_options.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_options COMMAND test_args_options)

    add_executable(test_verb_registration tests/arguments/test_verb_registration.c ${src_args} ${src_test_utils})
    add_test(NAME test_verb_registration COMMAND test_verb_registration)

    add_executable(test_args_parsing_basic tests/arguments/test_args_parsing_basic.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_parsing_basic COMMAND test_args_parsing_basic)

    add_executable(test_args_required_option tests/arguments/test_args_required_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_option COMMAND test_args_required_option)

    add_executable(test_args_default_option tests/arguments/test_args_default_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_default_option COMMAND test_args_default_option)

    add_executable(test_args_options_wchar tests/arguments/test_options.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_options_wchar COMMAND test_args_options_wchar)
    target_compile_definitions(test_args_options_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

    # Targets > Tests > Arguments > WChar
    add_executable(test_verb_registration_wchar tests/arguments/test_verb_registration.c ${src_args} ${src_test_utils})
    add_test(NAME test_verb_registration_wchar COMMAND test_verb_registration_wchar)
    target_compile_definitions(test_verb_registration_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

    add_executable(test_args_parsing_basic_wchar tests/arguments/test_args_parsing_basic.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_parsing_basic_wchar COMMAND test_args_parsing_basic_wchar)
    target_compile_definitions(test_args_parsing_basic_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

    add_executable(test_args_required_option_wchar tests/arguments/test_args_required_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_required_option_wchar COMMAND test_args_required_option_wchar)
    target_compile_definitions(test_args_required_option_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

    add_executable(test_args_default_option_wchar tests/arguments/test_args_default_option.c ${src_args} ${src_test_utils})
    add_test(NAME test_args_default_option_wchar COMMAND test_args_default_option_wchar)
    target_compile_definitions(test_args_default_option_wchar PUBLIC NP_GOODIES_ARGUMENTS_USE_WCHAR)

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
    add_executable(test_text_copyLineW tests/text/test_text_copyLineW.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copyLineW COMMAND test_text_copyLineW)

    add_executable(test_text_copy tests/text/test_text_copy.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copy COMMAND test_text_copy)
    add_executable(test_text_copyW tests/text/test_text_copyW.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_copyW COMMAND test_text_copyW)
    #target_compile_definitions(test_text_copyW PUBLIC NP_GOODIES_ADD_C11_OPTIMIZATIONS)

    add_executable(test_text_startsWith tests/text/test_text_startsWith.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_startsWith COMMAND test_text_startsWith)
    add_executable(test_text_startsWithW tests/text/test_text_startsWithW.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_startsWithW COMMAND test_text_startsWithW)

    add_executable(test_text_isEmpty tests/text/test_text_isEmpty.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_isEmpty COMMAND test_text_isEmpty)
    add_executable(test_text_isEmptyW tests/text/test_text_isEmptyW.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_isEmptyW COMMAND test_text_isEmptyW)

    add_executable(test_text_nextSpaceIndex tests/text/test_text_nextSpaceIndex.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_nextSpaceIndex COMMAND test_text_nextSpaceIndex)
    add_executable(test_text_nextSpaceIndexW tests/text/test_text_nextSpaceIndexW.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_nextSpaceIndexW COMMAND test_text_nextSpaceIndexW)

    add_executable(test_text_charToWChar tests/text/test_text_charToWChar.c ${src_text} ${src_test_utils})
    add_test(NAME test_text_charToWChar COMMAND test_text_charToWChar)
    #target_compile_definitions(test_text_charToWChar PUBLIC NP_GOODIES_ADD_C11_OPTIMIZATIONS)

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

# End
message("--> Done :)")
