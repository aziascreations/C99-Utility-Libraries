/** @file */

#pragma once

#include <stdint.h>

typedef struct single_linked_list_node SingleLinkedListNode;

typedef struct single_linked_list SingleLinkedList;

/**
 *  Repeatable structure that is pointed to internally by the \ref single_linked_list "SingleLinkedList" in order
 *    to represent a list entry.<br>
 *  This structure only contains pointer to the data it holds and the next
 *   \ref single_linked_list_node "SingleLinkedListNode".
 */
struct single_linked_list_node {
	/**
	 * Data to be held as the list entry's data.
	 */
	void *data;
	
	/**
	 * Pointer to a potentially `NULL` next \ref single_linked_list_node "SingleLinkedListNode".
	 */
	SingleLinkedListNode *next;
};

/**
 *  Main structure that contains pointers to the first, last and current
 *    \ref single_linked_list_node "SingleLinkedListNode".<br>
 *  All functions in this module use or return a pointer to this type of structure.
 *
 *  \see sllist_create
 *  \see sllist_free
 */
struct single_linked_list {
	/**
	 * Amount of nodes currently present in the list.<br>
	 * Prevents heavy calculation when the list's size need to be fetched.
	 */
	size_t size;
	
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's first
	 *  node.
	 */
	SingleLinkedListNode *first;
	
	/**
	 * Temporary pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's
	 *  currently selected node.<br>
	 * This pointer was implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 */
	SingleLinkedListNode *current;
	
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's last
	 *  node.<br>
	 * Used to make some operations faster.
	 */
	SingleLinkedListNode *last;
	
	/**
	 * Function used to free the data pointer present in the \ref double_linked_list_node "DoubleLinkedListNode"
	 *  structure.
	 * @param data The freed \ref double_linked_list_node "DoubleLinkedListNode"'s
	 *  \ref double_linked_list_node::data "data" field.
	 */
	void (*cb_freeData)(void *data);
	
	/**
	 * Function used to allocate the memory for a \ref single_linked_list_node "SingleLinkedListNode" when inserting
	 *  data into the list.
	 * This function can be replaced by one that allocates a bigger structure that only gets handled in another part
	 *  of the program to which the "sllist_" functions are entirely obvious.
	 * @return The pointer to the allocated \ref single_linked_list_node "SingleLinkedListNode" structure.
	 */
	SingleLinkedListNode *(*cb_mallocNode)();
	
	void (*cb_freeNode)(void *data);
};
