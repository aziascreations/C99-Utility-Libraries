#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'required options parsing behaviour'...\n");
	
	printf("> Preparing verbs and options for later tests...\n");
	Verb* rootVerb = args_createVerb(NULL, NULL);
	
	Option* firstRequiredOption = args_createOption('a', NULL, NULL, FLAG_OPTION_REQUIRED);
	Option* secondRequiredOption = args_createOption('b', NULL, NULL, FLAG_OPTION_REQUIRED);
	
	args_registerOption(firstRequiredOption, rootVerb);
	args_registerOption(secondRequiredOption, rootVerb);
	
	int launchArgumentsLen = 2;
	text_char *launchArguments[] = {
			NP_TEXT("-a"),
			NP_TEXT("-b"),
	};
	
	printf("> Running parser with one missing required option...\n");
	enum EArgumentParserErrors error = args_parseArguments(
			rootVerb,
			launchArguments, 0, launchArgumentsLen - 1,
			NULL);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_REQUIRED_OPTION_UNUSED, "Missing required option error");
	
	printf("> Preparing some values...\n");
	rootVerb->wasUsed = false;
	firstRequiredOption->occurrences = 0;
	
	printf("> Running parser with all required options...\n");
	error = args_parseArguments(
			rootVerb,
			launchArguments, 0, launchArgumentsLen,
			NULL);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_NONE, "No error returned");
	
	printf("> Freeing root verb, its sub-verbs and all related options...  (Check out logs and for segfault)\n");
	args_freeVerb(rootVerb);
	
	printf("All 'required options parsing behaviour' tests passed !\n");
	return 0;
}
