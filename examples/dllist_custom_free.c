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
	// Creating a list that will free the data with `freeMyStruct`.
	DoubleLinkedList *myList = dllist_create(&freeMyStruct);
	
	// Adding some data.
	struct my_struct *myData;
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = copyString("Hello world !");
	dllist_append(myList, myData);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = copyString("Lorem ipsum donor si amet.");
	dllist_append(myList, myData);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = copyString("Test 123");
	dllist_append(myList, myData);
	
	myData = malloc(sizeof(struct my_struct));
	myData->nestedString = copyString("I'm at the end :)");
	dllist_append(myList, myData);
	
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
	// This function will call the `&freeMyStruct` function we gave `dllist_create` earlier with each string we added.
	printf("Freeing the list...\n");
	dllist_free(myList);
}
