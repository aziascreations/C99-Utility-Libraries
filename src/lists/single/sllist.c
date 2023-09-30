#include "sllist.h"

#include <stdlib.h>

SingleLinkedList *sllist_create(void (*cb_freeData)(void *data)) {
	return sllist_createComplex(cb_freeData, NULL, NULL);
}

SingleLinkedList *sllist_createComplex(void (*cb_freeData)(void *data), SingleLinkedListNode *(*cb_mallocNode)(),
									   void (*cb_freeNode)(void *data)) {
	SingleLinkedList *newList = malloc(sizeof(SingleLinkedList));
	
	// Only setting up the fields if memory was allocated.
	if(newList != NULL) {
		newList->size = 0;
		newList->first = NULL;
		newList->current = NULL;
		newList->last = NULL;
		newList->cb_freeData = cb_freeData != NULL ? cb_freeData : &free;
		newList->cb_mallocNode = cb_mallocNode != NULL ? cb_mallocNode : &sllist_createNode;
		newList->cb_freeNode = cb_freeNode != NULL ? cb_freeNode : &free;
	}
	
	return newList;
}

SingleLinkedListNode *sllist_createNode() {
	return calloc(1, sizeof(SingleLinkedListNode));
}


