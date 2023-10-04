# Definitions

## Summary
* [Features Toggles](#features-toggles)
  * `NP_GOODIES_UUID_DISABLE_STRUCT_SIZE_CHECK` [➜](#uuid-structure-size-check)
  * TODO `llist, use common deleter`
* CMake Stuff
  * TODO `NP_GOODIES_BUILD_EXAMPLES`
  * TODO `NP_GOODIES_BUILD_TESTS`
* [Library Exports Toggles](#library-exports-toggles) *(As a [list of dependencies])*
  * `NP_GOODIES_EXPORT_ALL` [➜](#everything)
    * `NP_GOODIES_EXPORT_ARGUMENTS`
    * `NP_GOODIES_EXPORT_HASH`
      * `NP_GOODIES_EXPORT_CRC32`
    * `NP_GOODIES_EXPORT_LIST_ALL`
      * `NP_GOODIES_EXPORT_SLLIST`
      * `NP_GOODIES_EXPORT_DLLIST`
    * TODO `hashmaps`
    * TODO `NP_GOODIES_EXPORT_ULID`
    * `NP_GOODIES_EXPORT_UUID_ALL`
      * `NP_GOODIES_EXPORT_UUID4`
      * TODO `NP_GOODIES_EXPORT_UUID6`
      * TODO `NP_GOODIES_EXPORT_UUID7`
    * `NP_GOODIES_EXPORT_TEXT`


## Features Toggles

### UUID Structure size check
**Definition:** `NP_GOODIES_UUID_DISABLE_STRUCT_SIZE_CHECK`

This feature is a "simple" macro that is used at the top of every function in
"[src/uuid/](src/uuid)".<br>
The macro is defined at the end of "[src/uuid/structs.h](src/uuid/structs.h)" and
was implemented by following an article from
"[scaryreasoner.wordpress.com](https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/)".

When compiled, this macro should result in zero code and only exist to cause
compiler errors when the size of the `uuid` structure doesn't match what is expected.

If the ??? is defined, the macro will be empty.<br>
This shouldn't be done unless you have a good reason to and don't use and/or
export the UUID functions.


## Library Exports Toggles
[Note about hierarchy and dependencies.]

### Everything
**Definition:** `NP_GOODIES_EXPORT_ALL`

If defined, every possible function is exported in the library.<br>
This definition overrides any other `NP_GOODIES_EXPORT_*` definition.

### abc
def
