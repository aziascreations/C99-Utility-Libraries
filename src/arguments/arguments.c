/** @file */

#include "arguments.h"

#include "../debug.h"

/** @defgroup arguments Arguments parser
 *
 * TODO: Simple module description
 *
 * <b>Warning:</b><br>
 * Any reference to a *sub-verb* actually refers to a regular \ref arguments_verb "Verb" which can be considered as the
 *  another verb's children.
 *
 * Any reference to `np_args_char` can be the equivalent of `char` or `wchar_t` depending on 2 compiler constants.<br>
 * These constants, `NP_WIN32` and `NP_ARGS_WCHAR`, if both used, will make all functions and structures in this module
 *  use `wchar_t` strings instead of `char` ones.<br>
 * This features allows you to easily handle unicode characters and emojis in launch arguments on Windows platforms.
 *
 * These macro-ed types and functions are defined in \ref arguments/macros.h.<br>
 * This header also defines a bunch of macros for string-related operations done in this module.<br>
 * They shouldn't be used outside of it !
 *
 * If you want an example of this feature on a Windows app, you should check
 *  [aziascreations/C99-Win32-Wifi-Utility](https://github.com/aziascreations/C99-Win32-Wifi-Utility) on GitHub.
 *
 * @{
 */

// Creators

VerbA *args_createVerbA(char *verb, char *description) {
	VerbA *newVerb = malloc(sizeof(VerbA));
	
	// Quickly "fixing" NULL parameters for later.
	if(verb == NULL) {
		verb = "";
	}
	
	if(description == NULL) {
		description = "";
	}
	
	if(newVerb != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newVerb->name = text_copyA(verb);
		newVerb->description = text_copyA(description);
		newVerb->verbs = dllist_create();
		newVerb->options = dllist_create();
		newVerb->parentVerb = NULL;
		newVerb->wasUsed = false;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newVerb->name == NULL || newVerb->description == NULL || newVerb->verbs == NULL ||
		   newVerb->options == NULL) {
			args_freeVerbA(newVerb);
			newVerb = NULL;
		}
	}
	
	return newVerb;
}


VerbW *args_createVerbW(wchar_t *verb, wchar_t *description) {
	VerbW *newVerb = malloc(sizeof(VerbW));
	
	// Quickly "fixing" NULL parameters for later.
	if(verb == NULL) {
		verb = L"";
	}
	
	if(description == NULL) {
		description = L"";
	}
	
	if(newVerb != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newVerb->name = text_copyW(verb);
		newVerb->description = text_copyW(description);
		newVerb->verbs = dllist_create();
		newVerb->options = dllist_create();
		newVerb->parentVerb = NULL;
		newVerb->wasUsed = false;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newVerb->name == NULL || newVerb->description == NULL || newVerb->verbs == NULL ||
		   newVerb->options == NULL) {
			args_freeVerbW(newVerb);
			newVerb = NULL;
		}
	}
	
	return newVerb;
}

OptionA *args_createOptionA(char token, char *name, char *description, OptionFlags flags) {
	// Preliminary checks and parameter "fixing".
	if(token == '\0' && name == NULL) {
		return NULL;
	}
	
	if(name == NULL) {
		name = "";
	}
	
	if(description == NULL) {
		description = "";
	}
	
	// Doing the actual creation.
	OptionA *newOption = malloc(sizeof(OptionA));
	
	if(newOption != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newOption->token = token;
		newOption->name = text_copyA(name);
		newOption->description = text_copyA(description);
		newOption->flags = flags;
		newOption->arguments = dllist_create();
		newOption->occurrences = 0;
		newOption->registrationCount = 0;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newOption->name == NULL || newOption->description == NULL || newOption->arguments == NULL) {
			args_freeOptionA(newOption);
			newOption = NULL;
		}
	}
	
	return newOption;
}

OptionW *args_createOptionW(wchar_t token, wchar_t *name, wchar_t *description, OptionFlags flags) {
	// Preliminary checks and parameter "fixing".
	if(token == '\0' && name == NULL) {
		return NULL;
	}
	
	if(name == NULL) {
		name = L"";
	}
	
	if(description == NULL) {
		description = L"";
	}
	
	// Doing the actual creation.
	OptionW *newOption = malloc(sizeof(OptionW));
	
	if(newOption != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newOption->token = token;
		newOption->name = text_copyW(name);
		newOption->description = text_copyW(description);
		newOption->flags = flags;
		newOption->arguments = dllist_create();
		newOption->occurrences = 0;
		newOption->registrationCount = 0;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newOption->name == NULL || newOption->description == NULL || newOption->arguments == NULL) {
			args_freeOptionW(newOption);
			newOption = NULL;
		}
	}
	
	return newOption;
}


