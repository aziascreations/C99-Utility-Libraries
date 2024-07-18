#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'basic args parsing behaviour'...\n");
	
	printf("> Preparing verbs and options for later tests...\n");
	Verb* rootVerb = args_createVerb(NULL, NULL);
	
	Option* shortToggleOption = args_createOption('a', NULL, NULL, FLAG_OPTION_NONE);
	Option* longToggleOption = args_createOption('\0', NP_TEXT("bravo"), NULL, FLAG_OPTION_NONE);
	
	Option* mixedRepeatOption = args_createOption('c', NP_TEXT("charlie"), NULL, FLAG_OPTION_REPEATABLE);
	
	args_registerOption(shortToggleOption, rootVerb);
	args_registerOption(longToggleOption, rootVerb);
	args_registerOption(mixedRepeatOption, rootVerb);
	
	int launchArgumentsLen = 4;
	text_char *launchArguments[] = {
			NP_TEXT("-ac"),
			NP_TEXT("--bravo"),
			NP_TEXT("--charlie"),
			NP_TEXT("-c")  // Will be ignored due to endIndex passed to `args_parseArguments`.
	};
	
	printf("> Running parser...\n");
	Verb* returnedVerb = NULL;
	enum EArgumentParserErrors error = args_parseArguments(
			rootVerb,
			launchArguments, 0, launchArgumentsLen - 1,
			&returnedVerb);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_NONE, "No parser error returned");
	
	printf("> Checking verb fields...\n");
	assert(returnedVerb == rootVerb, "Relevant verb is root");
	assert(rootVerb->wasUsed, "Root verb's `wasUsed` flag is `true`");
	
	printf("> Checking options usage counts...\n");
	assert(shortToggleOption->occurrences == 1, "Option '-a' used once");
	assert(longToggleOption->occurrences == 1, "Option '--bravo' used once");
	assert(mixedRepeatOption->occurrences == 2, "Option '-c|--charlie' used twice");
	
	printf("> Freeing root verb, its sub-verbs and all related options...  (Check out logs and for segfault)\n");
	args_freeVerb(rootVerb);
	
	printf("All 'basic args parsing behaviour' tests passed !\n");
	return 0;
}
