/** @file */

#pragma once

#include <stdint.h>

/**
 *  Repeatable structure that is pointed to internally by the \ref double_linked_list "DoubleLinkedList" in order
 *    to represent a list entry.<br>
 *  This structure only contains pointer to the data it holds and the next and previous
 *    \ref double_linked_list_node "DoubleLinkedListNode".
 */
typedef struct double_linked_list_node {
	/**
	 * Data to be held as the list entry's data.
	 */
	void *data;
	
	/**
	 * Pointer to a potentially `NULL` previous \ref double_linked_list_node "DoubleLinkedListNode".
	 */
	struct double_linked_list_node *next;
	
	/**
	 * Pointer to a potentially `NULL` next \ref double_linked_list_node "DoubleLinkedListNode".
	 */
	struct double_linked_list_node *previous;
} DoubleLinkedListNode;

/**
 *  Main structure that contains pointers to the first, last and current
 *    \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *  All functions in this module use or return a pointer to this type of structure.
 *
 *  \see dllist_create
 *  \see dllist_free
 */
typedef struct double_linked_list {
	/**
	 * Amount of nodes currently present in the list.<br>
	 * Prevents heavy calculation when the list's size need to be fetched.
	 */
	size_t size;
	
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's first
	 *  node.
	 */
	struct double_linked_list_node *first;
	
	/**
	 * Temporary pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's
	 *  currently selected node.<br>
	 * This pointer was implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 */
	struct double_linked_list_node *current;
	
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's last
	 *  node.<br>
	 * Used to make some operations faster.
	 */
	struct double_linked_list_node *last;
	
	/**
	 * Function used to free the data pointer present in the \ref double_linked_list_node "DoubleLinkedListNode"
	 *  structure.
	 * @param data The freed \ref double_linked_list_node "DoubleLinkedListNode"'s
	 *  \ref double_linked_list_node::data "data" field.
	 */
	void (*free)(void *data);
} DoubleLinkedList;
