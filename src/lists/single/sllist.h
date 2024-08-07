/** @file */

#if !defined(NP_ONCE_C99_GOODIES_LLIST_SINGLE)
#define NP_ONCE_C99_GOODIES_LLIST_SINGLE

#include <stdbool.h>

#include "../../platform.h"

#include "../structs.h"
#include "../commons.h"

#if defined(NP_GOODIES_EXPORT_SLLIST) || defined(NP_GOODIES_EXPORT_LIST_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_SLLIST NP_DLL_EXPORT
#else
	#define DLL_EXP_SLLIST
#endif

/** @defgroup group_sllist Single linked lists
 *
 *  Extension of the \ref group_llist "Linked lists commons module" that implements all the required logic for
 *   interacting with single linked lists.
 *
 *  It should be noted that the functions whose logic is shared with their counterpart in the
 *   \ref group_dllist "Double linked lists module" are implemented in the form of a simple macro that links
 *   back to the appropriate function in the \ref group_llist "Linked lists commons module".
 *
 *  \see \ref group_llist "Linked lists commons module"
 *  \see \ref group_dllist "Double linked lists module"
 *
 *  @{
 */

/**
 * Creates an empty single linked list.
 * @return A pointer to a newly allocated \ref single_linked_list "SingleLinkedList" structure.
 */
#define sllist_create() ((SingleLinkedList *) llist_create())

/**
 * Creates an empty \ref single_linked_list_node "SingleLinkedListNode".
 * @return A pointer to a newly allocated \ref single_linked_list_node "SingleLinkedListNode" structure.
 */
DLL_EXP_SLLIST SingleLinkedListNode *sllist_createNode();

/**
 * Frees the given list and all of its nodes' data using the given callbacks for both the data and nodes.
 * @param list The \ref single_linked_list "SingleLinkedList" to be freed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
#define sllist_free(list, cb_freeData, cb_freeNode) (llist_free(list, cb_freeData, cb_freeNode))

/**
 * Selects the first node in the list as the current one and returns it.
 * @param list The \ref single_linked_list "SingleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no elements.
 */
#define sllist_selectFirst(list) ((SingleLinkedListNode *) llist_selectFirst((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one.
 * @param list The \ref single_linked_list "SingleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no next element.
 */
#define sllist_selectNext(list) ((SingleLinkedListNode *) llist_selectNext((LinkedList *) list))

/**
 * Retrieves the previous node and returns it without changing the currently selected one.
 * @param list The \ref single_linked_list "SingleLinkedList" whose previous element's data will be selected.
 * @return A pointer to the previous \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 */
DLL_EXP_SLLIST SingleLinkedListNode *sllist_getPrevious(SingleLinkedList *list);

/**
 * Retrieves the previous node and returns its data without changing the currently selected one.
 * @param list The \ref single_linked_list "SingleLinkedList" whose previous element's data will be selected.
 * @return The appropriate data pointer contained in the previous \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 */
