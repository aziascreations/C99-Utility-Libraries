#include <stdio.h>

#include "../assert.h"

#include "../../src/ini/ini.h"

np_ini_char *groupName1 = np_ini_L("test_group_01");
np_ini_char *groupName2 = np_ini_L("test_group_02");

int main(void) {
	printf("Testing 'registration of INI components'...\n");
	
	IniData *ini = ini_create((IniOptions) {
			.mergeGroups = true,
			.hashmapSizePower = 4,
	});
	printf("> Checking root's allocation...\n");
	assert(ini != NULL, "We got a pointer");
	
	IniGroupData *iniGroup1 = ini_createGroup(groupName1);
	printf("> Checking group #1 allocation...\n");
	assert(iniGroup1 != NULL, "We got a pointer");
	assert(np_ini_areStringsEqual(iniGroup1->name, groupName1), "The group has the same name");
	assert(iniGroup1->name != groupName1, "The group has copied the name, not referenced it");
	
	IniGroupData *iniGroup1Bis = ini_createGroup(groupName1);
	printf("> Checking group #1.bis allocation...\n");
	assert(iniGroup1 != NULL, "Group 1(bis) has been allocated");
	
	IniGroupData *iniGroup2 = ini_createGroup(groupName2);
	printf("> Checking group #2 allocation...\n");
	assert(iniGroup1 != NULL, "Group 2 has been allocated");
	
	printf("> Checking registration function parameter failures...\n");
	assert(!ini_setGroup(ini, NULL), "Cannot register NULL group");
	assert(!ini_setGroup(NULL, iniGroup1), "Cannot register into NULL IniData");
	assert(!ini_setGroup(NULL, NULL), "Cannot register NULL into NULL");
	
	printf("> Checking registration function normal operations...\n");
	assert(ini_setGroup(ini, iniGroup1), "Registered group #1 properly");
	assert(ini->groups != NULL, "The internal HashMap isn't NULL");
	assert(ini->groups->entryCount == 1, "The internal HashMap has 1 entry");
	assert(iniGroup1->parentIni == ini, "Group #1 parent is set");
	
	iniGroup2->parentIni = (void*) 420;
	assert(!ini_setGroup(ini, iniGroup2), "Cannot register group #2 with faked parent");
	iniGroup2->parentIni = NULL;
	assert(ini_setGroup(ini, iniGroup2), "Registered group #2 properly, parent was set back to NULL");
	assert(ini->groups->entryCount == 2, "The internal HashMap has 2 entries");
	assert(iniGroup2->parentIni == ini, "Group #2 parent is set");
	
	assert(!ini_setGroup(ini, iniGroup2), "Cannot register group #1 again");
	assert(!ini_setGroup(ini, iniGroup2), "Cannot register group #2 again");
	assert(ini->groups->entryCount == 2, "The internal HashMap still has 2 entries");
	
	assert(!ini_setGroup(ini, iniGroup1Bis), "Cannot register group #1.bis, identical name to #1");
	assert(ini->groups->entryCount == 2, "The internal HashMap still has 2 entries");
	assert(iniGroup1Bis->parentIni == NULL, "Group #1.bis parent is intact");
	
	printf("> Checking group deregistration function parameter failures...\n");
	assert(ini_deregisterGroup(ini, np_ini_L("nope")) == NULL, "Cannot remove fake group")
	assert(ini_deregisterGroup(NULL, np_ini_L("nope")) == NULL, "Cannot remove group from NULL")
	assert(ini_deregisterGroup(ini, NULL) == NULL, "Cannot remove NULL group")
	
	printf("> Checking group deregistration function parameter success...\n");
	assert(ini_deregisterGroup(ini, groupName2) == iniGroup2, "Removed group #2, and got its pointer back")
	assert(iniGroup2->parentIni == NULL, "Group #2's parent is NULL again")
	assert(ini->groups->entryCount == 1, "The internal HashMap has 1 entry");
	assert(ini_deregisterGroup(ini, groupName2) == NULL, "Cannot remove group #2 again")
	
	printf("> Preparing for deletion tests...\n");
	assert(ini_setGroup(ini, iniGroup2), "Registered group #2 again for testing");
	assert(ini->groups->entryCount == 2, "The internal HashMap has 2 entry");
	
	printf("> Checking group deletion function parameter failures...\n");
	assert(!ini_deleteGroup(ini, np_ini_L("nope")), "Cannot delete fake group")
	assert(!ini_deleteGroup(NULL, np_ini_L("nope")), "Cannot delete group from NULL")
	assert(!ini_deleteGroup(ini, NULL), "Cannot delete NULL group")
	
	printf("> Checking group deletion function parameter success...\n");
	assert(ini_deleteGroup(ini, groupName2), "Deleted and freed group #2")
	assert(ini->groups->entryCount == 1, "The internal HashMap has 1 entry");
	
	// Freeing this one before "ini" ensures the test will crash if it has been referenced inside "ini".
	ini_freeGroup(iniGroup1Bis);
	
	// Check for proper freeing of groups via trace prints, or hashmap related tests.
	ini_free(ini);
}
