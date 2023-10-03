/** @file */

#include "dllist.h"

DoubleLinkedListNode *dllist_createNode() {
	return calloc(1, sizeof(DoubleLinkedListNode));
}

DoubleLinkedListNode *dllist_selectPrevious(DoubleLinkedList *list) {
	if(list != NULL) {
		if(list->current != NULL) {
			list->current = list->current->previous;
			return list->current;
		}
	}
	return NULL;
}

bool dllist_prepend(DoubleLinkedList *list, void *data, DoubleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(cb_allocNode == NULL) {
			cb_allocNode = &dllist_createNode;
		}
		
		DoubleLinkedListNode *newNode = cb_allocNode();
		
		if(newNode != NULL) {
			newNode->data = data;
			
			if(list->first != NULL) {
				list->first->previous = newNode;
			}
			
			newNode->previous = NULL;
			newNode->next = list->first;
			list->first = newNode;
			
			if(list->last == NULL) {
				// This is the first node in the list.
				list->last = newNode;
			}
			
			list->size++;
			return true;
		}
	}
	
	return false;
}

bool dllist_append(DoubleLinkedList *list, void *data, DoubleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(cb_allocNode == NULL) {
			cb_allocNode = &dllist_createNode;
		}
		
		DoubleLinkedListNode *newNode = cb_allocNode();
		
		if(newNode != NULL) {
			newNode->next = NULL;
			newNode->data = data;
			
			if(list->last == NULL) {
				// This is the first node in the list.
				newNode->previous = NULL;
				list->last = newNode;
				list->first = newNode;
			} else {
				// We just append to the end of the list.
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

bool dllist_insertAfterCurrent(DoubleLinkedList *list, void *data, DoubleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(list->current != NULL) {
			if(cb_allocNode == NULL) {
				cb_allocNode = &dllist_createNode;
			}
			
			DoubleLinkedListNode *newNode = cb_allocNode();
			
			if(newNode != NULL) {
				newNode->data = data;
				
				newNode->next = list->current->next;
				list->current->next = newNode;
				
				newNode->previous = list->current;
				
				if(newNode->next == NULL) {
					list->last = newNode;
				} else {
					newNode->next->previous = newNode;
				}
				
				list->size++;
				return true;
			}
		}
	}
	
	return false;
}
