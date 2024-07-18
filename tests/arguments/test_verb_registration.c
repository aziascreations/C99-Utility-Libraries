#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'verbs registration behaviour'...\n");
	
	printf("> Preparing verbs and options for later tests...\n");
	Verb* rootVerb = args_createVerb(NULL, NULL);
	
	Verb* validSubVerb1 = args_createVerb(NP_TEXT("create"), NULL);
	Verb* validSubVerb2 = args_createVerb(NP_TEXT("delete"), NULL);
	
	Verb* invalidSubVerb1 = args_createVerb(NULL, NULL);
	Verb* invalidSubVerb2 = args_createVerb(NP_TEXT("  "), NULL);
	
	Option* shortOption = args_createOption('a', NULL, NULL, FLAG_OPTION_NONE);
	Option* longOption = args_createOption('\0', NP_TEXT("bravo"), NULL, FLAG_OPTION_NONE);
	Option* mixedOption = args_createOption('c', NP_TEXT("charlie"), NULL, FLAG_OPTION_NONE);
	
	Option* recursiveOption = args_createOption('r', NP_TEXT("recursive"), NULL, FLAG_OPTION_NONE);
	
	/* Verb & registration */
	printf("> Testing registration failure of invalid verbs...\n");
	assert(rootVerb->verbs->size == 0, "Root verb's sub-verbs count is 0");
	assert(!args_registerVerb(invalidSubVerb1, rootVerb), "First invalid verb");
	assert(!args_registerVerb(invalidSubVerb2, rootVerb), "Second invalid verb");
	assert(rootVerb->verbs->size == 0, "Root verb's sub-verbs count is still 0");
	
	printf("> Testing registration of valid verbs...\n");
	assert(rootVerb->verbs->size == 0, "Root verb's sub-verbs count is 0");
	assert(args_registerVerb(validSubVerb1, rootVerb), "First valid verb");
	assert(args_registerVerb(validSubVerb2, rootVerb), "Second valid verb");
	assert(rootVerb->verbs->size == 2, "Root verb's sub-verbs count is 2");
	
	printf("> Testing invalid re-registration of valid verbs...\n");
	assert(!args_registerVerb(validSubVerb1, rootVerb), "First valid verb");
	assert(!args_registerVerb(validSubVerb2, rootVerb), "Second valid verb");
	assert(rootVerb->verbs->size == 2, "Root verb's sub-verbs count is still 2");
	
	printf("> Testing post-registration of valid verbs changes...\n");
	assert(validSubVerb1->parentVerb == rootVerb, "First valid verb's parent verb pointer");
	assert(validSubVerb2->parentVerb == rootVerb, "Second valid verb's parent verb pointer");
	
	printf("> Testing sub-verb getter...\n");
	assert(args_getSubVerbByName(rootVerb, NP_TEXT("create")) == validSubVerb1, "Getting 'create' from root");
	assert(args_getSubVerbByName(rootVerb, NP_TEXT("delete")) == validSubVerb2, "Getting 'delete' from root");
	assert(args_getSubVerbByName(rootVerb, NP_TEXT("error")) == NULL, "Getting 'error' from root, should be NULL");
	
	/* Options in verbs */
	printf("> Testing option registration in root verb...\n");
	assert(args_registerOption(shortOption, rootVerb), "Short option");
	assert(args_registerOption(longOption, rootVerb), "Long option");
	assert(args_registerOption(mixedOption, rootVerb), "Mixed option");
	
	printf("> Testing invalid option re-registration in root verb...\n");
	assert(!args_registerOption(shortOption, rootVerb), "Short option");
	assert(!args_registerOption(longOption, rootVerb), "Long option");
	assert(!args_registerOption(mixedOption, rootVerb), "Mixed option");
	
	printf("> Testing option getter with valid inputs...\n");
	assert(args_getOptionByToken(rootVerb, 'a') == shortOption, "Getting short with 'a'");
	assert(args_getOptionByName(rootVerb, NP_TEXT("bravo")) == longOption, "Getting long with \"bravo\"");
	assert(args_getOptionByToken(rootVerb, 'c') == mixedOption, "Getting mixed with 'c'");
	assert(args_getOptionByName(rootVerb, NP_TEXT("charlie")) == mixedOption, "Getting mixed with \"charlie\"");
	
	printf("> Testing option getter with invalid inputs...\n");
	assert(args_getOptionByToken(rootVerb, 'A') == NULL, "With 'A'");
	assert(args_getOptionByToken(rootVerb, 'b') == NULL, "With 'b'  (No token for \"bravo\")");
	assert(args_getOptionByToken(rootVerb, 'd') == NULL, "With 'd'");
	assert(args_getOptionByToken(rootVerb, ' ') == NULL, "With ' '");
	assert(args_getOptionByToken(rootVerb, '\0') == NULL, "With '\0'");
	assert(args_getOptionByName(rootVerb, NULL) == NULL, "With NULL");
	assert(args_getOptionByName(rootVerb, NP_TEXT(" ")) == NULL, "With \" \"");
	assert(args_getOptionByName(rootVerb, NP_TEXT(" charlie")) == NULL, "With \" charlie\"  (No hidden trimming)");
	
	printf("> Registering some options in sub-verbs...\n");
	assert(args_registerOption(shortOption, validSubVerb1), "Short option in 'create'");
	assert(args_registerOption(shortOption, validSubVerb2), "Short option in 'delete'");
	assert(args_registerOption(longOption, validSubVerb1), "Long option in 'create'");
	
	printf("> Testing recursive option registration...\n");
	assert(args_registerOptionRecursively(recursiveOption, rootVerb), "Recursive option registration");
	assert(args_getOptionByToken(rootVerb, 'r') == recursiveOption, "Recursive option by token in root verb");
	assert(args_getOptionByToken(validSubVerb1, 'r') == recursiveOption, "Recursive option by token in sub-verb 1");
	assert(args_getOptionByToken(validSubVerb2, 'r') == recursiveOption, "Recursive option by token in sub-verb 2");
	assert(args_getOptionByName(rootVerb, NP_TEXT("recursive")) == recursiveOption, "Recursive option by name in root verb");
	assert(args_getOptionByName(validSubVerb1, NP_TEXT("recursive")) == recursiveOption, "Recursive option by name in sub-verb 1");
	assert(args_getOptionByName(validSubVerb2, NP_TEXT("recursive")) == recursiveOption, "Recursive option by name in sub-verb 2");
	
	// From now on, results will be observed in the fact the tests don't cause segfaults, and via the debugging logs.
	
	printf("> Freeing verbs not referenced anywhere else...\n");
	args_freeVerb(invalidSubVerb1);
	args_freeVerb(invalidSubVerb2);
	
	printf("> Freeing root verb, its sub-verbs and all related options...  (Check out logs and for segfault)\n");
	args_freeVerb(rootVerb);
	
	printf("All 'verbs registration behaviour' tests passed !\n");
	return 0;
}
