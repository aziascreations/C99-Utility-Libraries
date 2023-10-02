/** @file */

#pragma once

#include "./errors.h"
#include "./flags.h"
#include "./structs.h"
#include "./types.h"

#include "../text.h"

#if defined(NP_GOODIES_EXPORT_ARGUMENTS) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXP_ARGS __declspec(dllexport)
#else
#define DLL_EXP_ARGS
#endif

// Macros

#define args_canOptionHaveMultipleValue(option) ((option)->flags & FLAG_OPTION_HAS_VALUE && (option)->flags & FLAG_OPTION_REPEATABLE)

#define args_wasOptionUsed(option) (option->occurrences > 0)

// Creators

/**
 * Creates a \ref arguments_verb "Verb" with no parent.
 * @param verb Name used when searching for sub-verbs, leave as <code>""</code> or <code>NULL</code> for root verbs.
 * @param description Description shown in the help text.
 * @return The new \ref arguments_verb "Verb"'s pointer, or <code>NULL</code> if an error occurred.
 */
DLL_EXP_ARGS Verb *args_createVerb(np_args_char *verb, np_args_char *description);

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
DLL_EXP_ARGS Option *args_createOption(np_args_char token, np_args_char *name, np_args_char *description, OptionFlags flags);


// Cleaners

/**
 * Frees the memory allocated to a given \ref arguments_verb "Verb" and all of it's registered
 *  sub-\ref arguments_verb "Verb" and their \ref arguments_option "Option" in a recursive manner.
 * @param verb The \ref arguments_verb "Verb" that needs to be freed.
 */
DLL_EXP_ARGS void args_freeVerb(Verb *verb);

/**
 * Frees the memory allocated to a given \ref arguments_option "Option" if it isn't still registered in another
 *  \ref arguments_verb "Verb".
 * @param option The \ref arguments_option "Option" that needs to be freed.
 *
 * \see arguments_option::registrationCount
 */
DLL_EXP_ARGS void args_freeOption(Option *option);


// Registers

/**
 * Registers a \ref arguments_verb "Verb" into another one as a sub-\ref arguments_verb "Verb".
 * @param registeredVerb The sub-\ref arguments_verb "Verb".
 * @param parentVerb The parent \ref arguments_verb "Verb" into which the other one is registered.
 * @return <code>true</code> if it was registered, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerVerb(Verb *registeredVerb, Verb *parentVerb);

/**
 * Registers an \ref arguments_option "Option" in a given \ref arguments_verb "Verb".
 * @param registeredOption The registered \ref arguments_option "Option".
 * @param parentVerb The \ref arguments_verb "Verb" into which the \ref arguments_option "Option" is being registered.
 * @return <code>true</code> if it was registered and not already registered into it, <code>false</code> otherwise.
 */
DLL_EXP_ARGS bool args_registerOption(Option *registeredOption, Verb *parentVerb);

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
DLL_EXP_ARGS bool args_registerOptionRecursively(Option *registeredOption, Verb *rootVerb);


// Getters

/**
 * Get the parent \ref arguments_verb "Verb" of a given one.
 * @param verb The \ref arguments_verb "Verb" whose parent need to be retrieved.
 * @return The parent \ref arguments_verb "Verb" if it is present, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Verb *args_getParentVerb(Verb *verb);

/**
 * Get the \ref arguments_option "Option" with the \ref FLAG_OPTION_DEFAULT flag from a given \ref arguments_verb "Verb".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @return The default \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getDefaultOption(Verb *verb);

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::token "token".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredToken The desired \ref arguments_option "Option"'s <i>token</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getOptionByToken(Verb *verb, np_args_char desiredToken);

/**
 * Get an \ref arguments_option "Option" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_option::name "name".
 * @param verb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @param desiredName The desired \ref arguments_option "Option"'s <i>name</i>.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getOptionByName(Verb *verb, np_args_char *desiredName);

/**
 * Get a sub-\ref arguments_verb "Verb" from a given \ref arguments_verb "Verb" by searching for it with its
 *  \ref arguments_verb::name "name".
 * @param parentVerb The \ref arguments_verb "Verb" whose sub-\ref arguments_verb "Verb" will be sifted through.
 * @param desiredName The desired sub-\ref arguments_verb "Verb"'s <i>name</i>.
 * @return relevant \ref arguments_verb "Verb" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Verb *args_getSubVerbByName(Verb *parentVerb, np_args_char *desiredName);

/**
 * Attempts to grab the default \ref arguments_option "Option" that should be used as one during the parsing process
 *  based on whether it has been used before.<br>
 * It will ignore any default \ref arguments_option "Option" that was and can only be used once.
 * @param parentVerb The \ref arguments_verb "Verb" whose options will be sifted through.
 * @return The relevant \ref arguments_option "Option" if found, <code>NULL</code> otherwise.
 */
DLL_EXP_ARGS Option *args_getRelevantDefaultOption(Verb *parentVerb);


// Misc

/**
 * Adds a value to an \ref arguments_option "Option".<br>
 * This function is and should only be used by \ref args_parseArguments.
 * @param option The relevant \ref arguments_option "Option"
 * @param addedValue The value to be appended to the given \ref arguments_option "Option"'s values.
 * @return `true` if the value was added, `false` otherwise.
 */
DLL_EXP_ARGS bool args_addValueToOption(Option *option, np_args_char *addedValue);

/**
 * Checks if a \ref arguments_verb "Verb" is registered as a sub-\ref arguments_verb "Verb" in another
 *  \ref arguments_verb "Verb".
 * @param subVerb The \ref arguments_verb "Verb" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p subVerb.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isVerbAlreadyRegistered(Verb *subVerb, Verb *parentVerb);

/**
 * Checks if an \ref arguments_option "Option" is registered in the given \ref arguments_verb "Verb".
 * @param option The \ref arguments_option "Option" whose presence in \p parentVerb will be checked.
 * @param parentVerb The \ref arguments_verb "Verb" that may contain \p option.
 * @return `true` if it is registered into it, `false` otherwise.
 */
DLL_EXP_ARGS bool args_isOptionAlreadyRegistered(Option *option, Verb *parentVerb);


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
args_parseArguments(Verb *rootVerb, np_args_char *arguments[], int startIndex, int endIndex, Verb **pRelevantVerb);
