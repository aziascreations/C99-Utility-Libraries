#include "ini.h"

#include <stdlib.h>

#include "../hash/crc32/crc32.h"

/** @defgroup group_ini INI config parser
 *
 * TODO: Simple module description
 *
 * <b>Warning:</b><br>
 * Any reference to a *sub-verb* actually refers to a regular \ref arguments_verb "Verb" which can be considered as the
 *  another verb's children.
 *
 * Any reference to `np_args_char` can be the equivalent of `char` or `wchar_t` depending on 2 compiler constants.<br>
 * These constants, `NP_WIN32` and `NP_ARGS_WCHAR`, if both used, will make all functions and structures in this module
 *  use `wchar_t` strings instead of `char` ones.<br>
 * This features allows you to easily handle unicode characters and emojis in launch arguments on Windows platforms.
 *
 * These macro-ed types and functions are defined in \ref arguments/macros.h.<br>
 * This header also defines a bunch of macros for string-related operations done in this module.<br>
 * They shouldn't be used outside of it !
 *
 * If you want an example of this feature on a Windows app, you should check
 *  [aziascreations/C99-Win32-Wifi-Utility](https://github.com/aziascreations/C99-Win32-Wifi-Utility) on GitHub.
 *
 * @{
 */

#include "../debug.h"

// Creators

IniData *ini_create(IniOptions options) {
	IniData *ini = malloc(sizeof(IniData));
	
	if(ini != NULL) {
		ini->options = options;
		ini->groups = NULL;
	}
	
	return ini;
}

IniGroupData *ini_createGroup(np_ini_char *name) {
	IniGroupData *iniGroup = malloc(sizeof(IniGroupData));
	
	if(iniGroup != NULL) {
		iniGroup->name = np_ini_copyString(name);
		iniGroup->primitives = NULL;
		iniGroup->lists = NULL;
		iniGroup->maps = NULL;
		iniGroup->parentIni = NULL;
	}
	
	return iniGroup;
}


// Cleaners

void ini_free(IniData *ini) {
	if(ini != NULL) {
		if(ini->groups != NULL) {
			np_ini_hashmapFree((np_ini_hashmap *) ini->groups, (void (*)(void *)) &ini_freeGroup);
		}
		free(ini);
	}
}

void ini_freeGroup(IniGroupData *iniGroup) {
	if(iniGroup != NULL) {
		trace_println("INI: Freeing group '%s' @%p", iniGroup->name, iniGroup);
		free(iniGroup->name);
		free(iniGroup);
	}
}


// Registers

bool ini_registerGroup(IniData *ini, IniGroupData *iniGroup) {
	if(ini == NULL || iniGroup == NULL) {
		trace_println("INI: Given root and/or group is NULL ! => @%p & @%p", ini, groupName);
		return false;
	}
	
	if(iniGroup->parentIni != NULL) {
		trace_println("INI: Given group is already registered ! => @%p to @%p", iniGroup, iniGroup->parentIni);
		return false;
	}
	
	if(ini->groups == NULL) {
		trace_println("INI: Creating root's group hashmap => %u", ini->options.hashmapSizePower);
		ini->groups = (HashMap *) np_ini_hashmapCreate(ini->options.hashmapSizePower);
		
		if(ini->groups == NULL) {
			error_println("INI: Failed to create a hashmap with '%u' as its size power !", ini->options.hashmapSizePower);
			return false;
		}
	}
	
	if(np_ini_hashmapOverwriteByHash((np_ini_hashmap *) ini->groups, iniGroup,
									 hash_crc32b(iniGroup->name, np_ini_strlen(iniGroup->name) * sizeof(np_ini_char)),
									 NULL)) {
		iniGroup->parentIni = ini;
		return true;
	} else {
		trace_println("INI: Couldn't register group due to hashmap-related reasons");
		return false;
	}
}


// Getters

IniGroupData *ini_getGroup(IniData *ini, np_ini_char *groupName) {
	if(ini == NULL || groupName == NULL) {
		trace_println("INI: Given root and/or name is NULL ! => @%p & @%p", ini, groupName);
		return NULL;
	}
	
	if(ini->groups == NULL) {
		trace_println("INI: Root @%p doesn't have any group !", ini);
		return NULL;
	}
	
	size_t groupNameLength = np_ini_strlen(groupName);
	
	if(groupNameLength <= 0) {
		trace_println("INI: Given name's length is 0 !");
		return NULL;
	}
	
	return np_ini_hashmapGetByHash(
			(np_ini_hashmap *) ini->groups,
			hash_crc32b(groupName, groupNameLength * sizeof(np_ini_char)));
}

/** @} */ // end of group_ini
