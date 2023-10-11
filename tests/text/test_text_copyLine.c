#include <stdio.h>

#include "../assert.h"
#include "../memutils.h"

#include "../../src/debug.h"
#include "../../src/text.h"

int main(void) {
	//char *a = "My text\r\nLine2";
	//char *a = "My text\r\n";
	char *a = "";
	
	trace_println("> %zu", strlen(a));
	
	char *nextLine = NULL;
	size_t nextLineMaxLength = 0;
	
	char *b = text_copyLine(a, strlen(a), &nextLine, &nextLineMaxLength);
	
	trace_println("> Next: '%s'", nextLine);
	trace_println("> Next Max: %zu", nextLineMaxLength);
	
	if(b != NULL) {
		trace_println("> Line: '%s'", b);
		free(b);
	}
	
	return 0;
}
