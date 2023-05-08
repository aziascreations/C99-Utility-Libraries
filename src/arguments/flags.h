/** @file */

#pragma once

#include "./types.h"

/** @addtogroup arguments
 *  @{
 */

/**
 * \enum EOptionFlags
 * \brief Feature flags used when creating \ref arguments_option "Options".
 *
 * <b>Warning:</b><br>
 * Any function or variables that will hold one of this enum's member should be typed as `OptionFlags` or `uint8_t` !<br>
 * The custom `OptionFlags` type is defined in \ref arguments/types.h.
 *
 * \see args_createOption
 * \see arguments_option::flags
 */
enum EOptionFlags {
	/**
	 * Used by default to indicate that the \ref arguments_option "Option" has no special features.
	 */
	FLAG_OPTION_NONE = 0b00000000,
	
	/**
	 * Indicates that an \ref arguments_option "Option" should be a default one,
	 *  meaning that it can be used without using the short and long argument.<br>
	 * Its usage will be automatically detected in the parser.
	 */
	FLAG_OPTION_DEFAULT = 0b00000001,
	
	/**
	 * Indicates that an \ref arguments_option "Option" can have at least one value.
	 */
	FLAG_OPTION_HAS_VALUE = 0b00000010,
	
	/**
	 * Indicates that an \ref arguments_option "Option" can be used multiple time with or without a value.<br>
	 * The usage count can be found in \ref arguments_option::occurrences.
	 */
	FLAG_OPTION_REPEATABLE = 0b00000100,
	
	/**
	 * Indicates that an \ref arguments_option "Option" can have one or more value(s).
	 */
	FLAG_OPTION_HAS_MULTIPLE_VALUE = FLAG_OPTION_HAS_VALUE | FLAG_OPTION_REPEATABLE,
	
	/**
	 * Indicates that an \ref arguments_option "Option" shouldn't be shown in the help text.
	 */
	FLAG_OPTION_HIDDEN = 0b00001000,
	
	/**
	 * Indicates that an \ref arguments_option "Option" must be used in a used verb \ref arguments_verb "Verb".
	 */
	FLAG_OPTION_REQUIRED = 0b00010000,
	
	/**
	 * Indicates that an \ref arguments_option "Option" must stop the parsing process as soon as it has been parsed.
	 */
	FLAG_OPTION_STOPS_PARSING = 0b00100000,
	
	/**
	 * Indicates that an \ref arguments_option "Option" will not prevent further verbs from being parsed when encountered.<br>
	 * Usage of this flag required some forethought if the \ref arguments_option "Option" uses the
	 *  \ref FLAG_OPTION_DEFAULT flag since its values may be interpreted as a verb and cause all kinds
	 *  of errors.<br>
	 * A "better" alternative would be to only use the \ref FLAG_OPTION_REQUIRED flag if the value is needed,
	 *  which will force the user to explicitly use the option's name or token.
	 */
	FLAG_OPTION_ALLOW_VERBS_AFTER = 0b01000000,
};

/** @} */ // end of arguments
