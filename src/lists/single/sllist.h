/** @file */

#pragma once

#include "../structs.h"
#include "../commons.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 * Creates a single linked list.
 * @return A pointer to a newly allocated \ref single_linked_list "SingleLinkedList" structure.
 */
#define sllist_create() ((SingleLinkedList *) llist_create())

/**
 * Creates a single linked list node.
 * @return A pointer to a newly allocated \ref single_linked_list_node "SingleLinkedListNode" structure.
 */
DLL_EXPORT SingleLinkedListNode *sllist_createNode();

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
#define sllist_selectFirst(list) ((SingleLinkedListNode *) llist_selectFirst(list))

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *  or `NULL` if the list has no next element.
 */
#define dllist_selectNext(list) ((SingleLinkedListNode *) llist_selectNext(list))
