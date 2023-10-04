/** @file */

#include "sllist.h"

#include <stdlib.h>

SingleLinkedListNode *sllist_createNode() {
	return calloc(1, sizeof(SingleLinkedListNode));
}

SingleLinkedListNode *sllist_getPrevious(SingleLinkedList *list) {
	if(list != NULL) {
		if(list->current != NULL && list->current != list->first) {
			SingleLinkedListNode *currentNode = list->first;
			
			while(currentNode != NULL) {
				if(currentNode->next == list->current) {
					return currentNode;
				}
				
				currentNode = currentNode->next;
			}
		}
	}
	
	return NULL;
}

void *sllist_getPreviousData(SingleLinkedList *list) {
	SingleLinkedListNode *previousNode = sllist_getPrevious(list);
	
	if(previousNode != NULL) {
		return previousNode->data;
	}
	
	return NULL;
}

SingleLinkedListNode *sllist_selectPrevious(SingleLinkedList *list) {
	SingleLinkedListNode *previousNode = sllist_getPrevious(list);
	
	if(list != NULL) {
		list->current = previousNode;
	}
	
	return previousNode;
}

void *sllist_selectPreviousData(SingleLinkedList *list) {
	SingleLinkedListNode *previousNode = sllist_selectPrevious(list);
	
	if(previousNode != NULL) {
		return previousNode->data;
	}
	
	return NULL;
}

bool sllist_prepend(SingleLinkedList *list, void *data, SingleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(cb_allocNode == NULL) {
			cb_allocNode = &sllist_createNode;
		}
		
		SingleLinkedListNode *newNode = cb_allocNode();
		
		if(newNode != NULL) {
			newNode->data = data;
			
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

bool sllist_append(SingleLinkedList *list, void *data, SingleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(cb_allocNode == NULL) {
			cb_allocNode = &sllist_createNode;
		}
		
		SingleLinkedListNode *newNode = cb_allocNode();
		
		if(newNode != NULL) {
			newNode->next = NULL;
			newNode->data = data;
			
			if(list->last == NULL) {
				// This is the first node in the list.
				list->last = newNode;
				list->first = newNode;
			} else {
				// We just append to the end of the list.
				list->last->next = newNode;
				list->last = newNode;
			}
			
			list->size++;
			return true;
		}
	}
	
	return false;
}

bool sllist_insertAfterCurrent(SingleLinkedList *list, void *data, SingleLinkedListNode * (*cb_allocNode)()) {
	if(list != NULL) {
		if(list->current != NULL) {
			if(cb_allocNode == NULL) {
				cb_allocNode = &sllist_createNode;
			}
			
			SingleLinkedListNode *newNode = cb_allocNode();
			
			if(newNode != NULL) {
				newNode->data = data;
				
				newNode->next = list->current->next;
				list->current->next = newNode;
				
				if(newNode->next == NULL) {
					list->last = newNode;
				}
				
				list->size++;
				return true;
			}
		}
	}
	
	return false;
}

bool sllist_deleteFirst(SingleLinkedList *list, void (*cb_freeData)(void *data), void (*cb_freeNode)(void *data)) {
	if(list != NULL) {
		if(list->first != NULL) {
			SingleLinkedListNode *oldNode = list->first;
			
			list->first = oldNode->next;
			
			if(list->current == oldNode) {
				list->current = NULL;
			}
			
			if(list->last == oldNode) {
				list->last = NULL;
			}
			
			if(cb_freeData != NULL) {
				cb_freeData(oldNode->data);
			}
			
			if(cb_freeNode == NULL) {
				cb_freeNode = &free;
			}
			cb_freeNode(oldNode);
			
			list->size--;
			return true;
		}
	}
	
	return false;
}

bool sllist_deleteLast(SingleLinkedList *list, void (*cb_freeData)(void *data), void (*cb_freeNode)(void *data)) {
	if(list != NULL) {
		if(list->last != NULL) {
			SingleLinkedListNode *oldNode = list->last;
			
			SingleLinkedListNode *previousNode = list->first;
			while(previousNode != NULL) {
				if(previousNode->next == oldNode) {
					break;
				}
				previousNode = previousNode->next;
			}
			list->last = previousNode;
			
			if(list->last != NULL) {
				list->last->next = NULL;
			} else {
				list->first = NULL;
			}
			
			if(list->current == oldNode) {
				list->current = NULL;
			}
			
			if(cb_freeData != NULL) {
				cb_freeData(oldNode->data);
			}
			
			if(cb_freeNode == NULL) {
				cb_freeNode = &free;
			}
			cb_freeNode(oldNode);
			
			list->size--;
			return true;
		}
	}
	
	return false;
}



