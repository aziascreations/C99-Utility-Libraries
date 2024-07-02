/** @file */

#if !defined(NP_ONCE_C99_GOODIES_ARGUMENTS_MAIN)
#define NP_ONCE_C99_GOODIES_ARGUMENTS_MAIN

#include "../platform.h"

#include "./errors.h"
#include "./flags.h"
#include "./structs.h"
#include "./types.h"

#include "../text.h"

#if defined(NP_GOODIES_EXPORT_ARGUMENTS) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_ARGS NP_DLL_EXPORT
#else
	#define DLL_EXP_ARGS
#endif

// Macros

#define args_canOptionHaveMultipleValue(option) ((option)->flags & FLAG_OPTION_HAS_VALUE && (option)->flags & FLAG_OPTION_REPEATABLE)

#define args_canOptionHaveMultipleValueA args_canOptionHaveMultipleValue
#define args_canOptionHaveMultipleValueW args_canOptionHaveMultipleValue

#define args_wasOptionUsed(option) (option->occurrences > 0)



// Unicode macros
#if defined(NP_UNICODE)
	// Creators
	#define args_createVerb args_createVerbW
	#define args_createOption args_createOptionW

	// Cleaners
	#define args_freeVerb args_freeVerbW
	#define args_freeOption args_freeOptionW

	// Registers
	#define args_registerVerb args_registerVerbW
	#define args_registerOption args_registerOptionW
	#define args_registerOptionRecursively args_registerOptionRecursivelyW

	// Getters
	#define args_getParentVerb args_getParentVerbW
	#define args_getOptionByToken args_getOptionByTokenW
	#define args_getOptionByName args_getOptionByNameW
	#define args_getSubVerbByName args_getSubVerbByNameW

	// Misc
	#define args_addValueToOption args_addValueToOptionW
	#define args_isVerbAlreadyRegistered args_isVerbAlreadyRegisteredW
	#define args_isOptionAlreadyRegistered args_isOptionAlreadyRegisteredW

	// Parser
	#define args_parseArguments args_parseArgumentsW
#else
	// Creators
	#define args_createVerb args_createVerbA
	#define args_createOption args_createOptionA

	// Cleaners
	#define args_freeVerb args_freeVerbA
	#define args_freeOption args_freeOptionA

	// Registers
	#define args_registerVerb args_registerVerbA
	#define args_registerOption args_registerOptionA
	#define args_registerOptionRecursively args_registerOptionRecursivelyA

	// Getters
	#define args_getParentVerb args_getParentVerbA
	#define args_getOptionByToken args_getOptionByTokenA
	#define args_getOptionByName args_getOptionByNameA
	#define args_getSubVerbByName args_getSubVerbByNameA

	// Misc
	#define args_addValueToOption args_addValueToOptionA
	#define args_isVerbAlreadyRegistered args_isVerbAlreadyRegisteredA
	#define args_isOptionAlreadyRegistered args_isOptionAlreadyRegisteredA

	// Parser
	#define args_parseArguments args_parseArgumentsA
#endif



// Creators

/**
 * Creates a \ref arguments_verb "Verb" with no parent.
 * @param verb Name used when searching for sub-verbs, leave as <code>""</code> or <code>NULL</code> for root verbs.
 * @param description Description shown in the help text.
 * @return The new \ref arguments_verb "Verb"'s pointer, or <code>NULL</code> if an error occurred.
 */
DLL_EXP_ARGS VerbA *args_createVerbA(char *verb, char *description);

/**
 * Creates a \ref arguments_verb "Verb" with no parent.
 * @param verb Name used when searching for sub-verbs, leave as <code>L""</code> or <code>NULL</code> for root verbs.
 * @param description Description shown in the help text.
 * @return The new \ref arguments_verb "Verb"'s pointer, or <code>NULL</code> if an error occurred.
 */
DLL_EXP_ARGS VerbW *args_createVerbW(wchar_t *verb, wchar_t *description);

/**
 * Creates an \ref arguments_option "Option" with the given attributes.
 * @param token Token used when searching for the option with short options, or `\0` if no token is desired.
 * @param name Name used when searching for the option, leave as <code>""</code> or <code>NULL</code> if not desired.
 * @param description Description shown in the help text.
 * @param flags \ref EOptionFlags "Option flags" used to enable some specific features.
 * @return The new \ref arguments_option "Option"'s pointer, or <code>NULL</code> if an error occurred.
 *
 * \see EOptionFlags
 */
