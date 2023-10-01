#include "sllist.h"

#include <stdlib.h>

SingleLinkedListNode *sllist_createNode() {
	return calloc(1, sizeof(SingleLinkedListNode));
}
