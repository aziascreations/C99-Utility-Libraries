#include <stdio.h>

#include "../src/text.h"
#include "../src/lists/double/dllist.h"

int main() {
	// Creating a list.
	DoubleLinkedList *myList = dllist_create();
	
	// Adding some data.
	// We're also making a copy of these strings so that they can be freed later on.
	// If we use "static" strings will get some errors when they are passed to the `&free` function.
	// This can be ignored to some extent by using a custom data freeing callback as show in other examples.
	dllist_append(myList, copyString("Hello world !"), NULL);
	dllist_append(myList, copyString("Lorem ipsum donor si amet."), NULL);
	dllist_append(myList, copyString("Test 123"), NULL);
	dllist_append(myList, copyString("I'm at the end :)"), NULL);
	
	// Accessing the `DoubleLinkedListNode`, not the data.
	// This should only be done when manually browsing the list or when using custom nodes.
	printf("Explicit selection & data access through the list's node:\n");
	printf("> First: %s\n", (char *) (dllist_selectFirst(myList)->data));
	printf("> Nbr2: %s\n", (char *) (dllist_selectByIndex(myList, 2)->data));
	printf("> Nbr3: %s\n", (char *) dllist_selectByIndex(myList, 3)->data);
	printf("> Last: %s\n", (char *) dllist_selectLast(myList)->data);
	printf("\n");
	
	// Accessing the data directly.
	// The `dllist_selectFirstData` function will reset the list's internal `*current` pointer to the first element.
	printf("Explicit selection & direct data access:\n");
	printf("> First: %s\n", (char *) dllist_selectFirstData(myList));
	printf("\n");
	
	// Iterating over the list with indirect access
	// We MUST select the first element in order to reset the list's internal `*current` pointer which
	//  allows us to iterate over it later on.
	printf("Iteration with indirect data access:\n");
	DoubleLinkedListNode *loopNode = dllist_selectFirst(myList);
	while(loopNode != NULL) {
		printf("> %s\n", (char *) loopNode->data);
		
		// Preparing the next node.
		// This step can be done manually or with `dllist_selectNext`.
		// The only difference is that `dllist_selectNext` will update the list's `*current` member to the next node.
		loopNode = loopNode->next;
		//loopNode = dllist_selectNext(myList);
	}
	printf("\n");
	
	// Iterating over the list with direct access
	// We MUST select the first element in order to reset the list's internal `*current` pointer which
	//  allows us to iterate over it later on.
	printf("Iteration with direct data access:\n");
	void *loopData = dllist_selectFirstData(myList);
	while(loopData != NULL) {
		printf("> %s\n", (char *) loopData);
		
		// Preparing the iteration's data
		loopData = dllist_selectNextData(myList);
		// TODO: Implement a `dllist_selectNextData`.
	}
	printf("\n");
	
	// Freeing the list and the strings from memory.
	// This function will call the given `void (*cb_freeData)(void *data)` callback with each string we added.
	// If this parameter is left as NULL, the inserted data won't be freed.
	// The second callback can be left as NULL since we use the standard list nodes,
	//  the standard `free` function will automatically be called for each node in this case.
	printf("Freeing the list...\n");
	dllist_free(myList, &free, NULL);
}
