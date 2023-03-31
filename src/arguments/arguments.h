#pragma once

#include "./errors.h"
#include "./flags.h"
#include "./structs.h"
#include "./types.h"

#include "../text.h"

#ifdef NP_ARGUMENTS_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// Macros

#define args_canOptionHaveMultipleValue(option) ((option)->flags & FLAG_OPTION_HAS_VALUE && (option)->flags & FLAG_OPTION_REPEATABLE)


// Creators

/**
 * Creates a <code>Verb</code> with no parent.
 * @param verb Name used when searching for sub-verbs, leave as <code>""</code> or <code>NULL</code> for root verbs.
 * @param description Description that is shown in the help text.
 * @return The new <code>Verb</code>, or <code>NULL</code> if an error occurred.
 */
DLL_EXPORT Verb *args_createVerb(char *verb, char *description);

DLL_EXPORT Option *args_createOption(char token, char *name, char *description, OptionFlags flags);


// Cleaners

/**
 * Free the memory allocated to a given <code>Verb</code> and all of it's members registered into it in a recursive manner.
 * @param verb The <code>Verb</code> that needs to be freed.
 */
DLL_EXPORT void args_freeVerb(Verb *verb);

DLL_EXPORT void args_freeOption(Option *option);


// Registers

/**
 * Attempts to register a <code>Verb</code> into another one as a sub-<code>Verb</code>.
 * @param registeredVerb The sub-<code>Verb</code>.
 * @param parentVerb The parent <code>Verb</code> into which the other one is registered.
 * @return <code>true</code> if it was registered, <code>false</code> otherwise.
 */
DLL_EXPORT bool args_registerVerb(Verb *registeredVerb, Verb *parentVerb);

DLL_EXPORT bool args_registerOption(Option *registeredOption, Verb *parentVerb);


// Getters

/**
 * Get the parent <code>Verb</code> of a given one.
 * @param verb The <code>Verb</code> whose parent need to be retrieved.
 * @return The parent <code>Verb</code> if it is present, <code>NULL</code> otherwise.
 */
DLL_EXPORT Verb *args_getParentVerb(Verb *verb);

/**
 * Get the <code>Option</code> with the <code>FLAG_OPTION_DEFAULT</code> flag from a given <code>Verb</code>.
 * @param verb The <code>Verb</code> whose options will be sifted through.
 * @return The default <code>Option</code> if found, <code>NULL</code> otherwise.
 */
DLL_EXPORT Option *args_getDefaultOption(Verb *verb);

/**
 * Get an <code>Option</code> from a given <code>Verb</code> by searching for it with its <i>token</i>.
 * @param verb The <code>Verb</code> whose options will be sifted through.
 * @param desiredToken The desired <code>Option</code>'s <i>token</i>.
 * @return The relevant <code>Option</code> if found, <code>NULL</code> otherwise.
 */
DLL_EXPORT Option *args_getOptionByToken(Verb *verb, char desiredToken);

/**
 * Get an <code>Option</code> from a given <code>Verb</code> by searching for it with its <i>name</i>.
 * @param verb The <code>Verb</code> whose options will be sifted through.
 * @param desiredName The desired <code>Option</code>'s <i>name</i>.
 * @return The relevant <code>Option</code> if found, <code>NULL</code> otherwise.
 */
DLL_EXPORT Option *args_getOptionByName(Verb *verb, char *desiredName);

/**
 * Get a sub-<code>Verb</code> from a given <code>Verb</code> by searching for it with its <i>name</i>.
 * @param parentVerb The <code>Verb</code> whose sub-<code>Verb</code> will be sifted through.
 * @param desiredName The desired sub-<code>Verb</code>'s <i>name</i>.
 * @return relevant <code>Verb</code> if found, <code>NULL</code> otherwise.
 */
DLL_EXPORT Verb *args_getSubVerbByName(Verb *parentVerb, char *desiredName);

/**
 * Attempts to grab the default <code>Option</code> that should be used as one during the parsing process based on
 * whether it has been used before.
 * @param parentVerb The <code>Verb</code> whose options will be sifted through.
 * @return The relevant <code>Option</code> if found, <code>NULL</code> otherwise.
 */
DLL_EXPORT Option *args_getRelevantDefaultOption(Verb *parentVerb);


// Misc

DLL_EXPORT bool args_addValueToOption(Option *option, char *addedValue);

DLL_EXPORT bool args_isVerbAlreadyRegistered(Verb *subVerb, Verb *parentVerb);

DLL_EXPORT bool args_isOptionAlreadyRegistered(Option *option, Verb *parentVerb);


// Parser

DLL_EXPORT enum EArgumentParserErrors
args_parseArguments(Verb *rootVerb, char *arguments[], int startIndex, int endIndex, Verb **pRelevantVerb);
