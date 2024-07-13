#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'required options parsing behaviour'...\n");
	
	printf("> Preparing verbs and options for later tests...\n");
	Verb* rootVerb = args_createVerb(NULL, NULL);
	
	Option* defaultOption1 = args_createOption('a', NULL, NULL,
											   FLAG_OPTION_DEFAULT | FLAG_OPTION_HAS_VALUE);
	Option* defaultOption2 = args_createOption('b', NULL, NULL,
											   FLAG_OPTION_DEFAULT | FLAG_OPTION_HAS_MULTIPLE_VALUE);
	Option* defaultOption3 = args_createOption('c', NULL, NULL,
											   FLAG_OPTION_DEFAULT | FLAG_OPTION_HAS_VALUE);
	
	args_registerOption(defaultOption1, rootVerb);
	args_registerOption(defaultOption2, rootVerb);
	args_registerOption(defaultOption3, rootVerb);
	
	int launchArgumentsLen = 6;
	text_char *launchArguments[] = {
			TEXT("one"),
			TEXT("two"),
			TEXT("three"),
			TEXT("--"), // From now on, all entries are values
			TEXT("-c"),
			TEXT("four"),
	};
	
	printf("> Running parser...\n");
	enum EArgumentParserErrors error = args_parseArguments(
			rootVerb,
			launchArguments, 0, launchArgumentsLen,
			NULL);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_NONE, "No error returned");
	
	printf("> Checking option usage count...\n");
	assert(defaultOption1->occurrences == 1, "Option '-a' used once");
	assert(defaultOption2->occurrences == 4, "Option '-b' used four times");
	assert(defaultOption3->occurrences == 0, "Option '-c' not used");
	
	// FIXME: The test description is wrong due to copy-pasting !
	printf("> Checking assigned values and their order...\n");
	assert(
			text_areStringsEqual(dllist_selectFirstData(defaultOption1->arguments), TEXT("one")),
			"Option '-a' at index 0");
	assert(
			text_areStringsEqual(dllist_selectFirstData(defaultOption2->arguments), TEXT("two")),
			"Option '-b' at index 0");
	assert(
			text_areStringsEqual(dllist_selectNextData(defaultOption2->arguments), TEXT("three")),
			"Option '-b' at index 1");
	assert(
			text_areStringsEqual(dllist_selectNextData(defaultOption2->arguments), TEXT("-c")),
			"Option '-b' at index 2");
	assert(
			text_areStringsEqual(dllist_selectNextData(defaultOption2->arguments), TEXT("four")),
			"Option '-b' at index 3");
	
	printf("> Freeing root verb, its sub-verbs and all related options...  (Check out logs and for segfault)\n");
	args_freeVerb(rootVerb);
	
	printf("All 'required options parsing behaviour' tests passed !\n");
	return 0;
}
