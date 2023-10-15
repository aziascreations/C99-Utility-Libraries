/** @file */

#pragma once

#include "../platform.h"

#include "structs.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_DLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_LLIST NP_DLL_EXPORT
#else
	#define DLL_EXP_LLIST
#endif

/** @defgroup group_llist Linked lists commons
 *
 *  This module contains all the functions that can be used to interact with generic
 *    \ref single_linked_list "LinkedList".
 *
 *  The equivalent functions in the \ref group_sllist "Single linked lists" and \ref group_dllist "Double linked lists"
 *    modules use macros that expand to functions defined in this module.<br>
 *  If a functions requires different code based on the list's type, they will be declared in their respective module
 *    and **MAY** use some of the common functions provided here.
 *
 *  Internally, every linked list is composed of these 2 distinct parts.
 *
 *  <b>\ref LinkedList "LinkedList"</b><br>
 *  Main structure that contains pointers to the first, last and current \ref linked_list_node "LinkedListNode".<br>
 *  The \ref single_linked_list "SingleLinkedList" and \ref double_linked_list "DoubleLinkedList" structures are
 *    both 1-to-1 copies of this structure and are only present to help IDEs with typecasting warning and errors.
 *
 *  <b>\ref single_linked_list_node "LinkedListNode"</b><br>
 *  Structure that is pointed to internally by the \ref LinkedList "LinkedList" in order to represent
 *    a list's entry.<br>
 *  Pointers to this structure can either point to the \ref single_linked_list_node "SingleLinkedListNode" or
 *    \ref double_linked_list_node "DoubleLinkedListNode" structures depending on the list's type.<br>
 *
 *  In some cases, pointers to this structure can point to a custom structure that extends these 2 standard ones.<br>
 *  These extended structures should only be used in specific cases such as *Chained HashMap's Buckets* which need
 *    to retain a copy of the original hash while preferably not having to follow multiple pointers.<br>
 *  Please check \ref sllist_append and \ref dllist_append for more information.
 *
 *  \see \ref group_sllist "Single linked lists module"
 *  \see \ref group_dllist "Double linked lists module"
 *
 *  @{
 */

/**
 * Creates an empty \ref single_linked_list "LinkedList".
 * @return A pointer to a newly allocated \ref single_linked_list "LinkedList" structure.
 */
DLL_EXP_LLIST LinkedList *llist_create();

/**
 * Frees the given \ref single_linked_list "LinkedList" and all of its nodes' data using the given callback
 *  for both the data and nodes.
 * @param list The \ref single_linked_list "LinkedList" to be freed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_LLIST void llist_free(
		LinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref single_linked_list "LinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "LinkedListNode",
 *  or `NULL` if the list has no elements.
 */
DLL_EXP_LLIST LinkedListNode *llist_selectFirst(LinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref single_linked_list "LinkedList" whose next element will be selected.
 * @return A pointer to the next \ref single_linked_list_node "LinkedListNode",
 *  or `NULL` if the list has no next element or any is currently selected.
 */
DLL_EXP_LLIST LinkedListNode *llist_selectNext(LinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref single_linked_list "LinkedList" whose last element will be selected.
 * @return A pointer to the last \ref single_linked_list_node "LinkedListNode",
 *  or `NULL` if the list has no elements.
 */
DLL_EXP_LLIST LinkedListNode *llist_selectLast(LinkedList *list);

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref single_linked_list "LinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "LinkedListNode"'s data,
 *  or `NULL` if the list has no elements.
 */
DLL_EXP_LLIST void *llist_selectFirstData(LinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref single_linked_list "LinkedList" whose next element will be selected.
 * @return A pointer to the next \ref single_linked_list_node "LinkedListNode"'s data,
 *  or `NULL` if the list has no next element or any is currently selected.
 */
DLL_EXP_LLIST void *llist_selectNextData(LinkedList *list);

/**
 * Selects the last node in the list as the current one and returns its data pointer.
 * @param list The \ref single_linked_list "LinkedList" whose last element will be selected.
 * @return A pointer to the last \ref single_linked_list_node "LinkedListNode"'s data,
 *  or `NULL` if the list has no elements.
 */
DLL_EXP_LLIST void *llist_selectLastData(LinkedList *list);

/**
 * Returns a \ref single_linked_list_node "LinkedListNode" based on the currently selected node's `*next` pointer.
 * @param list The relevant \ref single_linked_list "LinkedList".
 * @return A pointer to the next \ref single_linked_list_node "LinkedListNode" in line,
 *  or `NULL` if the list has no elements or no element is currently selected.
 */
DLL_EXP_LLIST LinkedListNode *llist_getNext(LinkedList *list);

/**
 * Returns the data pointer for the next \ref single_linked_list_node "LinkedListNode" in the list based on the
 *  currently selected node's `*next` pointer.
 * @param list The relevant \ref single_linked_list "LinkedList".
 * @return A pointer to the next \ref single_linked_list_node "LinkedListNode"'s data in line,
 *  or `NULL` if the list has no elements or no element is currently selected.
 */
DLL_EXP_LLIST void *llist_getNextData(LinkedList *list);

/**
 * Returns a \ref single_linked_list_node "LinkedListNode" via its given index in the list.
 * @param list The \ref single_linked_list "LinkedList" whose element will be returned.
 * @param index The \ref single_linked_list_node "LinkedListNode"'s index.
 * @return The relevant \ref single_linked_list_node "LinkedListNode", or `NULL` if not found or out-of-bounds.
 */
DLL_EXP_LLIST LinkedListNode *llist_getByIndex(LinkedList *list, size_t index);

/**
 * Selects and returns a \ref single_linked_list_node "LinkedListNode" via its given index in the list.
 * @param list The \ref single_linked_list "LinkedList" whose element will be selected.
 * @param index The \ref single_linked_list_node "LinkedListNode"'s index.
 * @return The relevant \ref single_linked_list_node "LinkedListNode", or `NULL` if not found  or out-of-bounds.
 */
DLL_EXP_LLIST LinkedListNode *llist_selectByIndex(LinkedList *list, size_t index);

/** @} */ // end of group_llist