DLL_EXP_ARGS OptionA *args_createOptionA(char token, char *name, char *description, OptionFlags flags);

/**
 * Creates an \ref arguments_option "Option" with the given attributes.
 * @param token Token used when searching for the option with short options, or `\0` if no token is desired.
 * @param name Name used when searching for the option, leave as <code>L""</code> or <code>NULL</code> if not desired.
 * @param description Description shown in the help text.
 * @param flags \ref EOptionFlags "Option flags" used to enable some specific features.
 * @return The new \ref arguments_option "Option"'s pointer, or <code>NULL</code> if an error occurred.
 *
 * \see EOptionFlags
 */
DLL_EXP_ARGS OptionW *args_createOptionW(wchar_t token, wchar_t *name, wchar_t *description, OptionFlags flags);


// Cleaners

/**
 * Frees the memory allocated to a given \ref arguments_verb "Verb" and all of it's registered
 *  sub-\ref arguments_verb "Verb" and their \ref arguments_option "Option" in a recursive manner.
 * @param verb The \ref arguments_verb "Verb" that needs to be freed.
 * @note The <code>VerbW</code> structure can also be passed to this function if typecast.
 */
DLL_EXP_ARGS void args_freeVerbA(VerbA *verb);

#define args_freeVerbW(verb) args_freeVerbA((VerbA *) verb)

/**
 * Frees the memory allocated to a given \ref arguments_option "Option" if it isn't still registered in another
 *  \ref arguments_verb "Verb".
 * @param option The \ref arguments_option "Option" that needs to be freed.
 * @note The <code>OptionW</code> structure can also be passed to this function if typecast.
 *
 * \see arguments_option::registrationCount
 */
DLL_EXP_ARGS void args_freeOptionA(OptionA *option);

#define args_freeOptionW(option) args_freeOptionA((OptionA *) option)


// Registers

/**
 * Registers a \ref arguments_verb "Verb" into another one as a sub-\ref arguments_verb "Verb".
 * @param registeredVerb The sub-\ref arguments_verb "Verb".
 * @param parentVerb The parent \ref arguments_verb "Verb" into which the other one is registered.
 * @return <code>true</code> if it was registered, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerVerbA(VerbA *registeredVerb, VerbA *parentVerb);

/**
 * Registers a \ref arguments_verb "Verb" into another one as a sub-\ref arguments_verb "Verb".
 * @param registeredVerb The sub-\ref arguments_verb "Verb".
 * @param parentVerb The parent \ref arguments_verb "Verb" into which the other one is registered.
 * @return <code>true</code> if it was registered, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerVerbW(VerbW *registeredVerb, VerbW *parentVerb);

/**
 * Registers an \ref arguments_option "Option" in a given \ref arguments_verb "Verb".
 * @param registeredOption The registered \ref arguments_option "Option".
 * @param parentVerb The \ref arguments_verb "Verb" into which the \ref arguments_option "Option" is being registered.
 * @return <code>true</code> if it was registered and not already registered into it, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerOptionA(OptionA *registeredOption, VerbA *parentVerb);

/**
 * Registers an \ref arguments_option "Option" in a given \ref arguments_verb "Verb".
 * @param registeredOption The registered \ref arguments_option "Option".
 * @param parentVerb The \ref arguments_verb "Verb" into which the \ref arguments_option "Option" is being registered.
 * @return <code>true</code> if it was registered and not already registered into it, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerOptionW(OptionW *registeredOption, VerbW *parentVerb);

/**
 * Registers an \ref arguments_option "Option" in a given \ref arguments_verb "Verb" and all of its
 *  sub-\ref arguments_verb "Verb".
 * @param registeredOption The registered \ref arguments_option "Option".
 * @param rootVerb The \ref arguments_verb "Verb" into which the \ref arguments_option "Option" is being registered.
 * @return <code>true</code> if it was registered and not already registered in any affected \ref arguments_verb "Verb",
 *  <code>false</code> otherwise.
 *
 * \see args_registerOption
 */
