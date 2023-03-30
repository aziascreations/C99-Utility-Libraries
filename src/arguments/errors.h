#pragma once

#include "./types.h"

enum EArgumentParserErrors /*: ArgumentParserError*/ {
	/** Indicates that the parser encountered no error. */
	ERROR_ARGUMENTS_NONE = 0,
	
	/** Indicates that the parser failed to insert a value in an option. (Likely due to a malloc failure) */
	ERROR_ARGUMENTS_INSERTION_FAILURE = 1,
	
	/** Indicates that an unknown option was given as a launch argument. */
	ERROR_ARGUMENTS_UNKNOWN_OPTION = 10,
	
	/**
	 * Indicates that an option with the `FLAG_OPTION_DEFAULT` flag was needed but couldn't be found.
	 * Most likely due to improperly formatted launch arguments.
	 */
	ERROR_ARGUMENTS_NO_DEFAULT_FOUND = 11,
	
	/** Indicates that the `--` keyword was encountered more than once. */
	ERROR_ARGUMENTS_DUAL_END_OF_OPTIONS = 12,
	
	/** Indicates that an option without the `OPTION_FLAG_REPEATABLE` flag was found more than once in the launch arguments. */
	ERROR_ARGUMENTS_SINGLE_OPTION_REUSED = 13,
	
	/** ??? */
	ERROR_ARGUMENTS_NO_ARGUMENTS_LEFT = 20,

/** ??? */
#define ERROR_ARGUMENTS_EXPECTED_ARGUMENT 21

/** ??? */
#define ERROR_ARGUMENTS_NO_VERB_OR_DEFAULT_FOUND 30

/** ??? */
#define ERROR_ARGUMENTS_OPTION_DOES_NOT_HAVE_ARGUMENTS 40
	
	/** ??? */
	ERROR_ARGUMENTS_OPTION_HAS_VALUE_AND_MORE_SHORTS = 41,
	
	/** ??? */
	ERROR_ARGUMENTS_THIS_SHOULD_NOT_TRIGGER = 50,
};
