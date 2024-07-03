/** @file */

#include "help.h"

#include "../text.h"

// Private constants

//const int np_args_value_name_len = 5;  // Refers to "VALUE" to make changing that later easier.

const char args_str_valueA[] = "<VALUE>";
const char args_str_valuesA[] = "<VALUE...>";

const wchar_t args_str_valueW[] = L"<VALUE>";
const wchar_t args_str_valuesW[] = L"<VALUE...>";

// Private functions

/**
 * Calculated the length that a printed out option would be.
 * @param option The relevant <code>Option</code>.
 * @param addBrackets Whether the printed <code>Option</code> should have the brackets and pipe.
 * @return The calculated string length.
 */
int args_getOptionLengthA(OptionA *option, bool addBrackets) {
	// It looks awful, but it works...
	return (addBrackets ? 2 : 0) +  // Brackets at the start and end
		   (option->token != '\0' ? 2 : 0) +  // Token plus the '-'
		   (!text_isEmptyA(option->name) ? (int) text_strlenA(option->name) + (
				   addBrackets ? 1 : 2
		   ) : 0) +  // The comma and space, or the '|'
		   (option->token != '\0' && !text_isEmptyA(option->name) ? 2 : 0) +  // The option's name and '--'
		   ((option->flags & FLAG_OPTION_HAS_VALUE)
			? (  // The "<VALUE>" bit and whether the '...' should be added to the value.
					((option->flags & FLAG_OPTION_REPEATABLE) ? 11 : 8) -
					(addBrackets ? 2 : 0)  // Not including brackets in brackets
			) : 0);
}

/**
 * Calculated the length that a printed out option would be.
 * @param option The relevant <code>Option</code>.
 * @param addBrackets Whether the printed <code>Option</code> should have the brackets and pipe.
 * @return The calculated string length.
 */
