#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/double/dllist.h"

DoubleLinkedList *getTestList() {
	DoubleLinkedList *testList = dllist_create();
	dllist_append(testList, (void *) 1, NULL);
	dllist_append(testList, (void *) 2, NULL);
	dllist_append(testList, (void *) 3, NULL);
	dllist_append(testList, (void *) 4, NULL);
	return testList;
}

int main(void) {
	DoubleLinkedList *dllist;
	
	// Testing deleteFirst
	dllist = getTestList();
	assert(!dllist_deleteFirst(NULL, NULL, NULL), "deleteFirst > Failure when no list is given.")
	
	assert(dllist_deleteFirst(dllist, NULL, NULL), "deleteFirst > Success when none selected.")
	assert(dllist->first != NULL, "deleteFirst > `*first` isn't NULL.")
	assert(dllist->current == NULL, "deleteFirst > `*current` is still NULL.")
	assert(dllist->first->data == (void *) 2, "deleteFirst > `*first` points at `2`.")
	assert(dllist->first->previous == NULL, "deleteFirst > `*first` has no value in `*previous`.")
	
	dllist_selectLast(dllist);
	
	assert(dllist_deleteFirst(dllist, NULL, NULL), "deleteFirst > Success when last selected.")
	assert(dllist->current != NULL, "deleteFirst > `*current` isn't NULL.")
	assert(dllist->current == dllist->last, "deleteFirst > `*current` is still `*current`.")
	assert(dllist->first->data == (void *) 3, "deleteFirst > `*first` points at `3`.")
	
	dllist_selectFirst(dllist);
	
	assert(dllist_deleteFirst(dllist, NULL, NULL), "deleteFirst > Success when first selected.")
	assert(dllist->current == NULL, "deleteFirst > `*current` is back at NULL.")
	assert(dllist->first->data == (void *) 4, "deleteFirst > `*first` points at `4`.")
	
	assert(dllist_deleteFirst(dllist, NULL, NULL), "deleteFirst > Success when last node removed.")
	assert(dllist->first == NULL, "deleteFirst > `*first` is NULL.")
	assert(dllist->current == NULL, "deleteFirst > `*current` is NULL.")
	assert(dllist->last == NULL, "deleteFirst > `*last` is NULL.")
	assert(dllist->size == 0, "deleteFirst > `size` is `0`.")
	
	assert(!dllist_deleteFirst(dllist, NULL, NULL), "deleteFirst > Failure when no nodes left before removal.")
	
	dllist_free(dllist, NULL, NULL);
	
	
	// Testing deleteLast
	dllist = getTestList();
	assert(!dllist_deleteLast(NULL, NULL, NULL), "deleteLast > Failure when no list is given.")
	
	assert(dllist_deleteLast(dllist, NULL, NULL), "deleteLast > Success when none selected.")
	assert(dllist->last != NULL, "deleteLast > `*last` isn't NULL.")
	assert(dllist->current == NULL, "deleteLast > `*current` is still NULL.")
	assert(dllist->last->data == (void *) 3, "deleteLast > `*last` points at `3`.")
	assert(dllist->last->next == NULL, "deleteLast > `*last` has no value in `*next`.")
	
	dllist_selectFirst(dllist);
	
	assert(dllist_deleteLast(dllist, NULL, NULL), "deleteLast > Success when first selected.")
	assert(dllist->current != NULL, "deleteLast > `*current` isn't NULL.")
	assert(dllist->current == dllist->first, "deleteLast > `*current` is still `*current`.")
	assert(dllist->last->data == (void *) 2, "deleteLast > `*last` points at `2`.")
	
	dllist_selectLast(dllist);
	
	assert(dllist_deleteLast(dllist, NULL, NULL), "deleteLast > Success when last selected.")
	assert(dllist->current == NULL, "deleteLast > `*current` is back at NULL.")
	assert(dllist->last->data == (void *) 1, "deleteLast > `*last` points at `1`.")
	
	assert(dllist_deleteLast(dllist, NULL, NULL), "deleteLast > Success when last node removed.")
	assert(dllist->first == NULL, "deleteLast > `*first` is NULL.")
	assert(dllist->current == NULL, "deleteLast > `*current` is NULL.")
	assert(dllist->last == NULL, "deleteLast > `*last` is NULL.")
	assert(dllist->size == 0, "deleteLast > `size` is `0`.")
	
	assert(!dllist_deleteLast(dllist, NULL, NULL), "deleteLast > Failure when no nodes left before removal.")
	
	dllist_free(dllist, NULL, NULL);
	
	
	// Testing deleteCurrent
	dllist = getTestList();
	assert(!dllist_deleteCurrent(NULL, NULL, NULL), "deleteCurrent > Failure when no list is given.")
	
	dllist->current = NULL;  // Just to be 101% sure.
	assert(!dllist_deleteCurrent(dllist, NULL, NULL), "deleteCurrent > Failure when `*current` is NULL.")
	
	dllist_selectByIndex(dllist, 1);
	assert(dllist_deleteCurrent(dllist, NULL, NULL), "deleteCurrent > Success 2nd selected.")
	assert(dllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(dllist->first->next->data == (void *) 3, "deleteCurrent > `*first` via `*next` points at `3`.")
	assert(dllist->first->next->previous->data == (void *) 1, "deleteCurrent > `*first` points to node whose `*previous` points at `1`.")
	
	dllist_selectFirst(dllist);
	assert(dllist_deleteCurrent(dllist, NULL, NULL), "deleteCurrent > Success `*first` selected.")
	assert(dllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(dllist->first->data == (void *) 3, "deleteCurrent > `*first` points at `3`.")
	assert(dllist->first->previous == NULL, "deleteCurrent > `*first` points to NULL via `*previous`.")
	assert(dllist->first->next->data == (void *) 4, "deleteCurrent > `*first` via `*next` points at `4`.")
	assert(dllist->first->next->previous->data == (void *) 3, "deleteCurrent > `*first` points to node whose `*previous` points at `3`.")
	
	dllist_selectLast(dllist);
	assert(dllist_deleteCurrent(dllist, NULL, NULL), "deleteCurrent > Success `*last` selected.")
	assert(dllist->current == NULL, "deleteCurrent > `*current` is back at NULL.")
	assert(dllist->first->data == (void *) 3, "deleteCurrent > `*first` points at `3`.")
	assert(dllist->last->data == (void *) 3, "deleteCurrent > `*last` points at `3`.")
	assert(dllist->last->previous == NULL, "deleteCurrent > `*last` points at NULL via `*previous`.")
	assert(dllist->last->next == NULL, "deleteCurrent > `*last` points at NULL via `*next`.")
	
	dllist_free(dllist, NULL, NULL);
	
	return 0;
}
