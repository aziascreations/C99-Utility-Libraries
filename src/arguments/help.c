#include "help.h"

// Private constants

//const int np_args_value_name_len = 5;  // Refers to "VALUE" to make changing that later easier.
const np_args_char args_str_value[] = np_args_L("<VALUE>");
const np_args_char args_str_values[] = np_args_L("<VALUE...>");

// Private functions

/**
 * Calculated the length that a printed out option would be.
 * @param option The relevant <code>Option</code>.
 * @param addBrackets Whether the printed <code>Option</code> should have the brackets and pipe.
 * @return The calculated string length.
 */
int args_getOptionLength(Option *option, bool addBrackets) {
	// It looks awful, but it works...
	return (addBrackets ? 2 : 0) +  // Brackets at the start and end
		   (option->token != '\0' ? 2 : 0) +  // Token plus the '-'
		   (!np_args_isStringEmpty(option->name) ? (int) np_args_strlen(option->name) + (
				   addBrackets ? 1 : 2
		   ) : 0) +  // The comma and space, or the '|'
		   (option->token != '\0' && !np_args_isStringEmpty(option->name) ? 2 : 0) +  // The option's name and '--'
		   ((option->flags & FLAG_OPTION_HAS_VALUE)
			? (  // The "<VALUE>" bit and whether the '...' should be added to the value.
					((option->flags & FLAG_OPTION_REPEATABLE) ? 11 : 8) -
					(addBrackets ? 2 : 0)  // Not including brackets in brackets
			) : 0);
}

/**
 * Composes a string for a given option in a buffer of a given length.
 * The given length is assumed to be exact and won't be checked during the composition process.
 * @param option The relevant <code>Option</code>.
 * @param addBrackets Whether the square or pointy brackets should be included.
 * @param expectedLength The expected string length as given by <code>args_getOptionLength</code>.
 * @return The string pointer.
 */
np_args_char *args_getOptionText(Option *option, bool addBrackets, int expectedLength) {
	int bufferOffset = 0;
	
	np_args_char *returnedString = malloc(sizeof(np_args_char) * (expectedLength + 1));
	
	if(addBrackets) {
		returnedString[bufferOffset] = (option->flags & FLAG_OPTION_REQUIRED ? '<' : '[');
		bufferOffset++;
	}
	
	if(option->token != '\0') {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = option->token;
		bufferOffset += 2;
	}
	
	if(option->token != '\0' && !np_args_isStringEmpty(option->name)) {
		if(addBrackets) {
			returnedString[bufferOffset] = '|';
		} else {
			returnedString[bufferOffset] = ',';
			returnedString[bufferOffset + 1] = ' ';
			bufferOffset++;
		}
		bufferOffset++;
	}
	
	if(!np_args_isStringEmpty(option->name)) {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = '-';
		bufferOffset += 2;
		int optionNameLength = np_args_strlen(option->name);
		for(int j = 0; j < optionNameLength; j++) {
			returnedString[bufferOffset + j] = option->name[j];
		}
		bufferOffset +=optionNameLength;
	}
	
	if(option->flags & FLAG_OPTION_HAS_VALUE) {
		returnedString[bufferOffset] = ' ';
		bufferOffset++;
		
		if((option->flags & FLAG_OPTION_REPEATABLE)) {
			memcpy(&returnedString[bufferOffset], &args_str_values[0 + (addBrackets ? 1 : 0)], (10 - (addBrackets ? 2 : 0)) * sizeof(np_args_char));
			bufferOffset += 10 - (addBrackets ? 2 : 0);
		} else {
			memcpy(&returnedString[bufferOffset], &args_str_value[0 + (addBrackets ? 1 : 0)], (7 - (addBrackets ? 2 : 0)) * sizeof(np_args_char));
			bufferOffset += 7 - (addBrackets ? 2 : 0);
		}
	}
	
	if(addBrackets) {
		returnedString[bufferOffset] = (option->flags & FLAG_OPTION_REQUIRED ? '>' : ']');
		bufferOffset++;
	}
	
	returnedString[bufferOffset] = '\0';
	
	return returnedString;
}

/**
 *
 * @param option The relevant <code>Option</code>.
 * @param consoleWidth
 * @param programNameLength
 * @param currentX
 * @param addBrackets
 * @return The new currentX value.
 */
int args_printOption(Option *option, short consoleWidth, int newLineSpaceLength, int currentX, bool addBrackets) {
    // Calculating the size of the option details to be printed.
    int expectedLength = args_getOptionLength(option, addBrackets);
	
    // Checking if we need to cleanly make a line return before printing.
    if(currentX + expectedLength > consoleWidth) {
        printf("\n%*c", newLineSpaceLength, ' ');
		currentX = newLineSpaceLength + expectedLength;
    } else {
		currentX += expectedLength;
	}
	
    // Printing the actual option details
	np_args_char *optText = args_getOptionText(option, addBrackets, expectedLength);
	printf("%ws", optText);
	free(optText);
	
    return currentX;
}

// Public functions

// TODO: Change some formats for non-wchar_t prints.

bool args_printHelpText(Verb *verb, np_args_char *programName, short consoleWidth) {
    if (verb == NULL || programName == NULL) {
        return false;
    }
	
	for(int i=0; i<consoleWidth; i++) {
		printf("#");
	}
	printf("\n");
	
    // Preparing variables

    // Keeping this here avoids recalculating it like a dozen times.
    int programNameLength = np_args_strlen(programName);
	
	// Used to keep track of the cursor's current X position in order to intelligently do line returns.
	int currentX = programNameLength + 1;
	
	// Used in loops.
	Option *currentOption = NULL;
	
	// Printing the usage
    printf("%ws ", programName);
	
	// TODO: Print the verbs used in the reverse order "exe v1 v2 <...> v3 (options) sub-verbs"

    currentOption = dllist_selectFirstData(verb->options);
    while (currentOption != NULL) {
        currentX = args_printOption(currentOption, consoleWidth, programNameLength + 1, currentX, true);
        currentOption = dllist_selectNextData(verb->options);
		
		// Checking if we can print a space
		// If we can't, we let "args_printOption" handle the line return
		if(currentX < consoleWidth - 1) {
			printf(" ");
			currentX++;
		}
    }
	
	// TODO: [actions] for verbs and <X>/[X] if there are any defaults options.
	
	printf("\n\n");
	
	if(verb->verbs->size > 0) {
		printf("Actions:\n");
		Verb *currentSubVerb = dllist_selectFirstData(verb->verbs);
		while (currentSubVerb != NULL) {
			printf("  %ws", currentSubVerb->name);
			currentSubVerb = dllist_selectNextData(verb->verbs);
			printf("\n");
		}
		printf("\n");
	}
	
	if(verb->options->size > 0) {
		printf("Options:");
		
		currentOption = dllist_selectFirstData(verb->options);
		while (currentOption != NULL) {
			// Forcing the printer to make a line return for each option.
			currentX = args_printOption(currentOption, 0, 2, 0, false);
			
			// TODO: Print the description
			
			currentOption = dllist_selectNextData(verb->options);
		}
	}
	printf("\n");
	
    return true;
}
