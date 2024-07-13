#include <stdio.h>

#include "../src/text.h"
#include "../src/lists/double/dllist.h"

int main() {
	// Creating a list.
	DoubleLinkedList *myList = dllist_create();
	
	// Adding some data.
	dllist_append(myList, text_copyA("Hello world !"), NULL);
	dllist_append(myList, text_copyA("Lorem ipsum donor si amet."), NULL);
	dllist_append(myList, text_copyA("Test 123"), NULL);
	dllist_append(myList, text_copyA("I'm at the end :)"), NULL);
	
	// Testing functions specific to double linked lists.
	printf("Using `dllist_selectPrevious`:\n");
	printf("> #3 by index:    %s\n", (char *) (dllist_selectByIndex(myList, 2)->data));
	printf("> #2 by previous: %s\n", (char *) (dllist_selectPrevious(myList)->data));  // Specific to dllist
	printf("> #3 by next:     %s\n", (char *) (dllist_selectNext(myList)->data));
	printf("\n");
	
	// Freeing the list and the strings from memory.
	printf("Freeing the list...\n");
	dllist_free(myList, &free, NULL);
}
