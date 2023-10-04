#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/single/sllist.h"

SingleLinkedList *getTestList() {
	SingleLinkedList *testList = sllist_create();
	sllist_append(testList, (void *) 1, NULL);
	sllist_append(testList, (void *) 2, NULL);
	sllist_append(testList, (void *) 3, NULL);
	sllist_append(testList, (void *) 4, NULL);
	return testList;
}

int main(void) {
	SingleLinkedList *sllist;
	
	// Testing deleteFirst
	sllist = getTestList();
	assert(!sllist_deleteFirst(NULL, NULL, NULL), "deleteFirst > Failure when no list is given.")
	
	assert(sllist_deleteFirst(sllist, NULL, NULL), "deleteFirst > Success when none selected.")
	assert(sllist->first != NULL, "deleteFirst > `*first` isn't NULL.")
	assert(sllist->current == NULL, "deleteFirst > `*current` is still NULL.")
	assert(sllist->first->data == (void *) 2, "deleteFirst > `*first` points at `2`.")
	
	sllist_selectLast(sllist);
	
	assert(sllist_deleteFirst(sllist, NULL, NULL), "deleteFirst > Success when last selected.")
	assert(sllist->current != NULL, "deleteFirst > `*current` isn't NULL.")
	assert(sllist->current == sllist->last, "deleteFirst > `*current` is still `*current`.")
	assert(sllist->first->data == (void *) 3, "deleteFirst > `*first` points at `3`.")
	
	sllist_selectFirst(sllist);
	
	assert(sllist_deleteFirst(sllist, NULL, NULL), "deleteFirst > Success when first selected.")
	assert(sllist->current == NULL, "deleteFirst > `*current` is back at NULL.")
	assert(sllist->first->data == (void *) 4, "deleteFirst > `*first` points at `4`.")
	
	assert(sllist_deleteFirst(sllist, NULL, NULL), "deleteFirst > Success when last node removed.")
	assert(sllist->first == NULL, "deleteFirst > `*first` is NULL.")
	assert(sllist->current == NULL, "deleteFirst > `*current` is NULL.")
	assert(sllist->last == NULL, "deleteFirst > `*last` is NULL.")
	assert(sllist->size == 0, "deleteFirst > `size` is `0`.")
	
	assert(!sllist_deleteFirst(sllist, NULL, NULL), "deleteFirst > Failure when no nodes left before removal.")
	
	sllist_free(sllist, NULL, NULL);
	
	
	// Testing deleteLast
	sllist = getTestList();
	assert(!sllist_deleteLast(NULL, NULL, NULL), "deleteLast > Failure when no list is given.")
	
	assert(sllist_deleteLast(sllist, NULL, NULL), "deleteLast > Success when none selected.")
	assert(sllist->last != NULL, "deleteLast > `*last` isn't NULL.")
	assert(sllist->current == NULL, "deleteLast > `*current` is still NULL.")
	assert(sllist->last->data == (void *) 3, "deleteLast > `*last` points at `3`.")
	assert(sllist->last->next == NULL, "deleteLast > `*last` has no value in `*next`.")
	
	sllist_selectFirst(sllist);
	
	assert(sllist_deleteLast(sllist, NULL, NULL), "deleteLast > Success when first selected.")
	assert(sllist->current != NULL, "deleteLast > `*current` isn't NULL.")
	assert(sllist->current == sllist->first, "deleteLast > `*current` is still `*current`.")
	assert(sllist->last->data == (void *) 2, "deleteLast > `*last` points at `2`.")
	
	sllist_selectLast(sllist);
	
	assert(sllist_deleteLast(sllist, NULL, NULL), "deleteLast > Success when last selected.")
	assert(sllist->current == NULL, "deleteLast > `*current` is back at NULL.")
	assert(sllist->last->data == (void *) 1, "deleteLast > `*last` points at `1`.")
	
	assert(sllist_deleteLast(sllist, NULL, NULL), "deleteLast > Success when last node removed.")
	assert(sllist->first == NULL, "deleteLast > `*first` is NULL.")
	assert(sllist->current == NULL, "deleteLast > `*current` is NULL.")
	assert(sllist->last == NULL, "deleteLast > `*last` is NULL.")
	assert(sllist->size == 0, "deleteLast > `size` is `0`.")
	
	assert(!sllist_deleteLast(sllist, NULL, NULL), "deleteLast > Failure when no nodes left before removal.")
	
	sllist_free(sllist, NULL, NULL);
	
	
	// Testing deleteCurrent
	sllist = getTestList();
	assert(!sllist_deleteCurrent(NULL, NULL, NULL), "deleteCurrent > Failure when no list is given.")
	
	sllist->current = NULL;  // Just to be 101% sure.
	assert(!sllist_deleteCurrent(sllist, NULL, NULL), "deleteCurrent > Failure when `*current` is NULL.")
	
	sllist_selectByIndex(sllist, 1);
	assert(sllist_deleteCurrent(sllist, NULL, NULL), "deleteCurrent > Success 2nd selected.")
	assert(sllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(sllist->first->next->data == (void *) 3, "deleteCurrent > `*first` via `*next` points at `3`.")
	
	sllist_selectFirst(sllist);
	assert(sllist_deleteCurrent(sllist, NULL, NULL), "deleteCurrent > Success `*first` selected.")
	assert(sllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(sllist->first->data == (void *) 3, "deleteCurrent > `*first` points at `3`.")
	assert(sllist->first->next->data == (void *) 4, "deleteCurrent > `*first` via `*next` points at `4`.")
	
	sllist_selectLast(sllist);
	assert(sllist_deleteCurrent(sllist, NULL, NULL), "deleteCurrent > Success `*last` selected.")
	assert(sllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(sllist->first->data == (void *) 3, "deleteCurrent > `*first` points at `3`.")
	assert(sllist->last->data == (void *) 3, "deleteCurrent > `*last` points at `3`.")
	assert(sllist->last->next == NULL, "deleteCurrent > `*last` points at NULL via `*next`.")
	
	sllist_free(sllist, NULL, NULL);
	
	return 0;
}
