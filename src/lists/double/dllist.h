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
 * @param free
 * @return
 */
DLL_EXPORT DoubleLinkedList *dllist_create(void (*free)(void *data));

/**
 * Frees the given list and all of its nodes' data.
 * @param list
 */
DLL_EXPORT void dllist_free(DoubleLinkedList *list);

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list
 * @return
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectFirst(DoubleLinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list
 * @return The relevant node, or NULL if no node was selected or was found as the next one.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectNext(DoubleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one.
 * @param list
 * @return The relevant node, or NULL if no node was selected or was found as the previous one.
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectPrevious(DoubleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list
 * @return
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectLast(DoubleLinkedList *list);

/**
 * Selects the first node in the list as the current one and returns its data.
 * @param list
 * @return
 */
DLL_EXPORT void *dllist_selectFirstData(DoubleLinkedList *list);

/**
 * Selects the next node in the list based on the currently selected one and returns its data.
 * @param list
 * @return The relevant node's data, or NULL if no node was selected or was found as the next one.
 */
DLL_EXPORT void *dllist_selectNextData(DoubleLinkedList *list);

/**
 *
 * @param list
 * @param index
 * @return
 */
DLL_EXPORT DoubleLinkedListNode *dllist_getByIndex(DoubleLinkedList *list, size_t index);

/**
 *
 * @param list
 * @param index
 * @return
 */
DLL_EXPORT DoubleLinkedListNode *dllist_selectByIndex(DoubleLinkedList *list, size_t index);

/**
 * Appends a node at the end of the given list.
 * @param list
 * @param data
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXPORT bool dllist_append(DoubleLinkedList *list, void *data);

// Checking if the static module is explicitly disabled.
#ifndef NP_DLLIST_NO_MODULE
/**
 * Public static module's interface.
 */
static DoubleLinkedListModuleInterface dllist = {
		.create = dllist_create,
		.free = dllist_free,
		.selectFirst = dllist_selectFirst,
		.selectNext = dllist_selectNext,
		.selectPrevious = dllist_selectPrevious,
		.selectLast = dllist_selectLast,
		.getByIndex = dllist_getByIndex,
		.selectByIndex = dllist_selectByIndex,
		.append = dllist_append,
};

/**
 * Macro that resolves to the normal <code>dllist</code> static module interface.
 */
#define DoubleLinkedLists dllist
#endif
