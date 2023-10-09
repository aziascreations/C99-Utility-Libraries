#include <stdio.h>

#include "../assert.h"

#include "../../src/lists/double/dllist.h"

// TODO: Split this tests into multiple and more refined ones, just to be 101% safe.
int main(void) {
	// Preparing the lists and adding an empty node in each.
	DoubleLinkedList *dllist = dllist_create();
	
	
	// Preliminary tests.
	assert(dllist->size == 0, "New single linked list has 0 node.")
	assert(dllist->first == NULL, "New single linked list `first` is NULL.")
	assert(dllist->current == NULL, "New single linked list `current` is NULL.")
	assert(dllist->last == NULL, "New single linked list `last` is NULL.")
	
	
	// Populating the list in valid ways.
	dllist_append(dllist, (void *) 1, NULL);  // Sets first and last
	
	
	// Testing with 1 element since it's a special case.
	assert(dllist->size == 1, "Single linked list has 1 node.")
	assert(dllist->first != NULL, "Single linked list `first` isn't NULL.")
	assert(dllist->current == NULL, "Single linked list `current` is still NULL.")
	assert(dllist->last != NULL, "Single linked list `last` isn't NULL.")
	assert(dllist->first->data == (void *) 1, "The `first` node points to `1`.")
	assert(dllist->last->data == (void *) 1, "The `last` node points to `1`.")
	assert(dllist->first->next == NULL, "The node's `*next` points to NULL.")
	assert(dllist->first->previous == NULL, "The node's `*previous` points to NULL.")
	
	
	// Continuing to populate the list in valid ways.
	dllist_append(dllist, (void *) 3, NULL);  // New data to end
	dllist_selectFirst(dllist);
	dllist_append(dllist, (void *) 4, NULL);  // New data to end, if *current is *first
	
	
	// Quick test since we won't be able to test that later.
	assert(dllist->last->data == (void *) 4, "The `last` node points to `4`.")
	
	
	// Continuing to populate the list in valid ways, still...
	dllist_insertAfterCurrent(dllist, (void *) 2, NULL);  // Inserting in the middle.
	dllist_selectLast(dllist);
	dllist_insertAfterCurrent(dllist, (void *) 5, NULL);  // Inserting at the end, *current same.
	
	
	// Testing the entire list now
	assert(dllist->size == 5, "Single linked list has 5 node.")
	
	assert(dllist->first->data == (void *) 1, "The `first` node points to `1`.")
	
	assert(dllist->first->next->data == (void *) 2, "The `2nd` node points to `2`.  (via `*next`)")
	assert(dllist->first->next->next->data == (void *) 3, "The `3rd` node points to `3`.  (via `*next`)")
	assert(dllist->first->next->next->next->data == (void *) 4, "The `4th` node points to `4`.  (via `*next`)")
	assert(dllist->first->next->next->next->next->data == (void *) 5, "The `5th` node points to `5`.  (via `*next`)")
	
	assert(dllist->last->previous->data == (void *) 4, "The `4th` node points to `4`.  (via `*previous`)")
	assert(dllist->last->previous->previous->data == (void *) 3, "The `3rd` node points to `3`.  (via `*previous`)")
	assert(dllist->last->previous->previous->previous->data == (void *) 2, "The `2nd` node points to `2`.  (via `*previous`)")
	assert(dllist->last->previous->previous->previous->previous->data == (void *) 1, "The `1st` node points to `1`.  (via `*previous`)")
	
	assert(dllist->last->data == (void *) 5, "The `last` node points to `5`.")
	
	assert(dllist->current->data == (void *) 4, "The list's `*current` member points to 4th node.")
	
	assert(dllist->first->previous == NULL, "The `first` node's `*previous` member points to `NULL`.")
	assert(dllist->last->next == NULL, "The `last` node's `*next` member points to `NULL`.")
	
	
	// Testing prepending actions.
	dllist_prepend(dllist, (void *) -1, NULL);
	assert(dllist->size == 6, "Single linked list has 6 node.")
	assert(dllist->first->data == (void *) -1, "The `first` node points to `-1`.")
	assert(dllist->first->next->data == (void *) 1, "The `first` node's `*next` points to `1`.")
	assert(dllist->first->next->previous == dllist->first, "The `first` node's `*next` points to `first` node.")
	
	
	// Testing prepending actions on empty list.
	DoubleLinkedList *dllist_alt = dllist_create();
	
	dllist_prepend(dllist_alt, (void *) 10, NULL);
	
	assert(dllist_alt->size == 1, "Single linked list with prepend has 1 node.")
	assert(dllist_alt->first->data == (void *) 10, "The `first` node points to `10`.")
	assert(dllist_alt->last->data == (void *) 10, "The `2nd` node points to `10`.")
	
	assert(dllist_alt->first->next == NULL, "The `first` node's `*next` points to NULL.")
	assert(dllist_alt->first->previous == NULL, "The `first` node's `*previous` points to NULL.")
	
	
	// Freeing the memory
	dllist_free(dllist_alt, NULL, NULL);
	dllist_free(dllist, NULL, NULL);
}
