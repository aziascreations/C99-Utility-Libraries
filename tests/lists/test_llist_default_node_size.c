#include <stdio.h>

#include "../assert.h"
#include "../memutils.h"

#include "../../src/lists/double/dllist.h"
#include "../../src/lists/single/sllist.h"

int main(void) {
	// Preparing the lists and adding an empty node in each.
	SingleLinkedList *sllist = sllist_create();
	DoubleLinkedList *dllist = dllist_create();
	
	// Adding an empty node in each list.
	sllist_append(sllist, NULL, NULL);
	dllist_append(dllist, NULL, NULL);
	
	// Preliminary tests
	assert(sllist->size == 1, "Single linked list has 1 node.");
	assert(sllist->first != NULL, "Single linked list's node isn't NULL.");
	
	assert(dllist->size == 1, "Double linked list has 1 node.");
	assert(dllist->first != NULL, "Double linked list's node isn't NULL.");
	
	// Checking the size
	assert(memUtils_getSize(sllist->first) == sizeof(SingleLinkedListNode), "Single linked node struct size");
	assert(memUtils_getSize(dllist->first) == sizeof(DoubleLinkedListNode), "Double linked node struct size");
	
	// Freeing the memory
	sllist_free(sllist, NULL, NULL);
	dllist_free(dllist, NULL, NULL);
}
