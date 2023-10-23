#include <stdbool.h>
#include <stdio.h>

#include "../src/debug.h"

#include "../src/arguments/arguments.h"

/** Main verb that will contain all options and sub-verbs. */
static Verb *rootVerb;

/** Simple non-repeatable flag option. */
static Option *versionOption;

/** Simple repeatable flag option. */
static Option *verbosityLevelOption;

/** Simple repeatable option with values. */
static Option *inputFilesOption;

bool prepareArguments() {
	rootVerb = args_createVerb(np_args_L("root"), np_args_L("Test"));
	
	versionOption = args_createOption('\0', np_args_L("version"), np_args_L("Prints the version"),
									  FLAG_OPTION_NONE);
	
	verbosityLevelOption = args_createOption('v', np_args_L("verbose"), np_args_L("Increase the verbosity"),
											 FLAG_OPTION_REPEATABLE);
	
	inputFilesOption = args_createOption('i', np_args_L("input"), np_args_L("Add a file to the processing queue"),
										 FLAG_OPTION_DEFAULT | FLAG_OPTION_HAS_MULTIPLE_VALUE);
	
	// Checking if no error occurred and if we can register all the options.
	return rootVerb != NULL && versionOption != NULL && verbosityLevelOption != NULL && inputFilesOption != NULL &&
			args_registerOption(versionOption, rootVerb) &&
			args_registerOption(verbosityLevelOption, rootVerb) &&
			args_registerOption(inputFilesOption, rootVerb);
}

int main() {
	// Preparing variables
	int errorCode = 0;
	
	
	// Preparing fake launch arguments
	int argc = 9;
	np_args_char* argv[] = {
		np_args_L("example.exe"),      // ???
		np_args_L("-vvv"),             // Increasing the verbosity by 3
		np_args_L("--verbose"),        // Increasing the verbosity by 1
		np_args_L("-i"),               // Adding a file
		np_args_L("file1.txt"),
		np_args_L("--"),               // No longer parsing options, only values for `-i,--input`.
		np_args_L("file2.txt"),
		np_args_L("--version"),        // Will be interpreted as a filename
		np_args_L("file3.txt"),
	};
	
	
	// Preparing launch arguments
	if(!prepareArguments()) {
		fprintf(stderr, "Failed to prepare launch arguments !");
		return 1;
	}
	
	
	// Parsing the launch arguments
	enum EArgumentParserErrors parserError = args_parseArguments(rootVerb, argv, 1, argc, NULL);
	if(parserError != ERROR_ARGUMENTS_NONE) {
		fprintf(stderr, "Unable to parse launch arguments !  (Error #%d) \n", parserError);
		errorCode = 2;
		goto END_CLEAN_VERB;
	}
	
	
	// Processing the launch arguments
	
	// We can check for usage in 2 identical ways.
	if(versionOption->occurrences > 0) {
		printf("The version is 1.0.0 :D\n");
	}
	if(args_wasOptionUsed(versionOption)) {
		printf("The version is still 1.0.0 :D\n");
	}
	
	// We can also get the usage count
	if(args_wasOptionUsed(verbosityLevelOption)) {
		printf("Activating verbosity level '%zu' !\n", verbosityLevelOption->occurrences);
	}
	
	// And we can iterate on values too
	if(args_wasOptionUsed(inputFilesOption)) {
		// We grab the first value
		np_args_char *currentValue = dllist_selectFirstData(inputFilesOption->arguments);
		
		while(currentValue != NULL) {
			// We either print a `char` or `wchar_t` value.
			#if defined(NP_GOODIES_ARGUMENTS_USE_WCHAR)
				printf("Value => '%ws'\n", currentValue);
			#else
				printf("Value => '%s'\n", currentValue);
			#endif
			
			// We go to the next value.
			currentValue = dllist_selectNextData(inputFilesOption->arguments);
		}
	}
	
	
	// Cleaning up
	END_CLEAN_VERB:
	trace_println("Cleaning verbs and options...");
	args_freeVerb(rootVerb);
	
	return errorCode;
}
