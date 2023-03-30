#pragma once

#include <stdint.h>

typedef struct double_linked_list_node {
	void *data;
	struct double_linked_list_node *next;
	struct double_linked_list_node *previous;
} DoubleLinkedListNode;

typedef struct double_linked_list {
	/**
	 * Amount of nodes currently present in the list.
	 */
	size_t size;
	
	/**
	 * First node in the list.
	 */
	struct double_linked_list_node *first;
	
	/**
	 * Temporary pointer to the currently selected node.
	 * This behaviour is implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 */
	struct double_linked_list_node *current;
	
	/**
	 * Last node in the list.
	 * Used for quick access during appending operations
	 */
	struct double_linked_list_node *last;
	
	// Function used to free the data pointer present in the "SingleLinkedListNode" structure.
	void (*free)(void *data);
} DoubleLinkedList;

/**
 * Private interface structure that defines the functions provided by this module.
 */
typedef struct {
	DoubleLinkedList *(*create)(void (*free)(void *data));  // See: dllist_create
	void (*free)(DoubleLinkedList *list);
	
	DoubleLinkedListNode *(*selectFirst)(DoubleLinkedList *list);
	
	DoubleLinkedListNode *(*selectNext)(DoubleLinkedList *list);
	
	DoubleLinkedListNode *(*selectPrevious)(DoubleLinkedList *list);
	
	DoubleLinkedListNode *(*selectLast)(DoubleLinkedList *list);
	
	DoubleLinkedListNode *(*getByIndex)(DoubleLinkedList *list, size_t index);
	
	DoubleLinkedListNode *(*selectByIndex)(DoubleLinkedList *list, size_t index);
	
	bool (*append)(DoubleLinkedList *list, void *data);
} DoubleLinkedListModuleInterface;