DLL_EXP_ARGS bool args_registerOptionRecursivelyA(OptionA *registeredOption, VerbA *rootVerb);

/**
 * Registers an \ref arguments_option "Option" in a given \ref arguments_verb "Verb" and all of its
 *  sub-\ref arguments_verb "Verb".
 * @param registeredOption The registered \ref arguments_option "Option".
 * @param rootVerb The \ref arguments_verb "Verb" into which the \ref arguments_option "Option" is being registered.
 * @return <code>true</code> if it was registered and not already registered in any affected \ref arguments_verb "Verb",
 *  <code>false</code> otherwise.
 *
 * \see args_registerOption
 */
DLL_EXP_ARGS bool args_registerOptionRecursivelyW(OptionW *registeredOption, VerbW *rootVerb);


// Getters

/**
 * Get the parent \ref arguments_verb "Verb" of a given one.
 * @param verb The \ref arguments_verb "Verb" whose parent need to be retrieved.
 * @return The parent \ref arguments_verb "Verb" if it is present, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS VerbA *args_getParentVerbA(VerbA *verb);

/**
 * Get the parent \ref arguments_verb "Verb" of a given one.
 * @param verb The \ref arguments_verb "Verb" whose parent need to be retrieved.
 * @return The parent \ref arguments_verb "Verb" if it is present, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS VerbW *args_getParentVerbW(VerbW *verb);

/**
 * Get the \ref arguments_option "Option" with the \ref FLAG_OPTION_DEFAULT flag from a given \ref arguments_verb "Verb".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @return The default \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getDefaultOption(Verb *verb);

#define args_getDefaultOptionA(verb) ((OptionA*) args_getDefaultOption((VerbA*) verb))

#define args_getDefaultOptionW(verb) ((OptionW*) args_getDefaultOption((VerbA*) verb))

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::token "token".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredToken The desired \ref arguments_option "Option"'s <i>token</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS OptionA *args_getOptionByTokenA(VerbA *verb, char desiredToken);

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::token "token".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredToken The desired \ref arguments_option "Option"'s <i>token</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS OptionW *args_getOptionByTokenW(VerbW *verb, wchar_t desiredToken);

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::name "name".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredName The desired \ref arguments_option "Option"'s <i>name</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS OptionA *args_getOptionByNameA(VerbA *verb, char *desiredName);

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::name "name".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredName The desired \ref arguments_option "Option"'s <i>name</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS OptionW *args_getOptionByNameW(VerbW *verb, wchar_t *desiredName);

/**
 * Get a sub-\ref arguments_verb "Verb" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_verb::name "name".
 * @param parentVerb The \ref arguments_verb "Verb" whose sub-\ref arguments_verb "Verb" will be sifted through.
 * @param desiredName The desired sub-\ref arguments_verb "Verb"'s <i>name</i>.
 * @return relevant \ref arguments_verb "Verb" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS VerbA *args_getSubVerbByNameA(VerbA *parentVerb, char *desiredName);

/**
 * Get a sub-\ref arguments_verb "Verb" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_verb::name "name".
 * @param parentVerb The \ref arguments_verb "Verb" whose sub-\ref arguments_verb "Verb" will be sifted through.
 * @param desiredName The desired sub-\ref arguments_verb "Verb"'s <i>name</i>.
 * @return relevant \ref arguments_verb "Verb" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS VerbW *args_getSubVerbByNameW(VerbW *parentVerb, wchar_t *desiredName);

/**
 * Attempts to grab the default \ref arguments_option "Option" that should be used as one during the parsing process
 *  based on whether it has been used before.<br>
 * It will ignore any default \ref arguments_option "Option" that was and can only be used once.
 * @param parentVerb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getRelevantDefaultOption(Verb *parentVerb);

#define args_getRelevantDefaultOptionA(parentVerb) ((OptionA*) args_getRelevantDefaultOption((VerbA*) parentVerb))

#define args_getRelevantDefaultOptionW(parentVerb) ((OptionW*) args_getRelevantDefaultOption((VerbA*) parentVerb))


// Misc

/**
 * Adds a value to an \ref arguments_option "Option".<br>
 * This function is and should only be used by \ref args_parseArguments.
 * @param option The relevant \ref arguments_option "Option"
 * @param addedValue The value to be appended to the given \ref arguments_option "Option"'s values.
 * @return `true` if the value was added, `false` otherwise.
 */
