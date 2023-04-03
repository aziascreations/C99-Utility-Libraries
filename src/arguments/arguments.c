#include "arguments.h"

#include "../debug.h"


// Creators

Verb *args_createVerb(char *verb, char *description) {
	Verb *newVerb = malloc(sizeof(Verb));
	
	// Quickly "fixing" NULL parameters for later.
	if(verb == NULL) {
		verb = "";
	}
	if(description == NULL) {
		description = "";
	}
	
	if(newVerb != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newVerb->name = copyString(verb);
		newVerb->description = copyString(description);
		newVerb->verbs = dllist_create((void (*)(void *)) &args_freeVerb);
		newVerb->options = dllist_create((void (*)(void *)) &args_freeOption);
		newVerb->parentVerb = NULL;
		newVerb->wasUsed = false;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newVerb->name == NULL || newVerb->description == NULL || newVerb->verbs == NULL ||
		   newVerb->options == NULL) {
			args_freeVerb(newVerb);
			newVerb = NULL;
		}
	}
	
	return newVerb;
}

Option *args_createOption(char token, char *name, char *description, OptionFlags flags) {
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
	Option *newOption = malloc(sizeof(Option));
	
	if(newOption != NULL) {
		// We attempt to prepare all the fields assuming it worked for now.
		newOption->token = token;
		newOption->name = copyString(name);
		newOption->description = copyString(description);
		newOption->flags = flags;
		newOption->arguments = dllist_create(&free);
		newOption->occurrences = 0;
		newOption->registrationCount = 0;
		
		// Finally we check if the malloc operations worked, and if not, we just free it.
		if(newOption->name == NULL || newOption->description == NULL || newOption->arguments == NULL) {
			args_freeOption(newOption);
			newOption = NULL;
		}
	}
	
	return newOption;
}


// Cleaners

