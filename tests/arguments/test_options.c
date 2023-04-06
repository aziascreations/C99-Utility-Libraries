#include <stdio.h>

#include "../assert.h"

#include "../../src/arguments/arguments.h"

int main(void) {
	printf("Testing 'options behaviour'...\n");
	Option* testedOption = args_createOption('a', np_args_L("alice"), np_args_L(""), FLAG_OPTION_NONE);
	
	assert(testedOption != NULL, "Allocation");
	
	np_args_char* valueAdded = np_args_L("abc123");
	
	assert(testedOption->arguments->size == 0, "Value count before adding");
	assert(args_addValueToOption(testedOption, valueAdded), "Adding value");
	assert(testedOption->arguments->size == 1, "Value count after adding");
	
	assert(testedOption->arguments->first->data != (void *) valueAdded, "Different addresses between source and saved values");
	
	// TODO: Assert on the multiple thingy flag to check if one of the 2 bits cannot trigger a true if poorly checked.
	
	printf("All 'options behaviour' tests passed !\n");
	return 0;
}
