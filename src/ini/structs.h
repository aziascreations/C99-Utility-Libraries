/// @file structs.h

#if !defined(NP_ONCE_C99_GOODIES_INI_COMMONS_STRUCTS)
#define NP_ONCE_C99_GOODIES_INI_COMMONS_STRUCTS

#include <stdbool.h>
#include <stdint.h>

#include "./macros.h"

#include "../hashmaps/structs.h"
#include "../lists/structs.h"

// FIXME: Use something like the args for changing backend hashmap handling

/** @addtogroup group_ini
 *  @{
 */

#define INI_ROOT_GROUP_NAME np_args_L("np_ini_root")

typedef struct ini_options {
	/**
	 * Specifies whether distinct groups with an identical name should be merged by the parser.<br>
	 * It is recommended to leave this option as `true`.
	 */
	bool mergeGroups;
	
	/**
	 * Specifies the size power used when initializing hashmaps internally.<br>
	 * This value only affects newly created hashmaps.
	 */
	uint8_t hashmapSizePower;
} IniOptions;

typedef struct ini_data {
	IniOptions options;
	
	HashMap *groups;
} IniData;

typedef struct ini_group_data {
	/**
	 * Group's name without the leading and trailing brackets.
	 */
	np_ini_char *name;
	
	HashMap *primitives;
	HashMap *lists;
	HashMap *maps;
	
	// Used to prevent double registrations.
	IniData *parentIni;
} IniGroupData;

/** @} */ // end of group_ini

#endif /* !NP_ONCE_C99_GOODIES_INI_COMMONS_STRUCTS */
