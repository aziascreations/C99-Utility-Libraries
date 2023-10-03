/** @file */

#pragma once

#include <stdbool.h>

#include "../structs.h"
#include "../commons.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXP_SLLIST __declspec(dllexport)
#else
#define DLL_EXP_SLLIST
#endif

/** @defgroup group_sllist Single linked lists
 *
 *  TODO
 *
 *  \see \ref group_llist "Linked lists commons module"
 *  \see \ref group_dllist "Double linked lists module"
 *
 *  @{
 */

/**
 * Creates a single linked list.
 * @return A pointer to a newly allocated \ref single_linked_list "SingleLinkedList" structure.
 */
#define sllist_create() ((SingleLinkedList *) llist_create())

/**
 * Creates a single linked list node.
 * @return A pointer to a newly allocated \ref single_linked_list_node "SingleLinkedListNode" structure.
 */
DLL_EXP_SLLIST SingleLinkedListNode *sllist_createNode();

/**
 * Frees the given list and all of its nodes' data using the callback for both the data and nodes.
 * @param list The \ref single_linked_list "SingleLinkedList" to be freed.
 * @param cb_freeData
 * @param cb_freeNode
 */
#define sllist_free(list, cb_freeData, cb_freeNode) (llist_free(list, cb_freeData, cb_freeNode))

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref single_linked_list "SingleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "SingleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
#define sllist_selectFirst(list) ((SingleLinkedListNode *) llist_selectFirst((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no next element.
 */
#define sllist_selectNext(list) ((SingleLinkedListNode *) llist_selectNext((LinkedList *) list))

// * Selects the previous node in the list based on the currently selected one.
// * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element will be selected.
// * @return A pointer to the previous \ref double_linked_list_node "DoubleLinkedListNode",
// *  or `NULL` if the list has no previous element.
// */
//DLL_EXP_SLLIST SingleLinkedListNode *sllist_selectPrevious(SingleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
#define sllist_selectLast(list) ((SingleLinkedListNode *) llist_selectLast((LinkedList *) list))

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no elements.
 */
#define sllist_selectFirstData(list) (llist_selectFirstData((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no next element.
 */
#define sllist_selectNextData(list) (llist_selectNextData((LinkedList *) list))

/**
 * Returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be returned.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
#define sllist_getByIndex(list, index) ((SingleLinkedListNode *) llist_getByIndex((LinkedList *) list, index))

/**
 * Selects and returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be selected.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
#define sllist_selectByIndex(list, index) ((SingleLinkedListNode *) llist_selectByIndex((LinkedList *) list, index))

/**
 * Appends a \ref double_linked_list_node "DoubleLinkedListNode" with the given data at the end of the
 *  \ref double_linked_list "DoubleLinkedList".
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_SLLIST bool sllist_append(SingleLinkedList *list, void *data, SingleLinkedListNode * (*cb_allocNode)());

/** @} */ // end of group_sllist
