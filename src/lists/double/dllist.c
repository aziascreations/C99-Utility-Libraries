/** @file */

#include "dllist.h"

/** @defgroup group_dllist Double linked lists
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

/** @} */ // end of group_dllist
