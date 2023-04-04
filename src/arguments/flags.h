#pragma once

#include "./types.h"

enum EOptionFlags /*: OptionFlags*/ {
	/** Used by default to indicate that the <code>Option</code> has no special features. */
	FLAG_OPTION_NONE = 0b00000000,
	
	/**
	 * Used to indicate that an <code>Option</code> should be a default one,
	 * meaning that it can be used without using the short and long argument.
	 */
	FLAG_OPTION_DEFAULT = 0b00000001,
	
	/** Used to indicate that an <code>Option</code> can have at least one value. */
	FLAG_OPTION_HAS_VALUE = 0b00000010,
	
	/** Used to indicate that an <code>Option</code> can be used multiple time with or without a value. */
	FLAG_OPTION_REPEATABLE = 0b00000100,
	
	/** Used to indicate that an <code>Option</code> can have at one or more value(s). */
	FLAG_OPTION_HAS_MULTIPLE_VALUE = FLAG_OPTION_HAS_VALUE | FLAG_OPTION_REPEATABLE,
	
	/** Used to indicate that an <code>Option</code> shouldn't be shown in the help text. */
	FLAG_OPTION_HIDDEN = 0b00001000,
	
	/** Used to indicate that an <code>Option</code> must be used in the final <code>Verb</code>. */
	FLAG_OPTION_REQUIRED = 0b00010000,
	
	/** Used to indicate that an <code>Option</code> must stop the parsing process as soon as it has been handled. */
	FLAG_OPTION_STOPS_PARSING = 0b00100000,
	
	/**
	 * Used to indicate that an <code>Option</code> will not prevent further verbs from being parsed when encountered.
	 * Usage of this flag required some forethought as if the option uses the <code>FLAG_OPTION_DEFAULT</code> flag,
	 * 	its values may be interpreted as a verb and cause all kinds of errors
	 * A "better" alternative would be to only use the <code>FLAG_OPTION_REQUIRED</code> flag if the value is needed,
	 *  which wil force the user to explicitly use the option's name or token.
	 */
	FLAG_OPTION_ALLOW_VERBS_AFTER = 0b01000000,
};
