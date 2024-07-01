#include <stdio.h>

#include "../src/text.h"
#include "../src/lists/double/dllist.h"

struct my_struct {
	char *nestedString;
};

// This function will be called for every element in the list.
// The `*data` parameter represents the value we gave in the `dllist_append` call.
void freeMyStruct(void *data) {
	printf("> Freeing `struct my_struct` and its data @%p\n", data);
	
	// Freeing the nested string.
	free(((struct my_struct *) data)->nestedString);
	
	// Freeing the structure itself.
	free(data);
}

int main() {
	// Creating a list.
	DoubleLinkedList *myList = dllist_create();
	
	// Adding some data.
	struct my_struct *myData;
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = text_copyA("Hello world !");
	dllist_append(myList, myData, NULL);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = text_copyA("Lorem ipsum donor si amet.");
	dllist_append(myList, myData, NULL);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = text_copyA("Test 123");
	dllist_append(myList, myData, NULL);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = text_copyA("I'm at the end :)");
	dllist_append(myList, myData, NULL);
	
	// Iterating over the list with direct access
	printf("Iteration with direct data access:\n");
	void *loopData = dllist_selectFirstData(myList);
	while(loopData != NULL) {
		printf("> %s\n", ((struct my_struct *) loopData)->nestedString);
		
		// Preparing the iteration's data
		loopData = dllist_selectNextData(myList);
	}
	printf("\n");
	
	// Freeing the list and the strings from memory.
	// This function will call the given custom `void (*cb_freeData)(void *data)` callback with each string we added.
	// The second callback can be left as NULL since we use the standard list nodes,
	//  the standard `free` function will automatically be called for each node in this case.
	printf("Freeing the list...\n");
	dllist_free(myList, &freeMyStruct, NULL);
}
