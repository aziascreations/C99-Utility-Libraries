/** @file */

#include "commons.h"

#include <stdlib.h>

/** @defgroup group_llist Linked lists commons
 *
 *  Every linked list is composed of these 3 distinct parts.
 *
 *  <b>\ref double_linked_list "DoubleLinkedList"</b><br>
 *  Main structure that contains pointers to the first, last and current
 *    \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *  All functions in this module use or return a pointer to this type of structure.
 *
 *  <b>\ref double_linked_list_node "DoubleLinkedListNode"</b><br>
 *  Repeatable structure that is pointed to internally by the \ref double_linked_list "DoubleLinkedList" in order
 *    to represent a list entry.<br>
 *  This structure only contains pointer to the data it holds and the next and previous
 *    \ref double_linked_list_node "DoubleLinkedListNode".
 *
 *  <b>The data pointer</b><br>
 *  Also referred to as the *node's data*, this is a pointer to the data you want the list to hold.<br>
 *  When freeing a list, this is the pointer passed to the freeing function.
 *
 *  \see double_linked_list
 *  \see double_linked_list_node
 *
 *  @{
 */

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

/** @} */ // end of group_llist
