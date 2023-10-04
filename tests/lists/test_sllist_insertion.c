#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/single/sllist.h"

// TODO: Split this tests into multiple and more refined ones, just to be 101% safe.
int main(void) {
	// Preparing the lists and adding an empty node in each.
	SingleLinkedList *sllist = sllist_create();
	
	
	// Preliminary tests.
	assert(sllist->size == 0, "New single linked list has 0 node.")
	assert(sllist->first == NULL, "New single linked list `first` is NULL.")
	assert(sllist->current == NULL, "New single linked list `current` is NULL.")
	assert(sllist->last == NULL, "New single linked list `last` is NULL.")
	
	
	// Populating the list in valid ways.
	sllist_append(sllist, (void *) 1, NULL);  // Sets first and last
	
	
	// Testing with 1 element since it's a special case.
	assert(sllist->size == 1, "Single linked list has 1 node.")
	assert(sllist->first != NULL, "Single linked list `first` isn't NULL.")
	assert(sllist->current == NULL, "Single linked list `current` is still NULL.")
	assert(sllist->last != NULL, "Single linked list `last` isn't NULL.")
	assert(sllist->first->data == (void *) 1, "The `first` node points to `1`.")
	assert(sllist->last->data == (void *) 1, "The `last` node points to `1`.")
	assert(sllist->first->next == NULL, "The node's `*next` points to NULL.")
	
	
	// Continuing to populate the list in valid ways.
	sllist_append(sllist, (void *) 3, NULL);  // New data to end
	sllist_selectFirst(sllist);
	sllist_append(sllist, (void *) 4, NULL);  // New data to end, if *current is *first
	
	
	// Quick test since we won't be able to test that later.
	assert(sllist->last->data == (void *) 4, "The `last` node points to `4`.")
	
	
	// Continuing to populate the list in valid ways, still...
	sllist_insertAfterCurrent(sllist, (void *) 2, NULL);  // Inserting in the middle.
	sllist_selectLast(sllist);
	sllist_insertAfterCurrent(sllist, (void *) 5, NULL);  // Inserting at the end, *current same.
	
	
	// Testing the entire list now
	assert(sllist->size == 5, "Single linked list has 5 node.")
	
	assert(sllist->first->data == (void *) 1, "The `first` node points to `1`.")
	assert(sllist->first->next->data == (void *) 2, "The `2nd` node points to `2`.")
	assert(sllist->first->next->next->data == (void *) 3, "The `3rd` node points to `3`.")
	assert(sllist->first->next->next->next->data == (void *) 4, "The `4th` node points to `4`.")
	assert(sllist->first->next->next->next->next->data == (void *) 5, "The `5th` node points to `5`.")
	assert(sllist->last->data == (void *) 5, "The `last` node points to `5`.")
	
	assert(sllist->current->data == (void *) 4, "The list's `*current` member points to 4th node.")
	
	assert(sllist->last->next == NULL, "The `last` node's `*next` member points to `NULL`.")
	
	
	// Testing prepending actions.
	sllist_prepend(sllist, (void *) -1, NULL);
	assert(sllist->size == 6, "Single linked list has 6 node.")
	assert(sllist->first->data == (void *) -1, "The `first` node points to `-1`.")
	assert(sllist->first->next->data == (void *) 1, "The `first` node's `*next` points to `1`.")
	
	
	// Testing prepending actions on empty list.
	SingleLinkedList *sllist_alt = sllist_create();
	
	sllist_prepend(sllist_alt, (void *) 10, NULL);
	
	assert(sllist_alt->size == 1, "Single linked list with prepend has 1 node.")
	assert(sllist_alt->first->data == (void *) 10, "The `first` node points to `10`.")
	assert(sllist_alt->last->data == (void *) 10, "The `2nd` node points to `10`.")
	
	assert(sllist_alt->first->next == NULL, "The `first` node's `*next` points to NULL.")
	
	
	// Freeing the memory
	sllist_free(sllist_alt, NULL, NULL);
	sllist_free(sllist, NULL, NULL);
}
