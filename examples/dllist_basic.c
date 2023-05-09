#include <stdio.h>

#include "../src/text.h"
#include "../src/lists/double/dllist.h"

int main() {
	// Creating a list that will free the data with `free`.
	DoubleLinkedList *myList = dllist_create(&free);
	
	// Adding some data.
	// We're also making a copy of these strings so that they can be freed later on.
	// If we use "static" strings will get some errors when they are passed to the `&free` function.
	dllist_append(myList, copyString("Hello world !"));
	dllist_append(myList, copyString("Lorem ipsum donor si amet."));
	dllist_append(myList, copyString("Test 123"));
	dllist_append(myList, copyString("I'm at the end :)"));
	
	// Accessing the `DoubleLinkedListNode`, not the data.
	printf("Indirect data access:\n");
	printf("> First: %s\n", (char *) dllist_selectFirst(myList)->data);
	printf("> Nbr2: %s\n", (char *) dllist_selectByIndex(myList, 2)->data);
	printf("> Nbr3: %s\n", (char *) dllist_selectByIndex(myList, 3)->data);
	printf("> Last: %s\n", (char *) dllist_selectLast(myList)->data);
	printf("\n");
	
	// Accessing the data directly.
	// We can only access the first one to initiate foreach loops.
	printf("Direct data access:\n");
	printf("> First: %s\n", (char *) dllist_selectFirstData(myList));
	printf("\n");
	
	// Iterating over the list with indirect access
	printf("Iteration with indirect data access:\n");
	DoubleLinkedListNode *loopNode = dllist_selectFirst(myList);
	while(loopNode != NULL) {
		printf("> %s\n", (char *) loopNode->data);
		
		// Preparing the next node
		// This step can be done manually or with `dllist_selectNext`.
		// The only difference is that `dllist_selectNext` will update the list's `current` member to the next node.
		loopNode = loopNode->next;
		//loopNode = dllist_selectNext(myList);
	}
	printf("\n");
	
	// Iterating over the list with direct access
	printf("Iteration with direct data access:\n");
	void *loopData = dllist_selectFirstData(myList);
	while(loopData != NULL) {
		printf("> %s\n", (char *) loopData);
		
		// Preparing the iteration's data
		loopData = dllist_selectNextData(myList);
	}
	printf("\n");
	
	// Freeing the list and the strings from memory.
	// This function will call the `&free` function we gave `dllist_create` earlier with each string we added.
	// /!\ You just have to make sure you don't use static strings
	printf("Freeing the list...\n");
	dllist_free(myList);
}
