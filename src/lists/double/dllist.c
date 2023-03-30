#include "dllist.h"

DoubleLinkedList* dllist_create(void (*free)(void* data)) {
	DoubleLinkedList* newList = malloc(sizeof(DoubleLinkedList));
	
	// Only setting up the fields if memory was allocated.
	if(newList != NULL) {
		newList->size = 0;
		newList->first = NULL;
		newList->current = NULL;
		newList->last = NULL;
		newList->free = free;
	}
	
	return newList;
}

void dllist_free(DoubleLinkedList* list) {
	if(list == NULL) {
		return;
	}
	
	DoubleLinkedListNode * currentNode = list->first;
	while(currentNode != NULL) {
		if(list->free != NULL) {
			list->free(currentNode->data);
		}
		DoubleLinkedListNode* nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	
	free(list);
}

DoubleLinkedListNode* dllist_selectFirst(DoubleLinkedList* list) {
	if(list != NULL) {
		list->current = list->first;
		return list->first;
	}
	return NULL;
}

DoubleLinkedListNode* dllist_selectNext(DoubleLinkedList* list) {
	if(list != NULL) {
		if(list->current != NULL) {
			list->current = list->current->next;
			return list->current;
		}
	}
	return NULL;
}

DoubleLinkedListNode* dllist_selectPrevious(DoubleLinkedList* list) {
	if(list != NULL) {
		if(list->current != NULL) {
			list->current = list->current->previous;
			return list->current;
		}
	}
	return NULL;
}

DoubleLinkedListNode* dllist_selectLast(DoubleLinkedList* list) {
	if(list != NULL) {
		list->current = list->last;
		return list->last;
	}
	return NULL;
}

void* dllist_selectFirstData(DoubleLinkedList* list) {
	if(dllist_selectFirst(list) != NULL) {
		return list->current->data;
	}
	return NULL;
}

void* dllist_selectNextData(DoubleLinkedList* list) {
	if(dllist_selectNext(list) != NULL) {
		return list->current->data;
	}
	return NULL;
}


DoubleLinkedListNode* dllist_getByIndex(DoubleLinkedList* list, size_t index) {
	if(list != NULL) {
		DoubleLinkedListNode* currentNode = list->first;
		size_t currentIndex = 0;
		
		while(currentNode != NULL && currentIndex != index) {
			currentNode = currentNode->next;
			currentIndex++;
		}
		
		return currentNode;
	}
	
	return NULL;
}

DoubleLinkedListNode* dllist_selectByIndex(DoubleLinkedList* list, size_t index) {
	if(list != NULL) {
		list->current = dllist_getByIndex(list, index);
		return list->current;
	}
	
	return NULL;
}

bool dllist_append(DoubleLinkedList* list, void* data) {
	if(list != NULL) {
		DoubleLinkedListNode* newNode = malloc(sizeof(DoubleLinkedListNode));
		
		if(newNode != NULL) {
			newNode->next = NULL;
			newNode->data = data;
			
			if(list->last == NULL) {
				// This is the first node in the list.
				newNode->previous = NULL;
				list->last = newNode;
				list->first = newNode;
			} else {
				// We just append.
				newNode->previous = list->last;
				list->last->next = newNode;
				list->last = newNode;
			}
			
			list->size++;
			return true;
		}
	}
	
	return false;
}
