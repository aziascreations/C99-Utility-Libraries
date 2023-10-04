#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/double/dllist.h"

int main(void) {
	// Preparing the lists
	DoubleLinkedList *dllist = dllist_create();
	
	// Populating the list.
	dllist_append(dllist, (void *) 1, NULL);
	dllist_append(dllist, (void *) 2, NULL);
	dllist_append(dllist, (void *) 3, NULL);
	dllist_append(dllist, (void *) 4, NULL);
	dllist_append(dllist, (void *) 5, NULL);
	
	// Sanity checks
	assert(dllist->current == NULL, "Double linked list `*current` is NULL at start.")
	
	
	// --------------------
	//  Absolute selectors
	// --------------------
	
	// Testing selectFirst
	assert(dllist_selectFirst(dllist) != NULL, "selectFirst returned a non-NULL value.")
	assert(dllist->current->data == (void *) 1, "Double linked list `*current` now points at `1`.")
	assert(dllist_selectFirst(dllist)->data == (void *) 1, "selectFirst returned `1`.")
	dllist->current = NULL;
	
	// Testing selectFirstData
	assert(dllist_selectFirstData(dllist) != NULL, "selectFirstData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 1, "Double linked list `*current` now points at `1`.")
	assert(dllist_selectFirstData(dllist) == (void *) 1, "selectFirstData returned `1`.")
	dllist->current = NULL;
	
	// Testing selectLast
	assert(dllist_selectLast(dllist) != NULL, "selectLast returned a non-NULL value.")
	assert(dllist->current->data == (void *) 5, "Double linked list `*current` now points at `5`.")
	assert(dllist_selectLast(dllist)->data == (void *) 5, "selectLast returned `5`.")
	dllist->current = NULL;
	
	// Testing selectLastData
	assert(dllist_selectLastData(dllist) != NULL, "selectLastData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 5, "Double linked list `*current` now points at `5`.")
	assert(dllist_selectLastData(dllist) == (void *) 5, "selectLastData returned `5`.")
	dllist->current = NULL;
	
	
	// ---------------------
	//  Index-based getters
	// ---------------------
	
	// Testing getByIndex
	assert(dllist_getByIndex(dllist, 2) != NULL, "getByIndex(2) returned a non-NULL value.")
	assert(dllist->current == NULL, "Double linked list `*current` is still NULL.")
	assert(dllist_getByIndex(dllist, 2)->data == (void *) 3, "getByIndex(2) returned `3`.")
	
	// Testing selectByIndex
	assert(dllist_selectByIndex(dllist, 2) != NULL, "selectByIndex(2) returned a non-NULL value.")
	assert(dllist->current->data == (void *) 3, "Double linked list `*current` now points at `3`.")
	assert(dllist_selectByIndex(dllist, 2)->data == (void *) 3, "selectByIndex(2) returned `3`.")
	dllist->current = NULL;
	
	// Testing out-of-bounds conditions
	assert(dllist_getByIndex(dllist, 999) == NULL, "getByIndex(999) returned a NULL value.")
	assert(dllist->current == NULL, "Double linked list `*current` is still NULL.")
	assert(dllist_selectByIndex(dllist, 999) == NULL, "selectByIndex(999) returned a NULL value.")
	assert(dllist->current == NULL, "Double linked list `*current` is still NULL.")
	
	
	// ------------------
	//  Relative getters
	// ------------------
	
	// Testing getPrevious
	dllist_selectByIndex(dllist, 2);
	assert(dllist_getPrevious(dllist) != NULL, "getPrevious returned a non-NULL value.")
	assert(dllist->current->data == (void *) 3, "Double linked list `*current` still points at `3`.")
	assert(dllist_getPrevious(dllist)->data == (void *) 2, "getPrevious returned `2`.")
	dllist->current = NULL;
	assert(dllist_getPrevious(dllist) == NULL, "getPrevious returned NULL when `*current` is NULL.")
	
	// Testing getPreviousData
	dllist_selectByIndex(dllist, 2);
	assert(dllist_getPreviousData(dllist) != NULL, "getPreviousData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 3, "Double linked list `*current` still points at `3`.")
	assert(dllist_getPreviousData(dllist) == (void *) 2, "getPreviousData returned `2`.")
	dllist->current = NULL;
	assert(dllist_getPreviousData(dllist) == NULL, "getPreviousData returned NULL when `*current` is NULL.")
	
	// Testing getNext
	dllist_selectByIndex(dllist, 2);
	assert(dllist_getNext(dllist) != NULL, "getNext returned a non-NULL value.")
	assert(dllist->current->data == (void *) 3, "Double linked list `*current` still points at `3`.")
	assert(dllist_getNext(dllist)->data == (void *) 4, "getNext returned `4`.")
	dllist->current = NULL;
	assert(dllist_getNext(dllist) == NULL, "getNext returned NULL when `*current` is NULL.")
	
	// Testing getNextData
	dllist_selectByIndex(dllist, 2);
	assert(dllist_getNextData(dllist) != NULL, "getNextData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 3, "Double linked list `*current` still points at `3`.")
	assert(dllist_getNextData(dllist) == (void *) 4, "getNextData returned `4`.")
	dllist->current = NULL;
	assert(dllist_getNextData(dllist) == NULL, "getNextData returned NULL when `*current` is NULL.")
	
	
	// --------------------
	//  Relative selectors
	// --------------------
	
	// Testing selectPrevious
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectPrevious(dllist) != NULL, "selectPrevious returned a non-NULL value.")
	assert(dllist->current->data == (void *) 2, "Double linked list `*current` now points at `2`.")
	
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectPrevious(dllist)->data == (void *) 2, "selectPrevious returned `2`.")
	
	dllist_selectFirst(dllist);
	assert(dllist_selectPrevious(dllist) == NULL, "selectPrevious returned NULL when `*current` == `*first`.")
	assert(dllist->current == NULL, "selectPrevious set `*current` to NULL when `*current` == `*first`.")
	
	dllist->current = NULL;
	assert(dllist_selectPrevious(dllist) == NULL, "selectPrevious returned NULL when `*current` is NULL.")
	
	// Testing selectPreviousData
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectPreviousData(dllist) != NULL, "selectPreviousData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 2, "Double linked list `*current` now points at `2`.")
	
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectPreviousData(dllist) == (void *) 2, "selectPreviousData returned `2`.")
	
	dllist_selectFirst(dllist);
	assert(dllist_selectPreviousData(dllist) == NULL, "selectPreviousData returned NULL when `*current` == `*first`.")
	assert(dllist->current == NULL, "selectPreviousData set `*current` to NULL when `*current` == `*first`.")
	
	dllist->current = NULL;
	assert(dllist_selectPreviousData(dllist) == NULL, "selectPreviousData returned NULL when `*current` is NULL.")
	
	// Testing selectNext
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectNext(dllist) != NULL, "selectNext returned a non-NULL value.")
	assert(dllist->current->data == (void *) 4, "Double linked list `*current` now points at `4`.")
	
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectNext(dllist)->data == (void *) 4, "selectNext returned `4`.")
	
	dllist_selectLast(dllist);
	assert(dllist_selectNext(dllist) == NULL, "selectNext returned NULL when `*current` == `*last`.")
	assert(dllist->current == NULL, "selectNext set `*current` to NULL when `*current` == `*last`.")
	
	dllist->current = NULL;
	assert(dllist_selectNext(dllist) == NULL, "selectNext returned NULL when `*current` is NULL.")
	
	// Testing selectNextData
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectNextData(dllist) != NULL, "selectNextData returned a non-NULL value.")
	assert(dllist->current->data == (void *) 4, "Double linked list `*current` now points at `4`.")
	
	dllist_selectByIndex(dllist, 2);
	assert(dllist_selectNextData(dllist) == (void *) 4, "selectNextData returned `4`.")
	
	dllist_selectLast(dllist);
	assert(dllist_selectNextData(dllist) == NULL, "selectNextData returned NULL when `*current` == `*last`.")
	assert(dllist->current == NULL, "selectNextData set `*current` to NULL when `*current` == `*last`.")
	
	dllist->current = NULL;
	assert(dllist_selectNextData(dllist) == NULL, "selectNextData returned NULL when `*current` is NULL.")
	
	
	// -------------
	//  End of test
	// -------------
	
	// Freeing the memory
	dllist_free(dllist, NULL, NULL);
}
