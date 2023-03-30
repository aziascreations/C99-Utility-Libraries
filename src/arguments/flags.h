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
};
