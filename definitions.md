# Definitions

## Summary
* [Features Toggles](#features-toggles)
  * `NP_GOODIES_ADD_C11_OPTIMIZATIONS` [➜](#everything---add-c11-optimizations)
  * `NP_GOODIES_CRC32_DISABLE_LOOKUP_TABLE` [➜](#crc32---disable-lookup-table)
  * `NP_GOODIES_CRC32_ENABLE_BRANCHLESS` [➜](#crc32---enables-branchless-logic)
  * <s>`NP_GOODIES_LIST_USE_COMMON_DELETER`</s> **TODO**
  * `NP_GOODIES_UUID_DISABLE_STRUCT_SIZE_CHECK` [➜](#uuid-structure-size-check)
* [CMake Stuff](#cmake-stuff)
  * `NP_GOODIES_BUILD_BENCHMARKS` [➜](#build-benchmarks)
  * `NP_GOODIES_BUILD_EXAMPLES` [➜](#build-examples)
  * `NP_GOODIES_BUILD_TESTS` [➜](#build-tests)
* [Library Exports Toggles](#library-exports-toggles) *(As a hierarchical list of priority)*
  * `NP_GOODIES_EXPORT_ALL` [➜](#everything)
    * `NP_GOODIES_EXPORT_ARGUMENTS` [➜](#arguments-parser)
    * `NP_GOODIES_EXPORT_HASH` [➜](#hashing-function---everything)
      * `NP_GOODIES_EXPORT_CRC32` [➜](#hashing-function---crc32)
    * `NP_GOODIES_EXPORT_HASHMAP_ALL` [➜](#hashmap---everything)
      * `NP_GOODIES_EXPORT_HASHMAP_CHAINED` [➜](#hashmap---chained)
    * `NP_GOODIES_EXPORT_LIST_ALL` [➜](#lists---everything)
      * `NP_GOODIES_EXPORT_SLLIST` [➜](#lists---single-linked-lists)
      * `NP_GOODIES_EXPORT_DLLIST` [➜](#lists---double-linked-lists)
    * <s>`NP_GOODIES_EXPORT_ULID`</s> **TODO**
    * `NP_GOODIES_EXPORT_UUID_ALL` [➜](#uuid---everything)
      * `NP_GOODIES_EXPORT_UUID4` [➜](#uuid---version-4)
      * <s>`NP_GOODIES_EXPORT_UUID6`</s> **TODO**
      * <s>`NP_GOODIES_EXPORT_UUID7`</s> **TODO**
    * `NP_GOODIES_EXPORT_TEXT` [➜](#text-utilities)


## Features Toggles

### Everything - Add C11 Optimizations
**Definition:** `NP_GOODIES_ADD_C11_OPTIMIZATIONS`

Enables various optimizations that take advantage of new and safer features provided in the C11 standard.

If C11 support isn't available or allowed by your compiler, nothing will be changed.

### CRC32 - Disable lookup table
**Definition:** `NP_GOODIES_CRC32_DISABLE_LOOKUP_TABLE`

Disables the internal lookup table for CRC32 hashes and forces the functions to
calculate everything at runtime.

This feature shouldn't be disabled unless you intend on saving as much space as
possible in the final executable since it slow down calculations drastically.<br>
Check the [Benchmarks](benchmarks/readme.md) page for more information.

### CRC32 - Enables branchless logic
**Definition:** `NP_GOODIES_CRC32_ENABLE_BRANCHLESS`

If enabled, this feature will disable the lookup table and will for the functions to
calculate everything at runtime in a branchless way.

This feature is only intended to be used on platforms that don't have branch predictors.

The CRC computation is drastically slowed down due to the use of a multiplication in place of the condition.<br>
Check the [Benchmarks](benchmarks/readme.md) page for more information.

### UUID Structure size check
**Definition:** `NP_GOODIES_UUID_DISABLE_STRUCT_SIZE_CHECK`

This feature is a "simple" macro that is used at the top of every function in
"[src/uuid/](src/uuid)".<br>
The macro is defined at the end of "[src/uuid/structs.h](src/uuid/structs.h)" and
was implemented by following an article from
"[scaryreasoner.wordpress.com](https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/)".

When compiled, this macro should result in zero code and only exist to cause
compiler errors when the size of the `uuid` structure doesn't match what is expected.

If defined, the macro will be empty.<br>
This shouldn't be done unless you have a very good reason to and don't use and/or
export the UUID functions.


## CMake Stuff

### Build benchmarks
**Definition:** `NP_GOODIES_BUILD_BENCHMARKS`

If defined, the benchmark targets will be added.

### Build examples
**Definition:** `NP_GOODIES_BUILD_EXAMPLES`

If defined, the example targets will be added.

### Build tests
**Definition:** `NP_GOODIES_BUILD_TESTS`

If defined, the test targets will be added as CTest tests.<br>
CTest will also be included in CMake.


## Library Exports Toggles
The export toggles work as a hierarchical list of priority, which means that the more important a
definition is, the more will get exported regardless of which "lesser" related definitions are present.

### Everything
**Definition:** `NP_GOODIES_EXPORT_ALL`

If defined, every possible function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition.


### Arguments Parser
**Definition:** `NP_GOODIES_EXPORT_ARGUMENTS`

If defined, every function in [src/arguments](src/arguments) is exported.

⚠️ The lists and text-related functions will be present in the final executable
but may not be exported unless their respective definition is present.


### Hashing Function - Everything
**Definition:** `NP_GOODIES_EXPORT_HASH`

If defined, every possible hashing function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition
that pertains to hashing functions.

### Hashing Function - CRC32
**Definition:** `NP_GOODIES_EXPORT_CRC32`

If defined, every CRC32-related functions are exported.

⚠️ The [NP_GOODIES_CRC32_DISABLE_LOOKUP_TABLE](#crc32---disable-lookup-table)
and [NP_GOODIES_CRC32_ENABLE_BRANCHLESS](#crc32---enables-branchless-logic)
definitions will affect the exported functions.


### HashMap - Everything
**Definition:** `NP_GOODIES_EXPORT_HASHMAP_ALL`

If defined, every possible hashmap-related function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition
that pertains to hashmaps.

⚠️ No hashing function required for proper hashmap operations are included under this definition.

### HashMap - Chained
**Definition:** `NP_GOODIES_EXPORT_HASHMAP_CHAINED`

If defined, every functions related to chained hashmaps are exported.

⚠️ No hashing function required for proper hashmap operations are included under this definition.


### Lists - Everything
**Definition:** `NP_GOODIES_EXPORT_LIST_ALL`

If defined, every possible list-related function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition
that pertains to lists.

### Lists - Single Linked Lists
**Definition:** `NP_GOODIES_EXPORT_SLLIST`

If defined, every functions related to single linked lists are exported.

### Lists - Double Linked Lists
**Definition:** `NP_GOODIES_EXPORT_DLLIST`

If defined, every functions related to double linked lists are exported.


### UUID - Everything
**Definition:** `NP_GOODIES_EXPORT_UUID_ALL`

If defined, every possible UUID-related function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition
that pertains to UUIDs.

### UUID - Version 4
**Definition:** `NP_GOODIES_EXPORT_UUID4`

If defined, every functions related to UUIDv4 are exported.


### Text Utilities
**Definition:** `NP_GOODIES_EXPORT_TEXT`

If defined, every functions related to UUIDv4 are exported.

⚠️ Some functions may not be exported if `NP_WIN32` isn't defined.