void args_freeVerb(Verb *verb) {
	if(verb != NULL) {
		trace_println("Starting to free verb '%s' @0x%p", verb->name, verb);
		
		// Safely freeing lists.
		// The subsequent required "args_freeVerb" and "args_freeOption" calls will be made automatically.
		if(verb->verbs != NULL) {
			dllist_free(verb->verbs);
		}
		if(verb->options != NULL) {
			dllist_free(verb->options);
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

void args_freeOption(Option *option) {
	if(option != NULL) {
		trace_println("Starting to free option '0d%i':'%s' @0x%p", option->token, option->name, option);
		
		// We first decrement the `registrationCount` variable and check if it is at `0`.
		// This done in order to allow the same option to be used in multiple verbs easily and transparently.
		option->registrationCount--;
		
		// Checking if it is still registered in a verb that wasn't freed.
		// Can be a negative number if the option was never registered !
		if(option->registrationCount > 0) {
			trace_println("Skipped the freeing process, still registered in another verb !");
			return;
		}
		
		// Safely freeing lists.
		// The subsequent required "free" calls will be made automatically.
		if(option->arguments != NULL) {
			dllist_free(option->arguments);
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

bool args_registerVerb(Verb *registeredVerb, Verb *parentVerb) {
	if(registeredVerb == NULL || parentVerb == NULL) {
		error_println("Unable to register verb: One of them is null !  (parent: @0x%p, sub: @0x%p)", parentVerb,
					  registeredVerb);
		return false;
	}
	
	if(registeredVerb->name == NULL || strlen(registeredVerb->name) == 0 || isStringEmpty(registeredVerb->name)) {
		error_println("Unable to register verb: The sub's name is NULL or empty !  (name: @0x%p)",
					  registeredVerb->name);
		return false;
	}
	
	if(args_isVerbAlreadyRegistered(registeredVerb, parentVerb)) {
		error_println("Unable to register verb: A similar verb is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->verbs, registeredVerb)) {
		error_println("Unable to register verb: Internal DLList error");
		return false;
	}
	registeredVerb->parentVerb = parentVerb;
	
	return true;
}

bool args_registerOption(Option *registeredOption, Verb *parentVerb) {
	if(registeredOption == NULL && parentVerb == NULL) {
		error_println("Unable to register option: One of the parameter is null !  (parent: @0x%p, option: @0x%p)",
					  parentVerb, registeredOption);
		return false;
	}
	
	if(args_isOptionAlreadyRegistered(registeredOption, parentVerb)) {
		error_println("Unable to register option: A similar option is already registered !");
		return false;
	}
	
	if(!dllist_append(parentVerb->options, registeredOption)) {
		error_println("Unable to register option: Internal DLList error");
		return false;
	}
	registeredOption->registrationCount++;
	
	return true;
}


// Getters

Verb *args_getParentVerb(Verb *verb) {
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

Option *args_getOptionByToken(Verb *verb, char desiredToken) {
	if(verb != NULL && desiredToken != '\0') {
		Option *currentOption = (Option *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			if(currentOption->token == desiredToken) {
				return currentOption;
			}
			currentOption = (Option *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

Option *args_getOptionByName(Verb *verb, char *desiredName) {
	if(verb != NULL && desiredName != NULL) {
		trace_println("Attempting to find the '%s' option in the '%s' verb...", desiredName, verb->name);
		
		Option *currentOption = (Option *) dllist_selectFirstData(verb->options);
		
		while(currentOption != NULL) {
			trace_println("Checking the '%i':'%s' registered option @0x%p ...", currentOption->token,
						  currentOption->name, currentOption);
			
			if(strcmp(currentOption->name, desiredName) == 0) {
				return currentOption;
			}
			
			currentOption = (Option *) dllist_selectNextData(verb->options);
		}
	}
	
	return NULL;
}

Verb *args_getSubVerbByName(Verb *parentVerb, char *desiredName) {
	if(parentVerb != NULL && desiredName != NULL) {
		Verb *currentSubVerb = (Verb *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentSubVerb != NULL) {
			if(strcmp(currentSubVerb->name, desiredName) == 0) {
				return currentSubVerb;
			}
			currentSubVerb = (Verb *) dllist_selectNextData(parentVerb->verbs);
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

bool args_addValueToOption(Option *option, char *addedValue) {
	if(option == NULL || addedValue == NULL) {
		error_println("Unable to add value to option, one of them is NULL !  (option: @0x%p, str: @0x%p)", option,
					  addedValue);
		return false;
	}
	
	char *addedValueCopy = copyString(addedValue);
	if(addedValue == NULL) {
		error_println("Unable to copy the current argument !");
		return false;
	}
	
	if(!dllist_append(option->arguments, addedValueCopy)) {
		error_println("Unable to insert the current argument into the option !");
		free(addedValueCopy);
		return false;
	}
	
	return true;
}

bool args_isVerbAlreadyRegistered(Verb *subVerb, Verb *parentVerb) {
	if(subVerb != NULL && parentVerb != NULL) {
		Verb *currentRegisteredSubVerb = (Verb *) dllist_selectFirstData(parentVerb->verbs);
		
		while(currentRegisteredSubVerb != NULL) {
			// Checking the pointer itself
			if(subVerb == currentRegisteredSubVerb) {
				return true;
			}
			
			// Checking the name itself if not empty in either.
			if(!isStringEmpty(subVerb->name) && !isStringEmpty(currentRegisteredSubVerb->name) &&
			   areStringsEqual(subVerb->name, currentRegisteredSubVerb->name)) {
				return true;
			}
			
			currentRegisteredSubVerb = (Verb *) dllist_selectNextData(parentVerb->verbs);
		}
	}
	
	return false;
}

bool args_isOptionAlreadyRegistered(Option *option, Verb *parentVerb) {
	if(option != NULL && parentVerb != NULL) {
		Option *currentRegisteredOption = (Option *) dllist_selectFirstData(parentVerb->options);
		
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
			if(!isStringEmpty(option->name) && !isStringEmpty(currentRegisteredOption->name) &&
			   areStringsEqual(option->name, currentRegisteredOption->name)) {
				return true;
			}
			
			currentRegisteredOption = (Option *) dllist_selectNextData(parentVerb->options);
		}
	}
	
	return false;
}


// Parser

enum EArgumentParserErrors args_parseArguments(Verb *rootVerb, char *arguments[], int startIndex, int endIndex,
											   Verb **pRelevantVerb) {
	Verb *currentVerb = rootVerb;
	
	// Maybe assigned in multiple places to keep track of the option to which values belong.
	Option *relevantOption = NULL;
	
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
		size_t currentArgumentSize = strlen(arguments[iArg]);
		
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
		
		if(stringStartsWith(arguments[iArg], "--")) {
			trace_println(" > Long option or end of parameters");
			
			hasFinishedParsingVerbs = true;
			
			if(strlen(arguments[iArg]) == 2) {
				trace_println(" > End of options symbol.");
				
				if(hasReachedEndOfOptions) {
					error_println("Dual end of options given as '--' !");
					return ERROR_ARGUMENTS_DUAL_END_OF_OPTIONS;
				}
				
				hasReachedEndOfOptions = true;
			} else if(hasReachedEndOfOptions) {
				trace_println(" > Default option's value that starts with '--'");
				
				relevantOption = args_getRelevantDefaultOption(currentVerb);
				
				if(relevantOption == NULL) {
					error_println("No relevant default option found in the '%s' verb !", currentVerb->name);
					return ERROR_ARGUMENTS_NO_DEFAULT_FOUND;
				}
				
				relevantOption->occurrences++;
				if(!args_addValueToOption(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
			} else {
				trace_println(" > Generic option by '--<name>'");
				
				// Use arguments[iArg]+2 instead of arguments[iArg][2..]
				
				trace_println("1");
				
				relevantOption = args_getOptionByName(currentVerb, arguments[iArg] + 2);
				if(relevantOption == NULL) {
					error_println("Unable to find the '%s' option !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				trace_println("2");
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The option '%s' was used more than once !", arguments[iArg] + 2);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				trace_println("3");
				
				if(relevantOption->flags & FLAG_OPTION_HAS_VALUE) {
					trace_println("4");
					
					if(!args_canOptionHaveMultipleValue(relevantOption) && relevantOption->occurrences > 1) {
						// Most likely is redundant as both of these checks are done earlier in some way.
						error_println("The option '%s' can only have 1 argument !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_THIS_SHOULD_NOT_TRIGGER;
					}
					
					trace_println("5");
					
					if(endIndex <= iArg + 1) {
						error_println("Unable to get a value for '%s', no arguments left !", arguments[iArg] + 2);
						return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
					}
					
					trace_println("6");
					
					if(!args_addValueToOption(relevantOption, arguments[iArg + 1])) {
						return ERROR_ARGUMENTS_INSERTION_FAILURE;
					}
					
					trace_println("7");
					
					processedArgumentsCount++;
				}
				
				trace_println("8");
			}
		} else if(stringStartsWith(arguments[iArg], "-")) {
			trace_println(" > Short option(s)");
			
			hasFinishedParsingVerbs = true;
			
			for(int iChar = 1; iChar < strlen(arguments[iArg]); iChar++) {
				trace_println(" > Doing '%c'", arguments[iArg][iChar]);
				
				relevantOption = args_getOptionByToken(currentVerb, arguments[iArg][iChar]);
				
				if(relevantOption == NULL) {
					error_println("Unable to find the '%c' short option !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_UNKNOWN_OPTION;
				}
				
				if(relevantOption->occurrences > 0 && !(relevantOption->flags & FLAG_OPTION_REPEATABLE)) {
					error_println("The short option '%c' as used more than once !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_SINGLE_OPTION_REUSED;
				}
				relevantOption->occurrences++;
				
				if(!(relevantOption->flags & FLAG_OPTION_HAS_VALUE)) {
					continue;
				}
				
				if(iChar + 1 < strlen(arguments[iArg])) {
					error_println(
							"\"The short option '%c' was given before the end of the argument while requiring a value !",
							arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_OPTION_HAS_VALUE_AND_MORE_SHORTS;
				}
				
				if(endIndex <= iArg + 1) {
					error_println("Unable to get a value for '%c', no arguments left !", arguments[iArg][iChar]);
					return ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT;
				}
				
				if(!args_addValueToOption(relevantOption, arguments[iArg + 1])) {
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
			
			Verb *desiredVerb = NULL;
			
			if(!hasFinishedParsingVerbs) {
				desiredVerb = args_getSubVerbByName(currentVerb, arguments[iArg]);
			}
			
			// Only grabbing the default option if we have no new relevant verb
			if(desiredVerb == NULL) {
				relevantOption = args_getRelevantDefaultOption(currentVerb);
				
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
				hasFinishedParsingVerbs = true;
				
				// Not checking for flags and max value count since "args_getRelevantDefaultOption" takes care of it !
				// Remark: We simply won't receive it and will just have NULL as if we had none !
				
				relevantOption->occurrences++;
				
				if(!args_addValueToOption(relevantOption, arguments[iArg])) {
					return ERROR_ARGUMENTS_INSERTION_FAILURE;
				}
			}
		}
		
		iArg += processedArgumentsCount;
	}
	
	// Checking the "Required" flag recursively from the final to the root verb.
	// TODO
	//foreach(Option option in currentVerb.Options) {
	
	// Returning the last used verb if possible.
	if(pRelevantVerb != NULL) {
		*pRelevantVerb = currentVerb;
	}
	
	return ERROR_ARGUMENTS_NONE;
}
