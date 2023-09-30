#pragma once

#include "structs.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 * Creates a single linked list that uses the given function to free the nodes' data.
 * @param cb_freeData Pointer to a `void free(void *data)` function that will be called for each list element when freeing the
 *  entire list or on a single element when removing it.
 *  The function will receive the node's data pointer as-is.
 * @return A pointer to a newly allocated \ref single_linked_list "SingleLinkedList" structure.
 */
DLL_EXPORT SingleLinkedList *sllist_create(
		void (*cb_freeData)(void *data)
		);

/**
 * Creates a single linked list that uses the given functions to free the nodes' data as well as allocate and free
 * the node itself.
 * @param cb_freeData
 * @param cb_createNode
 * @param cb_freeNode
 * @return A pointer to a newly allocated \ref single_linked_list "SingleLinkedList" structure.
 */
DLL_EXPORT SingleLinkedList *sllist_createComplex(
		void (*cb_freeData)(void *data),
		SingleLinkedListNode *(*cb_mallocNode)(),
		void (*cb_freeNode)(void *data)
		);

DLL_EXPORT SingleLinkedListNode *sllist_createNode();
