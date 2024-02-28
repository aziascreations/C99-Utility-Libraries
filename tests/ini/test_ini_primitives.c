#include <stdio.h>
#include <stdlib.h>

#include "../assert.h"

#include "../../src/ini/ini.h"

np_ini_char *groupNameRegistered = np_ini_L("registered_group");
np_ini_char *groupNameOrphan = np_ini_L("orphan_group");

np_ini_char *primitive1Key = np_ini_L("key_1");
np_ini_char *primitive1Value = np_ini_L("value_1");
np_ini_char *primitive1ValueAlt = np_ini_L("value_1_alt");

np_ini_char *primitive2Key = np_ini_L("key_2");
np_ini_char *primitive2Value = np_ini_L("value_2");

int main(void) {
	// Temporary values
	np_ini_char *tmpValue = NULL;
	np_ini_char *tmpValueAlt = NULL;
	
	// Code
	printf("Testing 'primitives of INI components'...\n");
	
	printf("> Preparing components...\n");
	IniData *ini = ini_create((IniOptions) {
			.mergeGroups = true,
			.hashmapSizePower = 4,
	});
	assert(ini != NULL, "Root INI was allocated");
	IniGroupData *iniGroupValid = ini_createGroup(groupNameRegistered);
	assert(iniGroupValid != NULL, "Valid group was allocated");
	IniGroupData *iniGroupOrphan = ini_createGroup(groupNameOrphan);
	assert(iniGroupOrphan != NULL, "Orphan group was allocated");
	assert(ini_setGroup(ini, iniGroupValid), "Registered INI group");
	
	printf("> Checking common insertions errors due to invalid parameters...\n");
	assert(iniGroupValid->primitives == NULL, "The primitive list is NULL");
	assert(!ini_setPrimitive(NULL, primitive1Key, primitive1Value, true), "Group is NULL");
	assert(!ini_setPrimitive(iniGroupValid, NULL, primitive1Value, true), "Key is NULL");
	assert(!ini_setPrimitive(iniGroupValid, primitive1Key, NULL, true), "Value is NULL");
	assert(iniGroupValid->primitives == NULL, "The primitive list is still NULL");
	
	printf("> Checking common insertions errors due to invalid pre-conditions...\n");
	assert(iniGroupOrphan->primitives == NULL, "The orphan's primitive list is NULL");
	assert(!ini_setPrimitive(iniGroupOrphan, primitive1Key, primitive1Value, true), "Unable to insert in orphan group");
	assert(iniGroupOrphan->primitives == NULL, "The orphan's primitive list is still NULL");
	
	
	printf("> Checking valid insertions into non-orphan group...\n");
	assert(iniGroupValid->primitives == NULL, "The valid group's primitive list is NULL");
	assert(ini_setPrimitive(iniGroupValid, primitive1Key, primitive1Value, false), "Inserted value #1 (overwrite => false)");
	assert(iniGroupValid->primitives != NULL, "The valid group's primitive list is no longer NULL");
	assert(iniGroupValid->primitives->entryCount == 1, "Internal primitive list has 1 entry");
	
	
	printf("> Checking reference getters for non-orphan group...\n");
	tmpValue = ini_getPrimitiveReference(iniGroupValid, primitive2Key);
	assert(tmpValue == NULL, "Unable to get value #2, got NULL");
	
	tmpValue = ini_getPrimitiveReference(iniGroupValid, primitive1Key);
	assert(tmpValue != NULL, "Got value #1 as a reference");
	assert(tmpValue != primitive1Value, "The pointer doesn't match the original value, it was copied");
	
	tmpValueAlt = ini_getPrimitiveReference(iniGroupValid, primitive1Key);
	assert(tmpValueAlt == tmpValue, "We get identical pointers for repeated calls");
	tmpValue = NULL;
	tmpValueAlt = NULL;
	
	
	printf("> Checking copy getters for non-orphan group...\n");
	tmpValue = ini_getPrimitiveCopy(iniGroupValid, primitive2Key);
	assert(tmpValue == NULL, "Unable to get value #2, got NULL");
	
	tmpValue = ini_getPrimitiveCopy(iniGroupValid, primitive1Key);
	assert(tmpValue != NULL, "Got value #1 as a copy");
	assert(tmpValue != primitive1Value, "The pointer doesn't match the original value, it was copied");
	
	tmpValueAlt = ini_getPrimitiveReference(iniGroupValid, primitive1Key);
	assert(tmpValueAlt != tmpValue, "The copy pointer is different from the reference one");
	tmpValueAlt = NULL;
	
	tmpValueAlt = ini_getPrimitiveCopy(iniGroupValid, primitive1Key);
	assert(tmpValueAlt != NULL, "Got value #1 as another copy");
	assert(tmpValueAlt != tmpValue, "The 2 copies don't point to the same data");
	
	free(tmpValue);
	tmpValue = NULL;
	free(tmpValueAlt);
	tmpValueAlt = NULL;
	
	
	printf("> Attempting to overwrite values...\n");
	assert(ini_setPrimitive(iniGroupValid, primitive2Key, primitive2Value, true), "Inserted value #2 (overwrite => true)");
	assert(iniGroupValid->primitives->entryCount == 2, "Internal primitive list has 2 entry");
	
	assert(!ini_setPrimitive(iniGroupValid, primitive1Key, primitive1ValueAlt, false), "Cannot re-insert value #1 without override");
	assert(iniGroupValid->primitives->entryCount == 2, "Internal primitive list still has 2 entry");
	
	assert(ini_setPrimitive(iniGroupValid, primitive1Key, primitive1ValueAlt, true), "Overwritten value #1");
	assert(iniGroupValid->primitives->entryCount == 2, "Internal primitive list still has 2 entry");
	
	
	printf("> Checking new values...\n");
	tmpValue = ini_getPrimitiveCopy(iniGroupValid, primitive1Key);
	tmpValueAlt = ini_getPrimitiveCopy(iniGroupValid, primitive2Key);
	assert(tmpValue != NULL, "Got value #1 as another copy");
	assert(tmpValueAlt != NULL, "Got value #2 as another copy");
	assert(tmpValue != tmpValueAlt, "Values are different pointers (Sanity check)");
	
	assert(!np_ini_areStringsEqual(tmpValue, primitive1Value), "Value #1 doesn't have old value");
	assert(np_ini_areStringsEqual(tmpValue, primitive1ValueAlt), "Value #1 has expected value");
	assert(np_ini_areStringsEqual(tmpValueAlt, primitive2Value), "Value #2 has expected value");
	
	free(tmpValue);
	tmpValue = NULL;
	free(tmpValueAlt);
	tmpValueAlt = NULL;
	
	
	printf("> Checking new values as references for sanity check...\n");
	tmpValue = ini_getPrimitiveReference(iniGroupValid, primitive1Key);
	tmpValueAlt = ini_getPrimitiveReference(iniGroupValid, primitive2Key);
	assert(tmpValue != tmpValueAlt, "References to #1 and #2 are different");
	assert(np_ini_areStringsEqual(tmpValue, primitive1ValueAlt), "Reference #1 has expected value");
	assert(np_ini_areStringsEqual(tmpValueAlt, primitive2Value), "Reference #2 has expected value");
	tmpValue = NULL;
	tmpValueAlt = NULL;
	
	
	printf("> Cleaning up...\n");
	ini_freeGroup(iniGroupOrphan);
	ini_free(ini);
}
