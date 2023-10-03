/** @file */

#include "commons.h"

#include <stdlib.h>

LinkedList *llist_create() {
	LinkedList *newList = malloc(sizeof(LinkedList));
	
	// Only setting up the fields if memory was allocated.
	if(newList != NULL) {
		newList->size = 0;
		newList->first = NULL;
		newList->current = NULL;
		newList->last = NULL;
	}
	
	return newList;
}

void llist_free(LinkedList * list, void (*cb_freeData)(void *data), void (*cb_freeNode)(void *data)) {
	if(list == NULL) {
		return;
	}
	
	// We use the SingleLinkedListNode since it is the smallest common implementation of a linked list node available.
	SingleLinkedListNode *currentNode = list->first;
	while(currentNode != NULL) {
		if(cb_freeData != NULL) {
			cb_freeData(currentNode->data);
		}
		
		SingleLinkedListNode *nextNode = currentNode->next;
		
		if(cb_freeNode == NULL) {
			cb_freeNode = &free;
		}
		cb_freeNode(currentNode);
		currentNode = nextNode;
	}
	
	free(list);
}

LinkedListNode *llist_selectFirst(LinkedList *list) {
	if(list != NULL) {
		list->current = list->first;
		return list->first;
	}
	return NULL;
}

LinkedListNode *llist_selectNext(LinkedList *list) {
	if(list != NULL) {
		if(list->current != NULL) {
			list->current = list->current->next;
			return list->current;
		}
	}
	return NULL;
}


LinkedListNode *llist_selectLast(LinkedList *list) {
	if(list != NULL) {
		list->current = list->last;
		return list->last;
	}
	return NULL;
}

void *llist_selectFirstData(LinkedList *list) {
	if(llist_selectFirst(list) != NULL) {
		return list->current->data;
	}
	return NULL;
}

void *llist_selectNextData(LinkedList *list) {
	if(llist_selectNext(list) != NULL) {
		return list->current->data;
	}
	return NULL;
}

void *llist_selectLastData(LinkedList *list) {
	if(llist_selectLast(list) != NULL) {
		return list->current->data;
	}
	return NULL;
}

LinkedListNode *llist_getByIndex(LinkedList *list, size_t index) {
	if(list != NULL) {
		LinkedListNode *currentNode = list->first;
		size_t currentIndex = 0;
		
		while(currentNode != NULL && currentIndex != index) {
			currentNode = currentNode->next;
			currentIndex++;
		}
		
		return currentNode;
	}
	
	return NULL;
}

LinkedListNode *llist_selectByIndex(LinkedList *list, size_t index) {
	if(list != NULL) {
		list->current = llist_getByIndex(list, index);
		return list->current;
	}
	
	return NULL;
}