// Cleaners

void args_freeVerb(Verb *verb) {
	if(verb != NULL) {
		//np_args_trace_println("Starting to free verb '%s' @0x%p", verb->name, verb);
		
		// Safely freeing lists.
		// The subsequent required "args_freeVerb" and "args_freeOption" calls will be made automatically.
		// FIXME: HOW ?!?, As per given from where the fuck ?!?
		if(verb->verbs != NULL) {
			dllist_free(verb->verbs, &free, NULL);
		}
		if(verb->options != NULL) {
			dllist_free(verb->options, &free, NULL);
		}
		
		// Safely freeing strings.
		if(verb->name != NULL) {
			free(verb->name);
		}
		if(verb->description != NULL) {
			free(verb->description);
		}
		
		// Freeing root structure.
		free(verb);
	}
}

// FIXME: Check if the args_freeOptionA function is properly called from the "args_freeVerbA" one !!!
// Big ass memory leak incoming if not
void args_freeOption(Option *option) {
	if(option != NULL) {
		//np_args_trace_println("Starting to free option '0d%i':'%s' @0x%p", option->token, option->name, option);
		
		// We first decrement the `registrationCount` variable and check if it is at `0`.
		// This done in order to allow the same option to be used in multiple verbs easily and transparently.
		option->registrationCount--;
		
		// Checking if it is still registered in a verb that wasn't freed.
		// Can be a negative number if the option was never registered !
		if(option->registrationCount > 0) {
			//np_args_trace_println("Skipped the freeing process, still registered in another verb !");
			return;
		}
		
		// Safely freeing lists.
		// The subsequent required "free" calls will be made automatically.
		if(option->arguments != NULL) {
			dllist_free(option->arguments, &free, NULL);
		}
		
		// Safely freeing strings.
		// These should never be NULL, but it doesn't hurt to check twice.
		if(option->name != NULL) {
			free(option->name);
		}
		if(option->description != NULL) {
			free(option->description);
		}
		
		// Freeing root structure
		free(option);
	}
}


// Registers