DLL_EXP_SLLIST void *sllist_getPreviousData(SingleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one and returns it.
 * @param list The \ref single_linked_list "SingleLinkedList" whose previous element will be selected.
 * @return A pointer to the previous \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 */
DLL_EXP_SLLIST SingleLinkedListNode *sllist_selectPrevious(SingleLinkedList *list);

/**
 * Selects the previous node in the list based on the currently selected one and returns it's data.
 * @param list The \ref single_linked_list "SingleLinkedList" whose previous element will be selected.
 * @return The appropriate data pointer contained in the previous \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 */
DLL_EXP_SLLIST void *sllist_selectPreviousData(SingleLinkedList *list);

/**
 * Selects the last node in the list as the current one and returns it.
 * @param list The \ref single_linked_list "SingleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no elements.
 */
#define sllist_selectLast(list) ((SingleLinkedListNode *) llist_selectLast((LinkedList *) list))

/**
 * Selects the first node in the list as the current one and returns its data pointer.
 * @param list The \ref single_linked_list "SingleLinkedList" whose first element will be selected.
 * @return A pointer to the first \ref single_linked_list_node "SingleLinkedListNode"'s data,
 *         or `NULL` if the list has no elements.
 */
#define sllist_selectFirstData(list) (llist_selectFirstData((LinkedList *) list))

/**
 * Selects the next node in the list based on the currently selected one and returns its data pointer.
 * @param list The \ref single_linked_list "SingleLinkedList" whose next element will be selected.
 * @return A pointer to the next \ref single_linked_list_node "SingleLinkedListNode"'s data,
 *         or `NULL` if the list has no next element.
 */
#define sllist_selectNextData(list) (llist_selectNextData((LinkedList *) list))

/**
 * Selects the first last in the list as the current one and returns its data pointer.
 * @param list The \ref single_linked_list "SingleLinkedList" whose last element will be selected.
 * @return A pointer to the last \ref single_linked_list_node "SingleLinkedListNode"'s data,
 *         or `NULL` if the list has no elements.
 */
#define sllist_selectLastData(list) (llist_selectLastData((LinkedList *) list))

/**
 * Returns a \ref single_linked_list_node "SingleLinkedListNode" via its given index in the list.
 * @param list The \ref single_linked_list "SingleLinkedList" whose element will be returned.
 * @param index The \ref single_linked_list_node "SingleLinkedListNode"'s index.
 * @return The relevant \ref single_linked_list_node "SingleLinkedListNode", or `NULL` if not found.
 */
#define sllist_getByIndex(list, index) ((SingleLinkedListNode *) llist_getByIndex((LinkedList *) list, index))

/**
 * Selects and returns a \ref single_linked_list_node "SingleLinkedListNode" via its given index in the list.
 * @param list The \ref single_linked_list "SingleLinkedList" whose element will be selected.
 * @param index The \ref single_linked_list_node "SingleLinkedListNode"'s index.
 * @return The relevant \ref single_linked_list_node "SingleLinkedListNode", or `NULL` if not found.
 */
#define sllist_selectByIndex(list, index) ((SingleLinkedListNode *) llist_selectByIndex((LinkedList *) list, index))

/**
 * Retrieves the next node and returns it without changing the currently selected one.
 * @param list The \ref single_linked_list "SingleLinkedList" whose next element's data will be selected.
 * @return A pointer to the next \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
#define sllist_getNext(list) ((SingleLinkedListNode *) llist_getNext((LinkedList *) list))

/**
 * Retrieves the next node and returns its data without changing the currently selected one.
 * @param list The \ref single_linked_list "SingleLinkedList" whose next element's data will be selected.
 * @return The appropriate data pointer contained in the next \ref single_linked_list_node "SingleLinkedListNode",
 *         or `NULL` if the list has no previous element.
 */
#define sllist_getNextData(list) (llist_getNextData((LinkedList *) list))

/**
 * Prepends a \ref single_linked_list_node "SingleLinkedListNode" with the given data at the start of the
 *  \ref single_linked_list "SingleLinkedList".
 * @param list The relevant \ref single_linked_list "SingleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref single_linked_list_node "SingleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref single_linked_list_node "SingleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_SLLIST bool sllist_prepend(SingleLinkedList *list, void *data, SingleLinkedListNode *(*cb_allocNode)());

/**
 * Appends a \ref single_linked_list_node "SingleLinkedListNode" with the given data at the end of the
 *  \ref single_linked_list "SingleLinkedList".
 * @param list The relevant \ref single_linked_list "SingleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref single_linked_list_node "SingleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref single_linked_list_node "SingleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was appended properly, <code>false</code> otherwise.
 */
DLL_EXP_SLLIST bool sllist_append(SingleLinkedList *list, void *data, SingleLinkedListNode *(*cb_allocNode)());

/**
 * Inserts a \ref single_linked_list_node "SingleLinkedListNode" after the currently selected one.
 * @param list The relevant \ref single_linked_list "SingleLinkedList".
 * @param data Pointer to the data that will be held in a new \ref single_linked_list_node "SingleLinkedListNode".
 * @param cb_allocNode A function that allocates and return a \ref single_linked_list_node "SingleLinkedListNode".<br>
 *                     If left as `NULL`, the standard `sllist_createNode` function will be used !
 * @return <code>true</code> if it was inserted properly, <code>false</code> otherwise.
 */
DLL_EXP_SLLIST bool sllist_insertAfterCurrent(
		SingleLinkedList *list,
		void *data,
		SingleLinkedListNode *(*cb_allocNode)());

/**
 * Removes the first \ref single_linked_list_node "SingleLinkedListNode" and frees it with the given callbacks.<br>
 * If the first node was selected, the `current` pointer is set back to `NULL`.
 * @param list The \ref single_linked_list "SingleLinkedList" whose first element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_SLLIST bool sllist_deleteFirst(
		SingleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 * Removes the currently selected \ref single_linked_list_node "SingleLinkedListNode" and frees it with the given callbacks.<br>
 * It also sets the `current` pointer back to `NULL`.
 * @param list The \ref single_linked_list "SingleLinkedList" whose first element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_SLLIST bool sllist_deleteCurrent(
		SingleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/**
 * Removes the last \ref single_linked_list_node "SingleLinkedListNode" and frees it with the given callbacks.<br>
 * If the last node was selected, the `current` pointer is set back to `NULL`.
 * @param list The \ref single_linked_list "SingleLinkedList" whose last element will be removed.
 * @param cb_freeData A function that will free the node's data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @param cb_freeNode A function that will free the node's structure.<br>
 *                    If left as `NULL`, the standard `void free(void *data)` function will be used !
 * @return <code>true</code> if it was deleted properly, <code>false</code> otherwise.
 * @warning This function can be quite CPU intensive in single linked lists due to its lack of `*previous` pointer.<br>
 *          In a worst case scenario its performance will be `O(n)`.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_SLLIST bool sllist_deleteLast(
		SingleLinkedList *list,
		void (*cb_freeData)(void *data),
		void (*cb_freeNode)(void *data));

/** @} */ // end of group_sllist

#endif /* !NP_ONCE_C99_GOODIES_LLIST_SINGLE */
