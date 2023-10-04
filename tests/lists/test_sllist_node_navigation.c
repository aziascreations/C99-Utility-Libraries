#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/single/sllist.h"

int main(void) {
	// Preparing the lists
	SingleLinkedList *sllist = sllist_create();
	
	// Populating the list.
	sllist_append(sllist, (void *) 1, NULL);
	sllist_append(sllist, (void *) 2, NULL);
	sllist_append(sllist, (void *) 3, NULL);
	sllist_append(sllist, (void *) 4, NULL);
	sllist_append(sllist, (void *) 5, NULL);
	
	// Sanity checks
	assert(sllist->current == NULL, "Single linked list `*current` is NULL at start.")
	
	
	// --------------------
	//  Absolute selectors
	// --------------------
	
	// Testing selectFirst
	assert(sllist_selectFirst(sllist) != NULL, "selectFirst returned a non-NULL value.")
	assert(sllist->current->data == (void *) 1, "Single linked list `*current` now points at `1`.")
	assert(sllist_selectFirst(sllist)->data == (void *) 1, "selectFirst returned `1`.")
	sllist->current = NULL;
	
	// Testing selectFirstData
	assert(sllist_selectFirstData(sllist) != NULL, "selectFirstData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 1, "Single linked list `*current` now points at `1`.")
	assert(sllist_selectFirstData(sllist) == (void *) 1, "selectFirstData returned `1`.")
	sllist->current = NULL;
	
	// Testing selectLast
	assert(sllist_selectLast(sllist) != NULL, "selectLast returned a non-NULL value.")
	assert(sllist->current->data == (void *) 5, "Single linked list `*current` now points at `5`.")
	assert(sllist_selectLast(sllist)->data == (void *) 5, "selectLast returned `5`.")
	sllist->current = NULL;
	
	// Testing selectLastData
	assert(sllist_selectLastData(sllist) != NULL, "selectLastData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 5, "Single linked list `*current` now points at `5`.")
	assert(sllist_selectLastData(sllist) == (void *) 5, "selectLastData returned `5`.")
	sllist->current = NULL;
	
	
	// ---------------------
	//  Index-based getters
	// ---------------------
	
	// Testing getByIndex
	assert(sllist_getByIndex(sllist, 2) != NULL, "getByIndex(2) returned a non-NULL value.")
	assert(sllist->current == NULL, "Single linked list `*current` is still NULL.")
	assert(sllist_getByIndex(sllist, 2)->data == (void *) 3, "getByIndex(2) returned `3`.")
	
	// Testing selectByIndex
	assert(sllist_selectByIndex(sllist, 2) != NULL, "selectByIndex(2) returned a non-NULL value.")
	assert(sllist->current->data == (void *) 3, "Single linked list `*current` now points at `3`.")
	assert(sllist_selectByIndex(sllist, 2)->data == (void *) 3, "selectByIndex(2) returned `3`.")
	sllist->current = NULL;
	
	// Testing out-of-bounds conditions
	assert(sllist_getByIndex(sllist, 999) == NULL, "getByIndex(999) returned a NULL value.")
	assert(sllist->current == NULL, "Single linked list `*current` is still NULL.")
	assert(sllist_selectByIndex(sllist, 999) == NULL, "selectByIndex(999) returned a NULL value.")
	assert(sllist->current == NULL, "Single linked list `*current` is still NULL.")
	
	
	// ------------------
	//  Relative getters
	// ------------------
	
	// Testing getPrevious
	sllist_selectByIndex(sllist, 2);
	assert(sllist_getPrevious(sllist) != NULL, "getPrevious returned a non-NULL value.")
	assert(sllist->current->data == (void *) 3, "Single linked list `*current` still points at `3`.")
	assert(sllist_getPrevious(sllist)->data == (void *) 2, "getPrevious returned `2`.")
	sllist->current = NULL;
	assert(sllist_getPrevious(sllist) == NULL, "getPrevious returned NULL when `*current` is NULL.")
	
	// Testing getPreviousData
	sllist_selectByIndex(sllist, 2);
	assert(sllist_getPreviousData(sllist) != NULL, "getPreviousData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 3, "Single linked list `*current` still points at `3`.")
	assert(sllist_getPreviousData(sllist) == (void *) 2, "getPreviousData returned `2`.")
	sllist->current = NULL;
	assert(sllist_getPreviousData(sllist) == NULL, "getPreviousData returned NULL when `*current` is NULL.")
	
	// Testing getNext
	sllist_selectByIndex(sllist, 2);
	assert(sllist_getNext(sllist) != NULL, "getNext returned a non-NULL value.")
	assert(sllist->current->data == (void *) 3, "Single linked list `*current` still points at `3`.")
	assert(sllist_getNext(sllist)->data == (void *) 4, "getNext returned `4`.")
	sllist->current = NULL;
	assert(sllist_getNext(sllist) == NULL, "getNext returned NULL when `*current` is NULL.")
	
	// Testing getNextData
	sllist_selectByIndex(sllist, 2);
	assert(sllist_getNextData(sllist) != NULL, "getNextData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 3, "Single linked list `*current` still points at `3`.")
	assert(sllist_getNextData(sllist) == (void *) 4, "getNextData returned `4`.")
	sllist->current = NULL;
	assert(sllist_getNextData(sllist) == NULL, "getNextData returned NULL when `*current` is NULL.")
	
	
	// --------------------
	//  Relative selectors
	// --------------------
	
	// Testing selectPrevious
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectPrevious(sllist) != NULL, "selectPrevious returned a non-NULL value.")
	assert(sllist->current->data == (void *) 2, "Single linked list `*current` now points at `2`.")
	
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectPrevious(sllist)->data == (void *) 2, "selectPrevious returned `2`.")
	
	sllist_selectFirst(sllist);
	assert(sllist_selectPrevious(sllist) == NULL, "selectPrevious returned NULL when `*current` == `*first`.")
	assert(sllist->current == NULL, "selectPrevious set `*current` to NULL when `*current` == `*first`.")
	
	sllist->current = NULL;
	assert(sllist_selectPrevious(sllist) == NULL, "selectPrevious returned NULL when `*current` is NULL.")
	
	// Testing selectPreviousData
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectPreviousData(sllist) != NULL, "selectPreviousData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 2, "Single linked list `*current` now points at `2`.")
	
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectPreviousData(sllist) == (void *) 2, "selectPreviousData returned `2`.")
	
	sllist_selectFirst(sllist);
	assert(sllist_selectPreviousData(sllist) == NULL, "selectPreviousData returned NULL when `*current` == `*first`.")
	assert(sllist->current == NULL, "selectPreviousData set `*current` to NULL when `*current` == `*first`.")
	
	sllist->current = NULL;
	assert(sllist_selectPreviousData(sllist) == NULL, "selectPreviousData returned NULL when `*current` is NULL.")
	
	// Testing selectNext
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectNext(sllist) != NULL, "selectNext returned a non-NULL value.")
	assert(sllist->current->data == (void *) 4, "Single linked list `*current` now points at `4`.")
	
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectNext(sllist)->data == (void *) 4, "selectNext returned `4`.")
	
	sllist_selectLast(sllist);
	assert(sllist_selectNext(sllist) == NULL, "selectNext returned NULL when `*current` == `*last`.")
	assert(sllist->current == NULL, "selectNext set `*current` to NULL when `*current` == `*last`.")
	
	sllist->current = NULL;
	assert(sllist_selectNext(sllist) == NULL, "selectNext returned NULL when `*current` is NULL.")
	
	// Testing selectNextData
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectNextData(sllist) != NULL, "selectNextData returned a non-NULL value.")
	assert(sllist->current->data == (void *) 4, "Single linked list `*current` now points at `4`.")
	
	sllist_selectByIndex(sllist, 2);
	assert(sllist_selectNextData(sllist) == (void *) 4, "selectNextData returned `4`.")
	
	sllist_selectLast(sllist);
	assert(sllist_selectNextData(sllist) == NULL, "selectNextData returned NULL when `*current` == `*last`.")
	assert(sllist->current == NULL, "selectNextData set `*current` to NULL when `*current` == `*last`.")
	
	sllist->current = NULL;
	assert(sllist_selectNextData(sllist) == NULL, "selectNextData returned NULL when `*current` is NULL.")
	
	
	// -------------
	//  End of test
	// -------------
	
	// Freeing the memory
	sllist_free(sllist, NULL, NULL);
}
