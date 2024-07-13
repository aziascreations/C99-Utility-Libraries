/** @file */

#if !defined(NP_ONCE_C99_GOODIES_LLIST_DOUBLE)
#define NP_ONCE_C99_GOODIES_LLIST_DOUBLE

#include <malloc.h>
#include <stdbool.h>

#include "../../platform.h"

#include "../structs.h"
#include "../commons.h"

#if defined(NP_GOODIES_EXPORT_DLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_DLLIST NP_DLL_EXPORT
#else
	#define DLL_EXP_DLLIST
#endif

/** @defgroup group_dllist Double linked lists
 *
 *  Extension of the \ref group_llist "Linked lists commons module" that implements all the required logic for
 *   interacting with single linked lists.
 *
 *  It should be noted that the functions whose logic is shared with their counterpart in the
 *   \ref group_sllist "Single linked lists module" are implemented in the form of a simple macro that links
 *   back to the appropriate function in the \ref group_llist "Linked lists commons module".
 *
 *  \see \ref group_sllist "Single linked lists module"
 *  \see \ref group_dllist "Double linked lists module"
 *
 *  @{
 */

/**
 * Creates an empty double linked list.
 * @return A pointer to a newly allocated \ref double_linked_list "DoubleLinkedList" structure.
 */
#define dllist_create() ((DoubleLinkedList *) llist_create())

/**
 * Creates an empty \ref double_linked_list_node "DoubleLinkedListNode".
 * @return A pointer to a newly allocated \ref double_linked_list_node "DoubleLinkedListNode" structure.
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_createNode();

/**
 * Frees the given list and all of its nodes' data using the given callbacks for both the data and nodes.
 * @param list The \ref double_linked_list "DoubleLinkedList" to be freed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
#define dllist_free(list, cb_freeData, cb_freeNode) (llist_free((LinkedList *) list, cb_freeData, cb_freeNode))

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no elements.
 */
#define dllist_selectFirst(list) ((DoubleLinkedListNode *) llist_selectFirst((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no next element.
 */
#define dllist_selectNext(list) ((DoubleLinkedListNode *) llist_selectNext((LinkedList *) list))

/**
 * Retrieves the previous node and returns it without changing the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element's data will be selected.
 * @return A pointer to the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_getPrevious(DoubleLinkedList *list);

/**
 * Retrieves the previous node and returns its data without changing the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element's data will be selected.
 * @return The appropriate data pointer contained in the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
DLL_EXP_DLLIST void *dllist_getPreviousData(DoubleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element will be selected.
 * @return A pointer to the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
DLL_EXP_DLLIST DoubleLinkedListNode *dllist_selectPrevious(DoubleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one and returns it's data.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose previous element will be selected.
 * @return The appropriate data pointer contained in the previous \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
DLL_EXP_DLLIST void *dllist_selectPreviousData(DoubleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no elements.
 */
#define dllist_selectLast(list) ((DoubleLinkedListNode *) llist_selectLast((LinkedList *) list))

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *         or `NULL` if the list has no elements.
 */
#define dllist_selectFirstData(list) (llist_selectFirstData((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *         or `NULL` if the list has no next element.
 */
#define dllist_selectNextData(list) (llist_selectNextData((LinkedList *) list))

/**
 * Selects the last node in the list as the current one and returns its data pointer.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref double_linked_list_node "DoubleLinkedListNode"'s data,
 *         or `NULL` if the list has no elements.
 */
#define dllist_selectLastData(list) (llist_selectLastData((LinkedList *) list))

/**
 * Retrieves the next node and returns it without changing the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element's data will be selected.
 * @return A pointer to the next \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
#define dllist_getNext(list) ((DoubleLinkedListNode *) llist_getNext((LinkedList *) list))

/**
 * Retrieves the next node and returns its data without changing the currently selected one.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose next element's data will be selected.
 * @return The appropriate data pointer contained in the next \ref double_linked_list_node "DoubleLinkedListNode",
 *         or `NULL` if the list has no previous element.
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
 * Prepends a \ref double_linked_list_node "DoubleLinkedListNode" with the given data at the start of the
 *  \ref double_linked_list "DoubleLinkedList".
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_DLLIST bool dllist_prepend(DoubleLinkedList *list, void *data, DoubleLinkedListNode *(*cb_allocNode)());

/**
 * Appends a \ref double_linked_list_node "DoubleLinkedListNode" with the given data at the end of the
 *  \ref double_linked_list "DoubleLinkedList".
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_DLLIST bool dllist_append(DoubleLinkedList *list, void *data, DoubleLinkedListNode *(*cb_allocNode)());

/**
 * Inserts a \ref double_linked_list_node "DoubleLinkedListNode" after the currently selected one.
 * @param list The relevant \ref double_linked_list "DoubleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref double_linked_list_node "DoubleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref double_linked_list_node "DoubleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was inserted properly, <code>false</code> otherwise.
 */
DLL_EXP_DLLIST bool dllist_insertAfterCurrent(
		DoubleLinkedList *list,
		void *data,
		DoubleLinkedListNode *(*cb_allocNode)());

/**
 * Removes the first \ref double_linked_list_node "DoubleLinkedListNode" and frees it with the given callbacks.<br>
 * If the first node was selected, the `current` pointer is set back to `NULL`.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose first element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_DLLIST bool dllist_deleteFirst(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 * Removes the currently selected \ref double_linked_list_node "DoubleLinkedListNode" and frees it with the given callbacks.<br>
 * It also sets the `current` pointer back to `NULL`.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
bool dllist_deleteCurrent(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 * Removes the last \ref double_linked_list_node "DoubleLinkedListNode" and frees it with the given callbacks.<br>
 * If the last node was selected, the `current` pointer is set back to `NULL`.
 * @param list The \ref double_linked_list "DoubleLinkedList" whose last element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_DLLIST bool dllist_deleteLast(
		DoubleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/** @} */ // end of group_dllist

#endif /* !NP_ONCE_C99_GOODIES_LLIST_DOUBLE */
