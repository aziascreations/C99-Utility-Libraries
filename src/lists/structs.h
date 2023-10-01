#pragma once

typedef struct single_linked_list_node SingleLinkedListNode;
typedef struct double_linked_list_node DoubleLinkedListNode;

typedef struct single_linked_list SingleLinkedList;
typedef struct double_linked_list DoubleLinkedList;

// TODO: Explain that this is the common base used internally !
typedef SingleLinkedListNode LinkedListNode;
typedef SingleLinkedList LinkedList;

/**
 *  Repeatable structure that is pointed to internally by the \ref single_linked_list "SingleLinkedList" in order
 *    to represent a list entry.<br>
 *  This structure only contains pointer to the data it holds and the next
 *    \ref single_linked_list_node "SingleLinkedListNode".
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
	 * Pointer to a potentially `NULL` next \ref double_linked_list_node "DoubleLinkedListNode".
	 */
	DoubleLinkedListNode *next;
	
	/**
	 * Pointer to a potentially `NULL` previous \ref double_linked_list_node "DoubleLinkedListNode".
	 */
	DoubleLinkedListNode *previous;
} DoubleLinkedListNode;

/**
 *  Main structure that contains pointers to the first, last and current
 *    \ref single_linked_list_node "SingleLinkedListNode".<br>
 *  All functions in the `sllist` module use or return a pointer to this type of structure.
 *
 *  This structure is a duplicate of the \ref double_linked_list "DoubleLinkedList" and will be used
 *   internally via typecasting for any operations that involves memory allocation/freeing, insertions
 *   and data retrieval UNLESS the function is specifically meant for double linked lists.
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
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's last
	 *  node.<br>
	 * Used to make some operations faster.
	 */
	SingleLinkedListNode *last;
	
	/**
	 * Temporary pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's
	 *  currently selected node.<br>
	 * This pointer was implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 * This structure member is also the last since it is planned to be toggleable in the future to help save memory
	 *  in some edge-cases.
	 */
	SingleLinkedListNode *current;
};

/**
 *  TODO
 */
struct double_linked_list {
	/**
	 * Amount of nodes currently present in the list.<br>
	 * Prevents heavy calculation when the list's size need to be fetched.
	 */
	size_t size;
	
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's first
	 *  node.
	 */
	DoubleLinkedListNode *first;
	/**
	 * Pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's last
	 *  node.<br>
	 * Used to make some operations faster.
	 */
	DoubleLinkedListNode *last;
	
	/**
	 * Temporary pointer to a potentially `NULL` \ref double_linked_list_node "DoubleLinkedListNode" that is the list's
	 *  currently selected node.<br>
	 * This pointer was implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 */
	DoubleLinkedListNode *current;
};
