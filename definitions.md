# Definitions

## Summary
* [Features Toggles](#features-toggles)
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
    * `NP_GOODIES_EXPORT_ARGUMENTS`
    * `NP_GOODIES_EXPORT_HASH`
      * `NP_GOODIES_EXPORT_CRC32`
    * `NP_GOODIES_EXPORT_HASHMAP_ALL`
      * `NP_GOODIES_EXPORT_HASHMAP_CHAINED`
    * `NP_GOODIES_EXPORT_LIST_ALL`
      * `NP_GOODIES_EXPORT_SLLIST`
      * `NP_GOODIES_EXPORT_DLLIST`
    * <s>`NP_GOODIES_EXPORT_ULID`</s> **TODO**
    * `NP_GOODIES_EXPORT_UUID_ALL`
      * `NP_GOODIES_EXPORT_UUID4`
      * <s>`NP_GOODIES_EXPORT_UUID6`</s> **TODO**
      * <s>`NP_GOODIES_EXPORT_UUID7`</s> **TODO**
    * `NP_GOODIES_EXPORT_TEXT`


## Features Toggles

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
[TODO: Note about hierarchy and dependencies.]

### Everything
**Definition:** `NP_GOODIES_EXPORT_ALL`

If defined, every possible function is exported.<br>
This definition takes precedence over any other `NP_GOODIES_EXPORT_*` definition.
