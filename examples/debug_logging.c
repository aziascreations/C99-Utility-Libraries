#include <stdio.h>

#include "../src/debug.h"

int main() {
	#if defined(NP_DEBUG_LOGGING)
		printf("Debug logging is enabled !\n");
	#else
		printf("Debug logging is disabled !\n");
		printf("Define `NP_DEBUG_LOGGING` in order to enable it.\n");
	#endif
	
	printf("> Trace prints:\n");
	trace_print("Trace message\n");
	trace_println("Now with parameters => '%d'+'%d'='%d'", 42, 5, 42 + 5);
	
	printf("> Debug prints:\n");
	debug_print("Debug message\n");
	debug_println("Now with a parameter => '%s'", "Howdy :)");
	
	printf("> Error prints:\n");
	error_print("Error message\n");
	error_println("Now with a parameter => '0x%08lx'", (unsigned long) 3735928559);
	
	return 0;
}
