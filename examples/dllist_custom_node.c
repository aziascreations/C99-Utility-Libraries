#include <stdio.h>
#include <stdlib.h>

#include "../src/text.h"
#include "../src/lists/double/dllist.h"

// If you want to implement a superset of the standard list node, you can use custom structures.
// In this case, the standard `free` function can be used to free this structure.
// However, if you have allocated memory that is only used in this structure and that isn't `*data`,
//  you WILL need to implement a custom freeing function that should be given to `dllist_free`.
struct my_list_node {
	// First, we need to re-implement the structure members from DoubleLinkedListNode / struct double_linked_list_node.
	// See: "src/lists/structs.h"
	void *data;
	DoubleLinkedListNode *next;
	DoubleLinkedListNode *previous;
	
	// Now we can add our custom fields.
	// This would mainly be used for hashmaps to store their hash in a more efficient way.
	int myNodeCustomValue;
};

// This function is used to allocate the memory for our custom list node ``,
//  and to also populate the custom members.
// A pointer to this function gets passed to `dllist_append`.
DoubleLinkedListNode *allocateMyNode() {
	struct my_list_node *myNode = calloc(1, sizeof(struct my_list_node));
	
	if(myNode != NULL) {
		// The random numbers will always be the same due to the limited randomness of `rand()`.
		myNode->myNodeCustomValue = rand() % 100;
	}
	
	return (DoubleLinkedListNode *) myNode;
}

int main() {
	// Creating a list.
	DoubleLinkedList *myList = dllist_create();
	
	// Adding some custom nodes with no standard data.
	// The only data we will care about in this case is the node's `myNodeCustomValue` member.
	dllist_append(myList, NULL, &allocateMyNode);
	dllist_append(myList, NULL, &allocateMyNode);
	dllist_append(myList, NULL, &allocateMyNode);
	dllist_append(myList, NULL, &allocateMyNode);
	dllist_append(myList, NULL, &allocateMyNode);
	
	// Iterating over the list node by node while typecasting to our custom node.
	printf("Iteration:\n");
	struct my_list_node *loopNode = (struct my_list_node *) dllist_selectFirst(myList);
	while(loopNode != NULL) {
		printf("> %d\n", loopNode->myNodeCustomValue);
		
		// Preparing the next node.
		loopNode = (struct my_list_node *) dllist_selectNext(myList);
	}
	printf("\n");
	
	// Freeing the list from memory.
	// We pass `NULL` for the data freeing part since we haven't allocated anything in this example.
	// The second callback can be left as NULL since our custom node can be freed with the standard `free` function
	//  that automatically gets used since we passed NULL in this case.
	printf("Freeing the list...\n");
	dllist_free(myList, NULL, NULL);
}
