/** @file */

#pragma once

#include <malloc.h>
#include <stdbool.h>

#include "./structs.h"

#ifdef NP_DLLIST_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 * Creates a double linked list that uses the given function to free the nodes' data.
 * @param free Pointer to a `void free(void *data)` function that will be called for each list element when freeing the
 *  entire list or on a single element when removing it.
 *  The function will receive the node's data pointer as-is.
 * @return A pointer to a newly allocated \ref double_linked_list "DoubleLinkedList" structure.
 */
DLL_EXPORT DoubleLinkedList *dllist_create(void (*free)(void *data));

/**
 * Frees the given list and all of its nodes' data.
 * @param list The \ref double_linked_list "DoubleLinkedList" to be freed.
 */
DLL_EXPORT void dllist_free(DoubleLinkedList *list);

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectFirst(DoubleLinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no next element.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectNext(DoubleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element will be selected.
 * @return A pointer to the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no previous element.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectPrevious(DoubleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectLast(DoubleLinkedList *list);

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no elements.
 */
DLL_EXPORT void *dllist_selectFirstData(DoubleLinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *  or `NULL` if the list has no next element.
 */
DLL_EXPORT void *dllist_selectNextData(DoubleLinkedList *list);

/**
 * Returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be returned.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_getByIndex(DoubleLinkedList *list, size_t index);

/**
 * Selects and returns a \ref double_linked_list_node "DoubleLinkedListNode" via its given index in the list.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose element will be selected.
 * @param index The \ref double_linked_list_node "DoubleLinkedListNode"'s index.
 * @return The relevant \ref double_linked_list_node "DoubleLinkedListNode", or `NULL` if not found.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectByIndex(DoubleLinkedList *list, size_t index);

/**
 * Appends a \ref double_linked_list_node "DoubleLinkedListNode" with the given data at the end of the
 *  \ref double_linked_list "DoubleLinkedList".
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXPORT bool dllist_append(DoubleLinkedList *list, void *data);
