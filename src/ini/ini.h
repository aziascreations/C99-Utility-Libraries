/// @file ini.h

#if !defined(NP_ONCE_C99_GOODIES_INI_MAIN)
#define NP_ONCE_C99_GOODIES_INI_MAIN

#include "../platform.h"

#if defined(NP_GOODIES_EXPORT_INI) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_INI NP_DLL_EXPORT
#else
	#define DLL_EXP_INI
#endif

#include "./macros.h"
#include "./structs.h"

// Macros

#define ini_doesGroupExist(ini) (ini_getGroup(ini) != NULL)

// Creators

/**
 * Creates a \ref ini_data "IniData" with a given config and no groups.
 * @param options A \ref ini_options "IniParserOptions" passed on the stack that represents the INI's file config.
 * @return The new \ref ini_data "IniData"'s pointer, or <code>NULL</code> if an error occurred.
 */
DLL_EXP_INI IniData *ini_create(IniOptions options);

/**
 * Creates a \ref ini_group_data "IniGroupData" with a given config and no groups.
 * @param name Group's name used when searching for it or printing out the data.
 * @return The new \ref ini_group_data "IniGroupData"'s pointer, or <code>NULL</code> if an error occurred.
 */
DLL_EXP_INI IniGroupData *ini_createGroup(np_ini_char *name);

// Cleaners

DLL_EXP_INI void ini_free(IniData *ini);

DLL_EXP_INI void ini_freeGroup(IniGroupData *iniGroup);

// Removers

DLL_EXP_INI IniGroupData* ini_deregisterGroup(IniData *ini, np_ini_char *groupName);

DLL_EXP_INI bool ini_deleteGroup(IniData *ini, np_ini_char *groupName);

// Getters

/**
 * Returns a requested \ref ini_group_data "IniGroupData".
 * @param ini The \ref ini_data "IniData" that contains the requested group.
 * @return The requested \ref ini_group_data "IniGroupData", or <code>NULL</code> if it couldn't be found.
 */
DLL_EXP_INI IniGroupData *ini_getGroup(IniData *ini, np_ini_char *groupName);

DLL_EXP_INI np_ini_char *ini_getPrimitiveReference(IniGroupData *iniGroup, const np_ini_char *primitiveKey);

DLL_EXP_INI np_ini_char *ini_getPrimitiveCopy(IniGroupData *iniGroup, const np_ini_char *primitiveKey);

//DLL_EXP_INI void *ini_getList(IniGroupData *ini, np_ini_char *listName);
//
//DLL_EXP_INI size_t ini_getListSize(IniGroupData *ini, np_ini_char *listName);
//
//DLL_EXP_INI np_ini_char *ini_getListValue(IniGroupData *ini, np_ini_char *listName, size_t valueIndex);

// Setters

/**
 * Adds a given \ref ini_group_data "IniGroupData" to a given \ref ini_data "IniData".
 * @param ini The \ref ini_data "IniData" into which the group is added.
 * @param iniGroup The added \ref ini_group_data "IniGroupData".
 * @return <code>true</code> if the group was added, <code>false</code> if it couldn't or if one with the same name is
 *  already present.
 */
DLL_EXP_INI bool ini_setGroup(IniData *ini, IniGroupData *iniGroup);

/**
 *
 * @param iniGroup
 * @param primitiveKey
 * @param primitiveValue
 * @param overwriteAndFree
 * @return
 * @warning The given primitive data is copied, the original value must be freed accordingly !
 * @warning Usage of references to overwritten primitives will result in errors !
 */
DLL_EXP_INI bool ini_setPrimitive(
		IniGroupData *iniGroup,
		const np_ini_char *primitiveKey,
		const np_ini_char *primitiveValue,
		bool overwriteAndFree);

#endif /* !NP_ONCE_C99_GOODIES_INI_MAIN */