DLL_EXP_ARGS bool args_addValueToOptionA(OptionA *option, char *addedValue);

/**
 * Adds a value to an \ref arguments_option "Option".<br>
 * This function is and should only be used by \ref args_parseArguments.
 * @param option The relevant \ref arguments_option "Option"
 * @param addedValue The value to be appended to the given \ref arguments_option "Option"'s values.
 * @return `true` if the value was added, `false` otherwise.
 */
DLL_EXP_ARGS bool args_addValueToOptionW(OptionW *option, wchar_t *addedValue);

/**
 * Checks if a \ref arguments_verb "Verb" is registered as a sub-\ref arguments_verb "Verb" in another
 *  \ref arguments_verb "Verb".
 * @param subVerb The \ref arguments_verb "Verb" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p subVerb.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isVerbAlreadyRegisteredA(VerbA *subVerb, VerbA *parentVerb);

/**
 * Checks if a \ref arguments_verb "Verb" is registered as a sub-\ref arguments_verb "Verb" in another
 *  \ref arguments_verb "Verb".
 * @param subVerb The \ref arguments_verb "Verb" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p subVerb.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isVerbAlreadyRegisteredW(VerbW *subVerb, VerbW *parentVerb);

/**
 * Checks if an \ref arguments_option "Option" is registered in the given \ref arguments_verb "Verb".
 * @param option The \ref arguments_option "Option" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p option.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isOptionAlreadyRegisteredA(OptionA *option, VerbA *parentVerb);

/**
 * Checks if an \ref arguments_option "Option" is registered in the given \ref arguments_verb "Verb".
 * @param option The \ref arguments_option "Option" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p option.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isOptionAlreadyRegisteredW(OptionW *option, VerbW *parentVerb);


// Parser

/**
 * Parses launch arguments following a given \ref arguments_verb "Verb" and all its members until the end is reached
 *  or an error occurs.<br>
 * In the event of a failure, the entire \p rootVerb should be considered as tainted and not used in any subsequent
 *  task that doesn't involve it being freed from memory.
 * @param rootVerb The root verb from which the parsing process will start.
 * @param arguments Array of strings to be parsed as the launch arguments.
 * @param startIndex The index from which parsing will take place in the given \p arguments array.
 * @param endIndex The index at which parsing will stop in the given \p arguments array.
 * @param pRelevantVerb A nullable pointer to a \ref arguments_verb "Verb" pointer used as the return value which will
 *  point to the last used verb.
 * @return An \ref EArgumentParserErrors "error code" indicating how the parsing process went and which error may
 *  have occurred.
 *
 * \see EArgumentParserErrors
 */
DLL_EXP_ARGS enum EArgumentParserErrors
args_parseArgumentsA(VerbA *rootVerb, char *arguments[], int startIndex, int endIndex, VerbA **pRelevantVerb);

/**
 * Parses launch arguments following a given \ref arguments_verb "Verb" and all its members until the end is reached
 *  or an error occurs.<br>
 * In the event of a failure, the entire \p rootVerb should be considered as tainted and not used in any subsequent
 *  task that doesn't involve it being freed from memory.
 * @param rootVerb The root verb from which the parsing process will start.
 * @param arguments Array of strings to be parsed as the launch arguments.
 * @param startIndex The index from which parsing will take place in the given \p arguments array.
 * @param endIndex The index at which parsing will stop in the given \p arguments array.
 * @param pRelevantVerb A nullable pointer to a \ref arguments_verb "Verb" pointer used as the return value which will
 *  point to the last used verb.
 * @return An \ref EArgumentParserErrors "error code" indicating how the parsing process went and which error may
 *  have occurred.
 *
 * \see EArgumentParserErrors
 */
DLL_EXP_ARGS enum EArgumentParserErrors
args_parseArgumentsW(VerbW *rootVerb, wchar_t *arguments[], int startIndex, int endIndex, VerbW **pRelevantVerb);

#endif /* !NP_ONCE_C99_GOODIES_ARGUMENTS_MAIN */
