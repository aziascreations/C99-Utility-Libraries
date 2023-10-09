/** @file */

#pragma once

/** @addtogroup group_llist
 *  @{
 */

// There are duplicated structures in order to allow the IDE to raise errors when passing
//   `SingleLinkedList` instead of `DoubleLinkedList` or inversely.
// This shouldn't affect the compiled code as far as I know.
typedef struct single_linked_list SingleLinkedList;
typedef struct double_linked_list DoubleLinkedList;
typedef SingleLinkedList LinkedList;

typedef struct single_linked_list_node SingleLinkedListNode;
typedef struct double_linked_list_node DoubleLinkedListNode;

// The `SingleLinkedListNode` is used internally as the common `LinkedListNode` base.
typedef SingleLinkedListNode LinkedListNode;

/**
 *  Repeatable structure that is pointed to internally by the \ref single_linked_list "LinkedList" in order
 *    to represent a list entry.
 *
 *  This structure only contains pointer to the data it holds and the next
 *    \ref single_linked_list_node "LinkedListNode".
 *
 *  If a functions that specifically requires \ref double_linked_list_node "DoubleLinkedListNode" is called,
 *    it should internally typecast the node's pointer.
 *  This is because that structure is a plain extension of this one.
 *
 *  \see \ref double_linked_list_node "DoubleLinkedListNode"
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
 *
 *  This structure only contains pointer to the data it holds and the next and previous
 *    \ref double_linked_list_node "DoubleLinkedListNode".
 *
 *  Unless it is handled in a functions that specifically requires \ref double_linked_list_node "DoubleLinkedListNode",
 *    this structure is typecast-ed as a \ref single_linked_list_node "LinkedListNode".<br>
 *  This is because this structure is a plain extension of the \ref single_linked_list_node "LinkedListNode" one.
 *
 *  \see \ref single_linked_list_node "LinkedListNode"
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
 *  Main list structure that contains pointers to the first, last and current
 *    \ref single_linked_list_node "SingleLinkedListNode".<br>
 *  All functions in the `sllist` module use or return a pointer to this type of structure.
 *
 *  This structure is a 1-to-1 copy of the \ref double_linked_list "DoubleLinkedList" one.<br>
 *  There are duplicated in order to allow the IDE to raise errors when passing
 *    \ref single_linked_list "SingleLinkedList" instead of \ref double_linked_list "DoubleLinkedList" or inversely.
 *
 *  Any operations that involves memory allocation/freeing, insertions and data retrieval will use this structure
 *    via the \ref single_linked_list "LinkedList" type definition and a typecast **UNLESS** the function is
 *    specifically meant for double linked lists.
 *
 *  \see \ref double_linked_list "DoubleLinkedList"
 */
struct single_linked_list {
	/**
	 * Amount of nodes currently present in the list.<br>
	 * Prevents heavy calculation when the list's size need to be fetched.
	 */
	size_t size;
	
	/**
	 * Pointer to a potentially `NULL` \ref single_linked_list_node "SingleLinkedListNode" that is the list's first
	 *  node.
	 */
	SingleLinkedListNode *first;
	
	/**
	 * Pointer to a potentially `NULL` \ref single_linked_list_node "SingleLinkedListNode" that is the list's last
	 *  node.<br>
	 * Used to make some operations faster.
	 */
	SingleLinkedListNode *last;
	
	/**
	 * Temporary pointer to a potentially `NULL` \ref single_linked_list_node "SingleLinkedListNode" that is the list's
	 *  currently selected node.<br>
	 * This pointer was implemented in order to mimic PureBasic's lists and to make some generic ordering tasks less
	 *  tedious.
	 * This structure member is also the last since it is planned to be toggleable in the future to help save memory
	 *  in some edge-cases.
	 */
	SingleLinkedListNode *current;
};

/**
 *  Main list structure that contains pointers to the first, last and current
 *    \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *  All functions in the `dllist` module use or return a pointer to this type of structure.
 *
 *  This structure is a 1-to-1 copy of the \ref single_linked_list "SingleLinkedList" one.<br>
 *  There are duplicated in order to allow the IDE to raise errors when passing
 *    \ref single_linked_list "SingleLinkedList" instead of \ref double_linked_list "DoubleLinkedList" or inversely.
 *
 *  Any operations that involves memory allocation/freeing, insertions and data retrieval will use the
 *    \ref single_linked_list "SingleLinkedList" structure via the \ref single_linked_list "LinkedList" type
 *    definition and a typecast **UNLESS** the function is specifically meant for double linked lists.
 *
 *  \see \ref single_linked_list "SingleLinkedList"
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
	 * This structure member is also the last since it is planned to be toggleable in the future to help save memory
	 *  in some edge-cases.
	 */
	DoubleLinkedListNode *current;
};

/** @} */ // end of group_llist
