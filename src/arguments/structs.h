/** @file */

#if !defined(NP_ONCE_C99_GOODIES_ARGUMENTS_STRUCTS)
#define NP_ONCE_C99_GOODIES_ARGUMENTS_STRUCTS

#include <malloc.h>
#include <stdbool.h>

#include "../platform.h"
#include "../lists/double/dllist.h"
#include "./types.h"


// Unicode macros
#if defined(NP_UNICODE)
	#define arguments_option arguments_option_w
	#define Option OptionW
	#define arguments_verb arguments_verb_w
	#define Verb VerbW
#else
	#define arguments_option arguments_option_a
	#define Option OptionA
	#define arguments_verb arguments_verb_a
	#define Verb VerbA
#endif


/**
 * Structure used to hold any information about a singular option using `char` strings for any text-related values.
 *
 * <b>Warning:</b><br>
 * Any reference to np_args_char can be the equivalent of char or wchar_t depending on 2 compiler constants.<br>
 * See \ref arguments or \ref arguments/macros.h for more info.<br>
 */
typedef struct arguments_option_a {
	/**
	 * Token character used when searching for the \ref arguments_option "Option" or rendering the help text.
	 */
	char token;
	
	/**
	 * Name string used when searching for the \ref arguments_option "Option" or rendering the help text.
	 */
	char *name;
	
	/**
	 * Description that is shown in the help text.
	 */
	char *description;
	
	/**
	 * Binary flags used to toggle some special behaviour for the \ref arguments_option "Option" during the parsing process.
	 * \see EOptionFlags
	 */
	OptionFlags flags;
	
	/**
	 * List of values given to the \ref arguments_option "Option" if it is allowed to have any.<br>
	 * These values are stored in the form of copied `np_args_char` strings.
	 * \see EOptionFlags
	 * \see FLAG_OPTION_HAS_VALUE
	 * \see FLAG_OPTION_HAS_MULTIPLE_VALUE
	 */
	DoubleLinkedList *arguments;
	
	/**
	 * Counter used to indicate how many times the \ref arguments_option "Option" was used during the parsing process.
	 * \see EOptionFlags
	 * \see FLAG_OPTION_REPEATABLE
	 */
	size_t occurrences;
	
	/**
	 * Counter used to memorize how many verbs this \ref arguments_option "Option" was registered in a
	 *  \ref arguments_verb "Verb" in order to help during the memory freeing process.<br>
	 * Once this counter is decremented to 0 after a \ref arguments_verb "Verb"'s options are all released,
	 *  this \ref arguments_option "Option" should be freed from memory !
	 */
	int32_t registrationCount;
} OptionA;


/**
 * Structure used to hold any information about a singular option using `wchar_t` strings for any text-related values.
 *
 * <b>Warning:</b><br>
 * Any reference to np_args_char can be the equivalent of char or wchar_t depending on 2 compiler constants.<br>
 * See \ref arguments or \ref arguments/macros.h for more info.<br>
 */
typedef struct arguments_option_w {
	/**
	 * Token character used when searching for the \ref arguments_option "Option" or rendering the help text.
	 */
	wchar_t token;
	
	/**
	 * Name string used when searching for the \ref arguments_option "Option" or rendering the help text.
	 */
	wchar_t *name;
	
	/**
	 * Description that is shown in the help text.
	 */
	wchar_t *description;
	
	/**
	 * Binary flags used to toggle some special behaviour for the \ref arguments_option "Option" during the parsing process.
	 * \see EOptionFlags
	 */
	OptionFlags flags;
	
	/**
	 * List of values given to the \ref arguments_option "Option" if it is allowed to have any.<br>
	 * These values are stored in the form of copied `np_args_char` strings.
	 * \see EOptionFlags
	 * \see FLAG_OPTION_HAS_VALUE
	 * \see FLAG_OPTION_HAS_MULTIPLE_VALUE
	 */
	DoubleLinkedList *arguments;
	
	/**
	 * Counter used to indicate how many times the \ref arguments_option "Option" was used during the parsing process.
	 * \see EOptionFlags
	 * \see FLAG_OPTION_REPEATABLE
	 */
	size_t occurrences;
	
	/**
	 * Counter used to memorize how many verbs this \ref arguments_option "Option" was registered in a
	 *  \ref arguments_verb "Verb" in order to help during the memory freeing process.<br>
	 * Once this counter is decremented to 0 after a \ref arguments_verb "Verb"'s options are all released,
	 *  this \ref arguments_option "Option" should be freed from memory !
	 */
	int32_t registrationCount;
} OptionW;


/**
 * Structure used to hold all the info about any parsable launch-arguments which may include
 *  \ref arguments_verb "sub-verbs" and \ref arguments_option "Options".<br>
 * Uses `char` strings for any text-related values.
 *
 * <b>Warning:</b><br>
 * Any reference to np_args_char can be the equivalent of char or wchar_t depending on 2 compiler constants.<br>
 * See \ref arguments or \ref arguments/macros.h for more info.<br>
 *
 * Any reference to a *sub-verb* actually refers to a regular \ref arguments_verb "Verb" which can be considered as the
 *  another verb's children.
 */
typedef struct arguments_verb_a {
	/**
	 * Name used when searching for sub-verbs or preparing the help text.
	 */
	char *name;
	
	/**
	 * Description that is shown in the help text.
	 */
	char *description;
	
	/**
	 * List of registered \ref arguments_option "Options" via the \ref args_registerOption function.
	 */
	DoubleLinkedList *options;
	
	/**
	 * List of registered sub-\ref arguments_verb "Verb" via the \ref args_registerVerb function.
	 */
	DoubleLinkedList *verbs;
	
	/**
	 * Flag used to indicate if the verb was used at any point during the parsing process.
	 */
	bool wasUsed;
	
	/**
	 * Reference to a potential \ref arguments_verb "Verb" into which this one was registered.
	 */
	struct arguments_verb_a *parentVerb;
} VerbA;


/**
 * Structure used to hold all the info about any parsable launch-arguments which may include
 *  \ref arguments_verb "sub-verbs" and \ref arguments_option "Options".<br>
 * Uses `wchar_t` strings for any text-related values.
 *
 * <b>Warning:</b><br>
 * Any reference to np_args_char can be the equivalent of char or wchar_t depending on 2 compiler constants.<br>
 * See \ref arguments or \ref arguments/macros.h for more info.<br>
 *
 * Any reference to a *sub-verb* actually refers to a regular \ref arguments_verb "Verb" which can be considered as the
 *  another verb's children.
 */
typedef struct arguments_verb_w {
	/**
	 * Name used when searching for sub-verbs or preparing the help text.
	 */
	wchar_t *name;
	
	/**
	 * Description that is shown in the help text.
	 */
	wchar_t *description;
	
	/**
	 * List of registered \ref arguments_option "Options" via the \ref args_registerOption function.
	 */
	DoubleLinkedList *options;
	
	/**
	 * List of registered sub-\ref arguments_verb "Verb" via the \ref args_registerVerb function.
	 */
	DoubleLinkedList *verbs;
	
	/**
	 * Flag used to indicate if the verb was used at any point during the parsing process.
	 */
	bool wasUsed;
	
	/**
	 * Reference to a potential \ref arguments_verb "Verb" into which this one was registered.
	 */
	struct arguments_verb_w *parentVerb;
} VerbW;

#endif /* !NP_ONCE_C99_GOODIES_ARGUMENTS_STRUCTS */