int args_getOptionLengthW(OptionW *option, bool addBrackets) {
	// It looks awful, but it works...
	return (addBrackets ? 2 : 0) +  // Brackets at the start and end
		   (option->token != '\0' ? 2 : 0) +  // Token plus the '-'
		   (!text_isEmptyW(option->name) ? (int) text_strlenW(option->name) + (
				   addBrackets ? 1 : 2
		   ) : 0) +  // The comma and space, or the '|'
		   (option->token != '\0' && !text_isEmptyW(option->name) ? 2 : 0) +  // The option's name and '--'
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
char *args_getOptionTextA(OptionA *option, bool addBrackets, int expectedLength) {
	int bufferOffset = 0;
	
	char *returnedString = malloc(sizeof(char) * (expectedLength + 1));
	
	if(addBrackets) {
		// FIXME: Nagging about info loss on conversion
		returnedString[bufferOffset] = (option->flags & FLAG_OPTION_REQUIRED ? '<' : '[');
		bufferOffset++;
	}
	
	if(option->token != '\0') {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = option->token;
		bufferOffset += 2;
	}
	
	if(option->token != '\0' && !text_isEmptyA(option->name)) {
		if(addBrackets) {
			returnedString[bufferOffset] = '|';
		} else {
			returnedString[bufferOffset] = ',';
			returnedString[bufferOffset + 1] = ' ';
			bufferOffset++;
		}
		bufferOffset++;
	}
	
	if(!text_isEmptyA(option->name)) {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = '-';
		bufferOffset += 2;
		int optionNameLength = text_strlenA(option->name);
		for(int j = 0; j < optionNameLength; j++) {
			returnedString[bufferOffset + j] = option->name[j];
		}
		bufferOffset +=optionNameLength;
	}
	
	if(option->flags & FLAG_OPTION_HAS_VALUE) {
		returnedString[bufferOffset] = ' ';
		bufferOffset++;
		
		if((option->flags & FLAG_OPTION_REPEATABLE)) {
			memcpy(&returnedString[bufferOffset], &args_str_valuesA[0 + (addBrackets ? 1 : 0)], (10 - (addBrackets ? 2 : 0)) * sizeof(char));
			bufferOffset += 10 - (addBrackets ? 2 : 0);
		} else {
			memcpy(&returnedString[bufferOffset], &args_str_valueA[0 + (addBrackets ? 1 : 0)], (7 - (addBrackets ? 2 : 0)) * sizeof(char));
			bufferOffset += 7 - (addBrackets ? 2 : 0);
		}
	}
	
	if(addBrackets) {
		// FIXME: Nagging about info loss on conversion
		returnedString[bufferOffset] = (option->flags & FLAG_OPTION_REQUIRED ? '>' : ']');
		bufferOffset++;
	}
	
	returnedString[bufferOffset] = '\0';
	
	return returnedString;
}

/**
 * Composes a string for a given option in a buffer of a given length.
 * The given length is assumed to be exact and won't be checked during the composition process.
 * @param option The relevant <code>Option</code>.
 * @param addBrackets Whether the square or pointy brackets should be included.
 * @param expectedLength The expected string length as given by <code>args_getOptionLength</code>.
 * @return The string pointer.
 */
wchar_t *args_getOptionTextW(OptionW *option, bool addBrackets, int expectedLength) {
	int bufferOffset = 0;
	
	wchar_t *returnedString = malloc(sizeof(wchar_t) * (expectedLength + 1));
	
	if(addBrackets) {
		returnedString[bufferOffset] = (option->flags & FLAG_OPTION_REQUIRED ? '<' : '[');
		bufferOffset++;
	}
	
	if(option->token != '\0') {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = option->token;
		bufferOffset += 2;
	}
	
	if(option->token != '\0' && !text_isEmptyW(option->name)) {
		if(addBrackets) {
			returnedString[bufferOffset] = '|';
		} else {
			returnedString[bufferOffset] = ',';
			returnedString[bufferOffset + 1] = ' ';
			bufferOffset++;
		}
		bufferOffset++;
	}
	
	if(!text_isEmptyW(option->name)) {
		returnedString[bufferOffset] = '-';
		returnedString[bufferOffset + 1] = '-';
		bufferOffset += 2;
		int optionNameLength = text_strlenW(option->name);
		for(int j = 0; j < optionNameLength; j++) {
			returnedString[bufferOffset + j] = option->name[j];
		}
		bufferOffset +=optionNameLength;
	}
	
	if(option->flags & FLAG_OPTION_HAS_VALUE) {
		returnedString[bufferOffset] = ' ';
		bufferOffset++;
		
		if((option->flags & FLAG_OPTION_REPEATABLE)) {
			memcpy(&returnedString[bufferOffset], &args_str_valuesW[0 + (addBrackets ? 1 : 0)], (10 - (addBrackets ? 2 : 0)) * sizeof(wchar_t));
			bufferOffset += 10 - (addBrackets ? 2 : 0);
		} else {
			memcpy(&returnedString[bufferOffset], &args_str_valueW[0 + (addBrackets ? 1 : 0)], (7 - (addBrackets ? 2 : 0)) * sizeof(wchar_t));
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
int args_printOptionA(OptionA *option, short consoleWidth, int newLineSpaceLength, int currentX, bool addBrackets) {
	// Calculating the size of the option details to be printed.
	int expectedLength = args_getOptionLengthA(option, addBrackets);
	
	// Checking if we need to cleanly make a line return before printing.
	if(currentX + expectedLength > consoleWidth) {
		printf("\n%*c", newLineSpaceLength, ' ');
		currentX = newLineSpaceLength + expectedLength;
	} else {
		currentX += expectedLength;
	}
	
	// Printing the actual option details
	char *optText = args_getOptionTextA(option, addBrackets, expectedLength);
	printf("%s", optText);
	
	free(optText);
	
	return currentX;
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
int args_printOptionW(OptionW *option, short consoleWidth, int newLineSpaceLength, int currentX, bool addBrackets) {
	// Calculating the size of the option details to be printed.
	int expectedLength = args_getOptionLengthW(option, addBrackets);
	
	// Checking if we need to cleanly make a line return before printing.
	if(currentX + expectedLength > consoleWidth) {
		printf("\n%*c", newLineSpaceLength, ' ');
		currentX = newLineSpaceLength + expectedLength;
	} else {
		currentX += expectedLength;
	}
	
	// Printing the actual option details
	wchar_t *optText = args_getOptionTextW(option, addBrackets, expectedLength);
	printf("%ws", optText);
	
	free(optText);
	
	return currentX;
}

// Public functions

bool args_printHelpText(VerbA *verb, char *programName, short consoleWidth) {
	if (verb == NULL || programName == NULL) {
		return false;
	}
	
	for(int i=0; i<consoleWidth; i++) {
		printf("#");
	}
	printf("\n");
	
	// Preparing variables
	
	// Keeping this here avoids recalculating it like a dozen times.
	int programNameLength = text_strlenA(programName);
	
	// Used to keep track of the cursor's current X position in order to intelligently do line returns.
	int currentX = programNameLength + 1;
	
	// Used in loops.
	OptionA *currentOption = NULL;
	
	// Printing the usage
	printf("%s ", programName);
	
	// TODO: Print the verbs used in the reverse order "exe v1 v2 <...> v3 (options) sub-verbs"
	
	currentOption = dllist_selectFirstData(verb->options);
	while (currentOption != NULL) {
		currentX = args_printOptionA(currentOption, consoleWidth, programNameLength + 1, currentX, true);
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
		VerbA *currentSubVerb = dllist_selectFirstData(verb->verbs);
		while (currentSubVerb != NULL) {
			printf("%s ", currentSubVerb->name);
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
			currentX = args_printOptionA(currentOption, 0, 2, 0, false);
			
			// TODO: Print the description
			
			currentOption = dllist_selectNextData(verb->options);
		}
	}
	printf("\n");
	
	return true;
}


bool args_printHelpTextW(VerbW *verb, wchar_t *programName, short consoleWidth) {
	if (verb == NULL || programName == NULL) {
		return false;
	}
	
	for(int i=0; i<consoleWidth; i++) {
		printf("#");
	}
	printf("\n");
	
	// Preparing variables
	
	// Keeping this here avoids recalculating it like a dozen times.
	int programNameLength = text_strlenW(programName);
	
	// Used to keep track of the cursor's current X position in order to intelligently do line returns.
	int currentX = programNameLength + 1;
	
	// Used in loops.
	OptionW *currentOption = NULL;
	
	// Printing the usage
	printf("%ws ", programName);
	
	// TODO: Print the verbs used in the reverse order "exe v1 v2 <...> v3 (options) sub-verbs"
	
	currentOption = dllist_selectFirstData(verb->options);
	while (currentOption != NULL) {
		currentX = args_printOptionW(currentOption, consoleWidth, programNameLength + 1, currentX, true);
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
		VerbW *currentSubVerb = dllist_selectFirstData(verb->verbs);
		while (currentSubVerb != NULL) {
			printf("%ws ", currentSubVerb->name);
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
			currentX = args_printOptionW(currentOption, 0, 2, 0, false);
			
			// TODO: Print the description
			
			currentOption = dllist_selectNextData(verb->options);
		}
	}
	printf("\n");
	
	return true;
}