bool args_registerVerbA(VerbA *registeredVerb, VerbA *parentVerb) {
	if(registeredVerb == NULL || parentVerb == NULL) {
		error_println("Unable to register verb: One of them is null !  (parent: @0x%p, sub: @0x%p)", parentVerb,
					  registeredVerb);
		return false;
	}
	
	if(registeredVerb->name == NULL || text_strlenA(registeredVerb->name) == 0 || text_isEmptyA(registeredVerb->name)) {
		error_println("Unable to register verb: The sub's name is NULL or empty !  (name: @0x%p)",
					  registeredVerb->name);
		return false;
	}
	
	if(args_isVerbAlreadyRegisteredA(registeredVerb, parentVerb)) {
		error_println("Unable to register verb: A similar verb is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->verbs, registeredVerb, NULL)) {
		error_println("Unable to register verb: Internal DLList error");
		return false;
	}
	registeredVerb->parentVerb = parentVerb;
	
	return true;
}

bool args_registerVerbW(VerbW *registeredVerb, VerbW *parentVerb) {
	if(registeredVerb == NULL || parentVerb == NULL) {
		error_println("Unable to register verb: One of them is null !  (parent: @0x%p, sub: @0x%p)", parentVerb,
					  registeredVerb);
		return false;
	}
	
	if(registeredVerb->name == NULL || text_strlenW(registeredVerb->name) == 0 || text_isEmptyW(registeredVerb->name)) {
		error_println("Unable to register verb: The sub's name is NULL or empty !  (name: @0x%p)",
					  registeredVerb->name);
		return false;
	}
	
	if(args_isVerbAlreadyRegisteredW(registeredVerb, parentVerb)) {
		error_println("Unable to register verb: A similar verb is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->verbs, registeredVerb, NULL)) {
		error_println("Unable to register verb: Internal DLList error");
		return false;
	}
	registeredVerb->parentVerb = parentVerb;
	
	return true;
}

bool args_registerOptionA(OptionA *registeredOption, VerbA *parentVerb) {
	if(registeredOption == NULL || parentVerb == NULL) {
		error_println("Unable to register option: One of the parameter is null !  (parent: @0x%p, option: @0x%p)",
							  parentVerb, registeredOption);
		return false;
	}
	
	if(args_isOptionAlreadyRegisteredA(registeredOption, parentVerb)) {
		error_println("Unable to register option: A similar option is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->options, registeredOption, NULL)) {
		error_println("Unable to register option: Internal DLList error");
		return false;
	}
	registeredOption->registrationCount++;
	
	return true;
}

bool args_registerOptionW(OptionW *registeredOption, VerbW *parentVerb) {
	if(registeredOption == NULL || parentVerb == NULL) {
		error_println("Unable to register option: One of the parameter is null !  (parent: @0x%p, option: @0x%p)",
					  parentVerb, registeredOption);
		return false;
	}
	
	if(args_isOptionAlreadyRegisteredW(registeredOption, parentVerb)) {
		error_println("Unable to register option: A similar option is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->options, registeredOption, NULL)) {
		error_println("Unable to register option: Internal DLList error");
		return false;
	}
	registeredOption->registrationCount++;
	
	return true;
}

bool args_registerOptionRecursivelyA(OptionA *registeredOption, VerbA *rootVerb) {
	if(registeredOption == NULL && rootVerb == NULL) {
		return false;
	}
	
	args_registerOptionA(registeredOption, rootVerb);
	
	VerbA *currentSubVerb = dllist_selectFirstData(rootVerb->verbs);
	while(currentSubVerb != NULL) {
		args_registerOptionRecursivelyA(registeredOption, currentSubVerb);
		currentSubVerb = dllist_selectNextData(rootVerb->verbs);
	}
	
	return true;
}

bool args_registerOptionRecursivelyW(OptionW *registeredOption, VerbW *rootVerb) {
	if(registeredOption == NULL && rootVerb == NULL) {
		return false;
	}
	
	args_registerOptionW(registeredOption, rootVerb);
	
	VerbW *currentSubVerb = dllist_selectFirstData(rootVerb->verbs);
	while(currentSubVerb != NULL) {
		args_registerOptionRecursivelyW(registeredOption, currentSubVerb);
		currentSubVerb = dllist_selectNextData(rootVerb->verbs);
	}
	
	return true;
}


// Getters

VerbA *args_getParentVerbA(VerbA *verb) {
	if(verb != NULL) {
		return verb->parentVerb;
	}
	
	return NULL;
}

VerbW *args_getParentVerbW(VerbW *verb) {
	if(verb != NULL) {
		return verb->parentVerb;
	}
	
	return NULL;
}

Option *args_getDefaultOption(Verb *verb) {
	if(verb != NULL) {
		Option *currentOption = (Option *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			if(currentOption->flags & FLAG_OPTION_DEFAULT) {
				return currentOption;
			}
			currentOption = (Option *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

OptionA *args_getOptionByTokenA(VerbA *verb, char desiredToken) {
	if(verb != NULL && desiredToken != '\0') {
		OptionA *currentOption = (OptionA *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			if(currentOption->token == desiredToken) {
				return currentOption;
			}
			currentOption = (OptionA *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

OptionW *args_getOptionByTokenW(VerbW *verb, wchar_t desiredToken) {
	if(verb != NULL && desiredToken != '\0') {
		OptionW *currentOption = (OptionW *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			if(currentOption->token == desiredToken) {
				return currentOption;
			}
			currentOption = (OptionW *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

OptionA *args_getOptionByNameA(VerbA *verb, char *desiredName) {
	if(verb != NULL && desiredName != NULL) {
		trace_println("Attempting to find the '%s' option in the '%s' verb...", desiredName, verb->name);
		
		OptionA *currentOption = (OptionA *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			trace_println("Checking the '%i':'%s' registered option @0x%p ...", currentOption->token,
						  currentOption->name, currentOption);
			
			if(text_strcmpA(currentOption->name, desiredName) == 0) {
				return currentOption;
			}
			
			currentOption = (OptionA *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

OptionW *args_getOptionByNameW(VerbW *verb, wchar_t *desiredName) {
	if(verb != NULL && desiredName != NULL) {
		trace_println("Attempting to find the '%s' option in the '%s' verb...", desiredName, verb->name);
		
		OptionW *currentOption = (OptionW *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			trace_println("Checking the '%i':'%s' registered option @0x%p ...", currentOption->token,
						  currentOption->name, currentOption);
			
			if(text_strcmpW(currentOption->name, desiredName) == 0) {
				return currentOption;
			}
			
			currentOption = (OptionW *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

VerbA *args_getSubVerbByNameA(VerbA *parentVerb, char *desiredName) {
	if(parentVerb != NULL && desiredName != NULL) {
		VerbA *currentSubVerb = (VerbA *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentSubVerb != NULL) {
			if(text_strcmpA(currentSubVerb->name, desiredName) == 0) {
				return currentSubVerb;
			}
			currentSubVerb = (VerbA *) dllist_selectNextData(parentVerb->verbs);
		}
	}
	
	return NULL;
}

VerbW *args_getSubVerbByNameW(VerbW *parentVerb, wchar_t *desiredName) {
	if(parentVerb != NULL && desiredName != NULL) {
		VerbW *currentSubVerb = (VerbW *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentSubVerb != NULL) {
			if(text_strcmpW(currentSubVerb->name, desiredName) == 0) {
				return currentSubVerb;
			}
			currentSubVerb = (VerbW *) dllist_selectNextData(parentVerb->verbs);
		}
	}
	
	return NULL;
}

Option *args_getRelevantDefaultOption(Verb *parentVerb) {
	if(parentVerb != NULL) {
		Option *currentOption = (Option *) dllist_selectFirstData(parentVerb->options);
		
		while(currentOption != NULL) {
			if(currentOption->flags & FLAG_OPTION_DEFAULT) {
				if(currentOption->flags & FLAG_OPTION_REPEATABLE) {
					return currentOption;
				}
				
				if(currentOption->flags & FLAG_OPTION_HAS_VALUE && currentOption->occurrences == 0) {
					return currentOption;
				}
			}
			
			currentOption = (Option *) dllist_selectNextData(parentVerb->options);
		}
	}
	
	return NULL;
}


// Misc

bool args_addValueToOptionA(OptionA *option, char *addedValue) {
	if(option == NULL || addedValue == NULL) {
		error_println("Unable to add value to option, one of them is NULL !  (option: @0x%p, str: @0x%p)",
					  option, addedValue);
		return false;
	}
	
	char *addedValueCopy = text_copyA(addedValue);
	if(addedValueCopy == NULL) {
		error_println("Unable to copy the current argument !");
		return false;
	}
	
	if(!dllist_append(option->arguments, addedValueCopy, NULL)) {
		error_println("Unable to insert the current argument into the option !");
		free(addedValueCopy);
		return false;
	}
	
	return true;
}

bool args_addValueToOptionW(OptionW *option, wchar_t *addedValue) {
	if(option == NULL || addedValue == NULL) {
		error_println("Unable to add value to option, one of them is NULL !  (option: @0x%p, str: @0x%p)",
					  option, addedValue);
		return false;
	}
	
	wchar_t *addedValueCopy = text_copyW(addedValue);
	if(addedValueCopy == NULL) {
		error_println("Unable to copy the current argument !");
		return false;
	}
	
	if(!dllist_append(option->arguments, addedValueCopy, NULL)) {
		error_println("Unable to insert the current argument into the option !");
		free(addedValueCopy);
		return false;
	}
	
	return true;
}

bool args_isVerbAlreadyRegisteredA(VerbA *subVerb, VerbA *parentVerb) {
	if(subVerb != NULL && parentVerb != NULL) {
		VerbA *currentRegisteredSubVerb = (VerbA *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentRegisteredSubVerb != NULL) {
			// Checking the pointer itself
			if(subVerb == currentRegisteredSubVerb) {
				return true;
			}
			
			// Checking the name itself if not empty in either.
			if(!text_isEmptyA(subVerb->name) && !text_isEmptyA(currentRegisteredSubVerb->name) &&
			   text_areStringsEqualA(subVerb->name, currentRegisteredSubVerb->name)) {
				return true;
			}
			
			currentRegisteredSubVerb = (VerbA *) dllist_selectNextData(parentVerb->verbs);
		}
	}
	
	return false;
}

bool args_isVerbAlreadyRegisteredW(VerbW *subVerb, VerbW *parentVerb) {
	if(subVerb != NULL && parentVerb != NULL) {
		VerbW *currentRegisteredSubVerb = (VerbW *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentRegisteredSubVerb != NULL) {
			// Checking the pointer itself
			if(subVerb == currentRegisteredSubVerb) {
				return true;
			}
			
			// Checking the name itself if not empty in either.
			if(!text_isEmptyW(subVerb->name) && !text_isEmptyW(currentRegisteredSubVerb->name) &&
			   text_areStringsEqualW(subVerb->name, currentRegisteredSubVerb->name)) {
				return true;
			}
			
			currentRegisteredSubVerb = (VerbW *) dllist_selectNextData(parentVerb->verbs);
		}
	}
	
	return false;
}

bool args_isOptionAlreadyRegisteredA(OptionA *option, VerbA *parentVerb) {
	if(option != NULL && parentVerb != NULL) {
		OptionA *currentRegisteredOption = (OptionA *) dllist_selectFirstData(parentVerb->options);
		
		while(currentRegisteredOption != NULL) {
			// Checking the pointer itself
			if(option == currentRegisteredOption) {
				return true;
			}
			
			// Checking the token if defined in both.
			if(option->token != '\0' && currentRegisteredOption->token != '\0' &&
			   option->token == currentRegisteredOption->token) {
				return true;
			}
			
			// Checking the name itself if not empty in either.
			if(!text_isEmptyA(option->name) && !text_isEmptyA(currentRegisteredOption->name) &&
			   text_areStringsEqualA(option->name, currentRegisteredOption->name)) {
				return true;
			}
			
			currentRegisteredOption = (OptionA *) dllist_selectNextData(parentVerb->options);
		}
	}
	
	return false;
}

bool args_isOptionAlreadyRegisteredW(OptionW *option, VerbW *parentVerb) {
	if(option != NULL && parentVerb != NULL) {
		OptionW *currentRegisteredOption = (OptionW *) dllist_selectFirstData(parentVerb->options);
		
		while(currentRegisteredOption != NULL) {
			// Checking the pointer itself
			if(option == currentRegisteredOption) {
				return true;
			}
			
			// Checking the token if defined in both.
			if(option->token != '\0' && currentRegisteredOption->token != '\0' &&
			   option->token == currentRegisteredOption->token) {
				return true;
			}
			
			// Checking the name itself if not empty in either.
			if(!text_isEmptyW(option->name) && !text_isEmptyW(currentRegisteredOption->name) &&
			   text_areStringsEqualW(option->name, currentRegisteredOption->name)) {
				return true;
			}
			
			currentRegisteredOption = (OptionW *) dllist_selectNextData(parentVerb->options);
		}
	}
	
	return false;
}


// Parser

enum EArgumentParserErrors args_parseArgumentsA(VerbA *rootVerb, char *arguments[], int startIndex, int endIndex,
											    VerbA **pRelevantVerb) {
	VerbA *currentVerb = rootVerb;
	
	// Maybe assigned in multiple places to keep track of the option to which values belong.
	OptionA *relevantOption = NULL;
	
	// TODO: Check if the flag exists and/or should exist !
	// Set to true once the "--" token is encountered, or when an option with the ??? flag is encountered.
	bool hasReachedEndOfOptions = false;
	
	// Set to true once the first option is found.
	bool hasFinishedParsingVerbs = false;
	
	int iArg = startIndex;
	
	while(iArg < endIndex) {
		// Count of how many launch parameters were parsed during this iteration of the loop.
		// This count should only change when encountering options with one or more value(s).
		int processedArgumentsCount = 1;
		
		// Used to simplify some early checks.
		size_t currentArgumentSize = text_strlenA(arguments[iArg]);
		
		// Checking for the 'StopsParsing' flags and setting 'relevantOption' back to NULL if not encountered.
		if(relevantOption != NULL) {
			if(relevantOption->flags & FLAG_OPTION_STOPS_PARSING) {
				// FIXME: Return something.
				//return currentVerb;
			}
			relevantOption = NULL;
		}
		
		// Making sure the root verb is marked as having been used.
		currentVerb->wasUsed = true;
		
		trace_println("Parsing: '%s'", arguments[iArg]);
		
		if(!hasReachedEndOfOptions && text_startsWithA(arguments[iArg], "--")) {
			trace_println(" > Long option or end of parameters");
			
			bool skipAllowVerbAfterOptionCheck = false;
			
			if(text_strlenA(arguments[iArg]) == 2) {
				trace_println(" > End of options symbol.");
				
				if(hasReachedEndOfOptions) {
					error_println("Dual end of options given as '--' !");
					return ERROR_ARGUMENTS_DUAL_END_OF_OPTIONS;
				}
				
				hasReachedEndOfOptions = true;
				skipAllowVerbAfterOptionCheck = true;
			} else if(hasReachedEndOfOptions) {
				trace_println(" > Default option's value that starts with '--'");
				
				relevantOption = args_getRelevantDefaultOptionA(currentVerb);
				
				if(relevantOption == NULL) {
					error_println("No relevant default option found in the '%s' verb !", currentVerb->name);
					return ERROR_ARGUMENTS_NO_DEFAULT_FOUND;
				}
				
				relevantOption->occurrences++;
				if(!args_addValueToOptionA(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
			} else {
				trace_println(" > Generic option by '--<name>'");
				
				// Use arguments[iArg]+2 instead of arguments[iArg][2..]
				
				relevantOption = args_getOptionByNameA(currentVerb, arguments[iArg] + 2);
				if(relevantOption == NULL) {
					error_println("Unable to find the '%s' option !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The option '%s' was used more than once !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				if(relevantOption->flags & FLAG_OPTION_HAS_VALUE) {
					if(!args_canOptionHaveMultipleValueA(relevantOption) && relevantOption->occurrences > 1) {
						// Most likely is redundant as both of these checks are done earlier in some way.
						error_println("The option '%s' can only have 1 argument !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_THIS_SHOULD_NOT_TRIGGER;
					}
					
					if(endIndex <= iArg + 1) {
						error_println("Unable to get a value for '%s', no arguments left !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
					}
					
					if(!args_addValueToOptionA(relevantOption, arguments[iArg + 1])) {
						return ERROR_ARGUMENTS_INSERTION_FAILURE;
					}
					
					processedArgumentsCount++;
				}
			}
			
			if(skipAllowVerbAfterOptionCheck || !(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
				trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
				hasFinishedParsingVerbs = true;
			}
		} else if(!hasReachedEndOfOptions && text_startsWithA(arguments[iArg], "-")) {
			trace_println(" > Short option(s)");
			
			for(int iChar = 1; iChar < text_strlenA(arguments[iArg]); iChar++) {
				trace_println(" > Doing '%c'", arguments[iArg][iChar]);
				
				relevantOption = args_getOptionByTokenA(currentVerb, arguments[iArg][iChar]);
				
				if(relevantOption == NULL) {
					error_println("Unable to find the '%c' short option !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The short option '%c' as used more than once !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				if(!(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
					trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
					hasFinishedParsingVerbs = true;
				}
				
				if(!(relevantOption->flags & FLAG_OPTION_HAS_VALUE)) {
					continue;
				}
				
				if(iChar + 1 < text_strlenA(arguments[iArg])) {
					error_println(
							"\"The short option '%c' was given before the end of the argument while requiring a value !",
							arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_OPTION_HAS_VALUE_AND_MORE_SHORTS;
				}
				
				if(endIndex <= iArg + 1) {
					error_println("Unable to get a value for '%c', no arguments left !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
				}
				
				if(!args_addValueToOptionA(relevantOption, arguments[iArg + 1])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
				processedArgumentsCount++;
			}
		} else {
			trace_println(" > Verb or default argument's value");
			
			// Remark:
			// This block is a flattened version of the C# library's one.
			// It may be hard to wrap you head around the conditions since they sort of "cross" into each other.
			// This was done in an effort to avoid duplicating code for no good reason above intuitive understanding.
			// Please refer to the code at the following URL for the original and more readable version:
			// * https://github.com/aziascreations/DotNet-Arguments/blob/master/NibblePoker.Library.Arguments/ArgumentsParser.cs#L137
			
			VerbA *desiredVerb = NULL;
			
			if(!hasFinishedParsingVerbs) {
				desiredVerb = args_getSubVerbByNameA(currentVerb, arguments[iArg]);
			}
			
			// Only grabbing the default option if we have no new relevant verb
			if(desiredVerb == NULL) {
				relevantOption = args_getRelevantDefaultOptionA(currentVerb);
				
				if(relevantOption == NULL) {
					error_println("No relevant default option found in the '%s' verb !", currentVerb->name);
					return ERROR_ARGUMENTS_NO_DEFAULT_FOUND;
				}
				
				trace_println(" > Grabbed the default option and will be adding a value to it.");
			} else {
				// Will not trigger the next `if` condition !
				desiredVerb->wasUsed = true;
				currentVerb = desiredVerb;
			}
			
			// Can be set to NULL in the condition above or at the start of the loop.
			if(relevantOption != NULL) {
				// Not checking for flags and max value count since "args_getRelevantDefaultOption" takes care of it !
				// Remark: We simply won't receive it and will just have NULL as if we had none !
				
				relevantOption->occurrences++;
				
				if(!args_addValueToOptionA(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
				
				if(!(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
					trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
					hasFinishedParsingVerbs = true;
				}
			}
		}
		
		iArg += processedArgumentsCount;
	}
	
	// Checking the "Required" flag recursively from the final verb back to the root verb.
	VerbA* tempReqVerb = currentVerb;
	while(tempReqVerb != NULL) {
		OptionA* tempReqOption = dllist_selectFirstData(tempReqVerb->options);
		
		while(tempReqOption != NULL) {
			if(tempReqOption->flags & FLAG_OPTION_REQUIRED && tempReqOption->occurrences < 1) {
				error_println("The '%c':'%s' option was required but not given !",
							  tempReqOption->token, tempReqOption->name);
				return ERROR_ARGUMENTS_REQUIRED_OPTION_UNUSED;
			}
			tempReqOption = (OptionA *) dllist_selectNextData(tempReqVerb->options);
		}
		
		tempReqVerb = currentVerb->parentVerb;
	}
	
	// Returning the last used verb if possible.
	if(pRelevantVerb != NULL) {
		*pRelevantVerb = currentVerb;
	}
	
	return ERROR_ARGUMENTS_NONE;
}

enum EArgumentParserErrors args_parseArgumentsW(VerbW *rootVerb, wchar_t *arguments[], int startIndex, int endIndex,
											    VerbW **pRelevantVerb) {
	VerbW *currentVerb = rootVerb;
	
	// Maybe assigned in multiple places to keep track of the option to which values belong.
	OptionW *relevantOption = NULL;
	
	// TODO: Check if the flag exists and/or should exist !
	// Set to true once the "--" token is encountered, or when an option with the ??? flag is encountered.
	bool hasReachedEndOfOptions = false;
	
	// Set to true once the first option is found.
	bool hasFinishedParsingVerbs = false;
	
	int iArg = startIndex;
	
	while(iArg < endIndex) {
		// Count of how many launch parameters were parsed during this iteration of the loop.
		// This count should only change when encountering options with one or more value(s).
		int processedArgumentsCount = 1;
		
		// Used to simplify some early checks.
		size_t currentArgumentSize = text_strlenW(arguments[iArg]);
		
		// Checking for the 'StopsParsing' flags and setting 'relevantOption' back to NULL if not encountered.
		if(relevantOption != NULL) {
			if(relevantOption->flags & FLAG_OPTION_STOPS_PARSING) {
				// FIXME: Return something.
				//return currentVerb;
			}
			relevantOption = NULL;
		}
		
		// Making sure the root verb is marked as having been used.
		currentVerb->wasUsed = true;
		
		trace_println("Parsing: '%s'", arguments[iArg]);
		
		if(!hasReachedEndOfOptions && text_startsWithW(arguments[iArg], L"--")) {
			trace_println(" > Long option or end of parameters");
			
			bool skipAllowVerbAfterOptionCheck = false;
			
			if(text_strlenW(arguments[iArg]) == 2) {
				trace_println(" > End of options symbol.");
				
				if(hasReachedEndOfOptions) {
					error_println("Dual end of options given as '--' !");
					return ERROR_ARGUMENTS_DUAL_END_OF_OPTIONS;
				}
				
				hasReachedEndOfOptions = true;
				skipAllowVerbAfterOptionCheck = true;
			} else if(hasReachedEndOfOptions) {
				trace_println(" > Default option's value that starts with '--'");
				
				relevantOption = args_getRelevantDefaultOptionW(currentVerb);
				
				if(relevantOption == NULL) {
					error_println("No relevant default option found in the '%s' verb !", currentVerb->name);
					return ERROR_ARGUMENTS_NO_DEFAULT_FOUND;
				}
				
				relevantOption->occurrences++;
				if(!args_addValueToOptionW(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
			} else {
				trace_println(" > Generic option by '--<name>'");
				
				// Use arguments[iArg]+2 instead of arguments[iArg][2..]
				
				relevantOption = args_getOptionByNameW(currentVerb, arguments[iArg] + 2);
				if(relevantOption == NULL) {
					error_println("Unable to find the '%s' option !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The option '%s' was used more than once !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				if(relevantOption->flags & FLAG_OPTION_HAS_VALUE) {
					if(!args_canOptionHaveMultipleValueW(relevantOption) && relevantOption->occurrences > 1) {
						// Most likely is redundant as both of these checks are done earlier in some way.
						error_println("The option '%s' can only have 1 argument !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_THIS_SHOULD_NOT_TRIGGER;
					}
					
					if(endIndex <= iArg + 1) {
						error_println("Unable to get a value for '%s', no arguments left !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
					}
					
					if(!args_addValueToOptionW(relevantOption, arguments[iArg + 1])) {
						return ERROR_ARGUMENTS_INSERTION_FAILURE;
					}
					
					processedArgumentsCount++;
				}
			}
			
			if(skipAllowVerbAfterOptionCheck || !(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
				trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
				hasFinishedParsingVerbs = true;
			}
		} else if(!hasReachedEndOfOptions && text_startsWithW(arguments[iArg], L"-")) {
			trace_println(" > Short option(s)");
			
			for(int iChar = 1; iChar < text_strlenW(arguments[iArg]); iChar++) {
				trace_println(" > Doing '%c'", arguments[iArg][iChar]);
				
				relevantOption = args_getOptionByTokenW(currentVerb, arguments[iArg][iChar]);
				
				if(relevantOption == NULL) {
					error_println("Unable to find the '%c' short option !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The short option '%c' as used more than once !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				if(!(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
					trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
					hasFinishedParsingVerbs = true;
				}
				
				if(!(relevantOption->flags & FLAG_OPTION_HAS_VALUE)) {
					continue;
				}
				
				if(iChar + 1 < text_strlenW(arguments[iArg])) {
					error_println(
							"\"The short option '%c' was given before the end of the argument while requiring a value !",
							arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_OPTION_HAS_VALUE_AND_MORE_SHORTS;
				}
				
				if(endIndex <= iArg + 1) {
					error_println("Unable to get a value for '%c', no arguments left !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
				}
				
				if(!args_addValueToOptionW(relevantOption, arguments[iArg + 1])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
				processedArgumentsCount++;
			}
		} else {
			trace_println(" > Verb or default argument's value");
			
			// Remark:
			// This block is a flattened version of the C# library's one.
			// It may be hard to wrap you head around the conditions since they sort of "cross" into each other.
			// This was done in an effort to avoid duplicating code for no good reason above intuitive understanding.
			// Please refer to the code at the following URL for the original and more readable version:
			// * https://github.com/aziascreations/DotNet-Arguments/blob/master/NibblePoker.Library.Arguments/ArgumentsParser.cs#L137
			
			VerbW *desiredVerb = NULL;
			
			if(!hasFinishedParsingVerbs) {
				desiredVerb = args_getSubVerbByNameW(currentVerb, arguments[iArg]);
			}
			
			// Only grabbing the default option if we have no new relevant verb
			if(desiredVerb == NULL) {
				relevantOption = args_getRelevantDefaultOptionW(currentVerb);
				
				if(relevantOption == NULL) {
					error_println("No relevant default option found in the '%s' verb !", currentVerb->name);
					return ERROR_ARGUMENTS_NO_DEFAULT_FOUND;
				}
				
				trace_println(" > Grabbed the default option and will be adding a value to it.");
			} else {
				// Will not trigger the next `if` condition !
				desiredVerb->wasUsed = true;
				currentVerb = desiredVerb;
			}
			
			// Can be set to NULL in the condition above or at the start of the loop.
			if(relevantOption != NULL) {
				// Not checking for flags and max value count since "args_getRelevantDefaultOption" takes care of it !
				// Remark: We simply won't receive it and will just have NULL as if we had none !
				
				relevantOption->occurrences++;
				
				if(!args_addValueToOptionW(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
				
				if(!(relevantOption->flags & FLAG_OPTION_ALLOW_VERBS_AFTER)) {
					trace_println("Setting internal 'hasFinishedParsingVerbs' flag.");
					hasFinishedParsingVerbs = true;
				}
			}
		}
		
		iArg += processedArgumentsCount;
	}
	
	// Checking the "Required" flag recursively from the final verb back to the root verb.
	VerbW* tempReqVerb = currentVerb;
	while(tempReqVerb != NULL) {
		OptionW* tempReqOption = dllist_selectFirstData(tempReqVerb->options);
		
		while(tempReqOption != NULL) {
			if(tempReqOption->flags & FLAG_OPTION_REQUIRED && tempReqOption->occurrences < 1) {
				error_println("The '%c':'%s' option was required but not given !",
							  tempReqOption->token, tempReqOption->name);
				return ERROR_ARGUMENTS_REQUIRED_OPTION_UNUSED;
			}
			tempReqOption = (OptionW *) dllist_selectNextData(tempReqVerb->options);
		}
		
		tempReqVerb = tempReqVerb->parentVerb;
	}
	
	// Returning the last used verb if possible.
	if(pRelevantVerb != NULL) {
		*pRelevantVerb = currentVerb;
	}
	
	return ERROR_ARGUMENTS_NONE;
}

/** @} */ // end of arguments
