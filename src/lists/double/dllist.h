/** @file */

#pragma once

#include <malloc.h>
#include <stdbool.h>

#include "../structs.h"
#include "../commons.h"

#if defined(NP_GOODIES_EXPORT_DLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXP_DLLIST __declspec(dllexport)
#else
#define DLL_EXP_DLLIST
#endif

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
 *
 *  \see \ref group_llist "Linked lists commons module"
 *  \see \ref group_sllist "Single linked lists module"
 *
 *  \see double_linked_list
 *  \see double_linked_list_node
 *
 *  @{
 */

/**
 * Creates a double linked list that uses the given function to free the nodes' data.
 * @param free Pointer to a `void free(void *data)` function that will be called for each list element when freeing the
 *  entire list or on a single element when removing it.
 *  The function will receive the node's data pointer as-is.
 * @return A pointer to a newly allocated \ref double_linked_list "DoubleLinkedList" structure.
 */
#define dllist_create() ((DoubleLinkedList *) llist_create())

/**
 * Creates a single linked list node.
 * @return A pointer to a newly allocated \ref single_linked_list_node "SingleLinkedListNode" structure.
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_createNode();

/**
 * Frees the given list and all of its nodes' data.
 * @param list The \ref double_linked_list "DoubleLinkedList" to be freed.
 * @param cb_freeData
 * @param cb_freeNode
 */
#define dllist_free(list, cb_freeData, cb_freeNode) (llist_free((LinkedList *) list, cb_freeData, cb_freeNode))

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
#define dllist_selectFirst(list) ((DoubleLinkedListNode *) llist_selectFirst((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no next element.
 */
#define dllist_selectNext(list) ((DoubleLinkedListNode *) llist_selectNext((LinkedList *) list))

/**
 *
 * @param list
 * @return
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_getPrevious(DoubleLinkedList *list);

/**
 *
 * @param list
 * @return
 */
DLL_EXP_DLLIST void *dllist_getPreviousData(DoubleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one.
 * [Set the current pointer to new or null !]
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element will be selected.
 * @return A pointer to the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no previous element.
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_selectPrevious(DoubleLinkedList *list);

/**
 *
 * @param list
 * @return
 */
DLL_EXP_DLLIST void *dllist_selectPreviousData(DoubleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
#define dllist_selectLast(list) ((DoubleLinkedListNode *) llist_selectLast((LinkedList *) list))

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no elements.
 */
#define dllist_selectFirstData(list) (llist_selectFirstData((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no next element.
 */
#define dllist_selectNextData(list) (llist_selectNextData((LinkedList *) list))

/**
 * TODO
 */
#define dllist_selectLastData(list) (llist_selectLastData((LinkedList *) list))

/**
 * TODO
 */
#define dllist_getNext(list) ((DoubleLinkedListNode *) llist_getNext((LinkedList *) list))

/**
 * TODO
 */
#define dllist_getNextData(list) (llist_getNextData((LinkedList *) list))

/**
 * Returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be returned.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
#define dllist_getByIndex(list, index) ((DoubleLinkedListNode *) llist_getByIndex((LinkedList *) list, index))

/**
 * Selects and returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be selected.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
#define dllist_selectByIndex(list, index) ((DoubleLinkedListNode *) llist_selectByIndex((LinkedList *) list, index))

/**
 * ???
 * @param list
 * @param data
 * @param cb_allocNode
 * @return
 */
DLL_EXP_DLLIST bool dllist_prepend(DoubleLinkedList *list, void *data, DoubleLinkedListNode *(*cb_allocNode)());

/**
 * Appends a \ref double_linked_list_node "DoubleLinkedListNode" with the given data at the end of the
 *  \ref double_linked_list "DoubleLinkedList".
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_DLLIST bool dllist_append(DoubleLinkedList *list, void *data, DoubleLinkedListNode *(*cb_allocNode)());

/**
 * ???
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data
 * @param cb_allocNode
 * @return (If not current, false)
 */
DLL_EXP_DLLIST bool dllist_insertAfterCurrent(
		DoubleLinkedList *list,
		void *data,
		DoubleLinkedListNode *(*cb_allocNode)());

/**
 *
 * @param list
 * @param cb_freeData
 * @param cb_freeNode
 * @return
 */
DLL_EXP_DLLIST bool dllist_deleteFirst(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 *
 * @param list
 * @param cb_freeData
 * @param cb_freeNode
 * @return
 */
bool dllist_deleteCurrent(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 *
 * @param list
 * @param cb_freeData
 * @param cb_freeNode
 * @return
 */
DLL_EXP_DLLIST bool dllist_deleteLast(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/** @} */ // end of group_dllist
