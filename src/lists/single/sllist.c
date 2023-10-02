/** @file */

#include "sllist.h"

#include <stdlib.h>

/** @defgroup group_sllist Single linked lists
 *
 *  TODO
 *
 *  @{
 */

SingleLinkedListNode *sllist_createNode() {
	return calloc(1, sizeof(SingleLinkedListNode));
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

/** @} */ // end of group_sllist
