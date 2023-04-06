#pragma once

#include <malloc.h>
#include <stdbool.h>

#include "../lists/double/dllist.h"
#include "./macros.h"
#include "./types.h"

typedef struct arguments_option {
	/** Token character used when searching for the <code>Option</code> or rendering the help text. */
	np_args_char token;
	
	/** Name string used when searching for the <code>Option</code> or rendering the help text. */
	np_args_char *name;
	
	/** Description that is shown in the help text. */
	np_args_char *description;
	
	/** Binary flags used to toggle some special behaviour for the <code>Option</code> during the parsing process. */
	OptionFlags flags;
	
	/** List of values given to the <code>Option</code> if it is allowed to have any. */
	DoubleLinkedList *arguments;
	
	/** Counter used to indicate how many times the <code>Option</code> was used during the parsing process. */
	size_t occurrences;
	
	/**
	 * Counter used to memorize how many verbs this <code>Option</code> was registered in to help during the memory
	 * freeing process.
	 * Once this counter is decremented to 0 after a verb's options are released, it should be freed from memory !
	 */
	int32_t registrationCount;
} Option;

typedef struct arguments_verb {
	/** Name used when searching for sub-verbs or rendering the help text. */
	np_args_char *name;
	
	/** Description that is shown in the help text. */
	np_args_char *description;
	
	/** List of registered <code>Option</code> via the 'RegisterOption' function. */
	DoubleLinkedList *options;
	
	/** List of registered sub-<code>Verb</code> via the 'RegisterVerb' function. */
	DoubleLinkedList *verbs;
	
	/** Flag used to indicate if the verb was used at any point during the parsing process. */
	bool wasUsed;
	
	/** Reference to a potential <code>Verb</code> into which this one was registered. */
	struct arguments_verb *parentVerb;
} Verb;
