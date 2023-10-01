#pragma once

#include "structs.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_DLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 * Creates a single linked list.
 * @return A pointer to a newly allocated \ref linked_list "LinkedList" structure.
 */
DLL_EXPORT LinkedList *llist_create();

/**
 * Frees the given list and all of its nodes' data using the callback for both the data and nodes.
 * @param list The \ref linked_list "LinkedList" to be freed.
 * @param cb_freeData
 * @param cb_freeNode
 */
DLL_EXPORT void llist_free(
		LinkedList * list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data)
);

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref linked_list "LinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "SingleLinkedListNode",
 *  or `NULL` if the list has no elements.
 */
DLL_EXPORT LinkedListNode *llist_selectFirst(LinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no next element.
 */
DLL_EXPORT LinkedListNode *llist_selectNext(LinkedList *list);

LinkedListNode *llist_selectLast(LinkedList *list);

void *llist_selectFirstData(LinkedList *list);

void *llist_selectNextData(LinkedList *list);

LinkedListNode *llist_getByIndex(LinkedList *list, size_t index);

LinkedListNode *llist_selectByIndex(LinkedList *list, size_t index);