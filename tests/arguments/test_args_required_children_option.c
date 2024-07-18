#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'required options in parent verbs parsing behaviour'...\n");
	
	printf("> Preparing verbs and options for later tests...\n");
	Verb* rootVerb = args_createVerb(NULL, NULL);
	Verb* subVerb = args_createVerb(NP_TEXT("sub"), NULL);
	
	Option* rootRequiredOption = args_createOption('a', NULL, NULL, FLAG_OPTION_REQUIRED | FLAG_OPTION_ALLOW_VERBS_AFTER);
	Option* subRequiredOption = args_createOption('b', NULL, NULL, FLAG_OPTION_REQUIRED);
	
	args_registerOption(rootRequiredOption, rootVerb);
	args_registerOption(subRequiredOption, subVerb);
	
	args_registerVerb(subVerb, rootVerb);
	
	int invalidLaunchArgumentsLen = 2;
	text_char *invalidLaunchArguments[] = {
			NP_TEXT("sub"),
			NP_TEXT("-b"),
	};
	
	int validLaunchArgumentsLen = 3;
	text_char *validLaunchArguments[] = {
			NP_TEXT("-a"),
			NP_TEXT("sub"),
			NP_TEXT("-b"),
	};
	
	printf("> Running parser with missing root's required option...\n");
	enum EArgumentParserErrors error = args_parseArguments(
			rootVerb,
			invalidLaunchArguments, 0, invalidLaunchArgumentsLen,
			NULL);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_REQUIRED_OPTION_UNUSED, "Missing required option error");
	
	printf("> Preparing some values...\n");
	rootVerb->wasUsed = false;
	subVerb->wasUsed = false;
	rootRequiredOption->occurrences = 0;
	subRequiredOption->occurrences = 0;
	
	printf("> Running parser with all required options...\n");
	error = args_parseArguments(
			rootVerb,
			validLaunchArguments, 0, validLaunchArgumentsLen,
			NULL);
	
	printf("> Checking error...\n");
	assert(error == ERROR_ARGUMENTS_NONE, "No error returned");
	
	printf("> Freeing root verb, its sub-verbs and all related options...  (Check out logs and for segfault)\n");
	args_freeVerb(rootVerb);
	
	printf("All 'required options parsing behaviour' tests passed !\n");
	return 0;
}
