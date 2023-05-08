/** @file */

#pragma once

#include "./types.h"

/** @addtogroup arguments
 *  @{
 */

/**
 * \enum EArgumentParserErrors
 * \brief Errors returned by the \ref args_parseArguments function.
 *
 * <b>Warning:</b><br>
 * Any function or variables that will hold one of this enum's member should be typed as `ArgumentParserError` or `uint8_t` !<br>
 * The custom `ArgumentParserError` type is defined in \ref arguments/types.h.
 *
 * \see args_parseArguments
 */
enum EArgumentParserErrors /*: ArgumentParserError*/ {
	/**
	 * Indicates that the parser encountered no error.
	 */
	ERROR_ARGUMENTS_NONE = 0,
	
	/**
	 * Indicates that the parser failed to insert a value in an option. (Likely due to a malloc failure)
	 */
	ERROR_ARGUMENTS_INSERTION_FAILURE = 1,
	
	/**
	 * Indicates that an unknown option was given as a launch argument.
	 */
	ERROR_ARGUMENTS_UNKNOWN_OPTION = 10,
	
	/**
	 * Indicates that a default \ref arguments_option "Option" with the `FLAG_OPTION_DEFAULT` flag was needed but
	 *  couldn't be found in the current \ref arguments_verb "Verb".<br>
	 * This error is likely caused by improperly formatted launch arguments.
	 */
	ERROR_ARGUMENTS_NO_DEFAULT_FOUND = 11,
	
	/**
	 * Indicates that the `--` token was encountered more than once.
	 */
	ERROR_ARGUMENTS_DUAL_END_OF_OPTIONS = 12,
	
	/**
	 * Indicates that an \ref arguments_option "Option" without the `OPTION_FLAG_REPEATABLE` flag was found more
	 *  than once in the launch arguments.
	 */
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
	
	/**
	 * Special error that should never be returned.<br>
	 * It is used in duplicated checks which should never fail if the one in which this is present is reached.
	 */
	ERROR_ARGUMENTS_THIS_SHOULD_NOT_TRIGGER = 50,
};

/** @} */ // end of arguments
