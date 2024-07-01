#include <stdio.h>
#include <stdlib.h>

#include "../../src/platform.h"

#include "../assert.h"
#include "../memutils.h"

#include "../../src/text.h"

static const char *text_no_trim = "Hello world !";

static const char *text_left_single_trim = "_Hello world !";
static const char *text_left_multi_trim = "___Hello world !";

static const char *text_right_single_trim = "Hello world !_";
static const char *text_right_multi_trim = "Hello world !___";

static const char *text_both_trim = "____Hello world !__";

static const char *text_empty_trim = "";
static const char *text_full_trim = "_______";
static const char *text_single_char_trim = "E";

int main(void) {
	// Preliminary tests
	assert(text_trimA(NULL, ' ') == NULL,
		   "Returns NULL if `string` is NULL")
	assert(text_trimA(text_no_trim, '\0') == NULL,
		   "Returns NULL if `trimmedChar` is NULL")
	
	// Preparing temporary variable.
	char *tmpCopy = NULL;
	
	
	// Testing without any trim
	tmpCopy = text_trimA(text_no_trim, '_');
	
	assert(tmpCopy != NULL, "No trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "No trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "No trim is the same as the original.")
	assert(text_no_trim != tmpCopy, "No trim doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "No trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "No trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with single char left trim
	tmpCopy = text_trimA(text_left_single_trim, '_');
	
	assert(tmpCopy != NULL, "Left single trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Left single trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "Left single trim is the same as the non-padded original.")
	assert(text_left_single_trim != tmpCopy, "Left single trim doesn't point to the original.")
	assert(text_no_trim != tmpCopy, "Left single trim doesn't point to the non-padded original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Left single trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Left single trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with multi char left trim
	tmpCopy = text_trimA(text_left_multi_trim, '_');
	
	assert(tmpCopy != NULL, "Left multi trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Left multi trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "Left multi trim is the same as the non-padded original.")
	assert(text_left_multi_trim != tmpCopy, "Left multi trim doesn't point to the original.")
	assert(text_no_trim != tmpCopy, "Left multi trim doesn't point to the non-padded original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Left multi trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Left multi trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with single char right trim
	tmpCopy = text_trimA(text_right_single_trim, '_');
	
	assert(tmpCopy != NULL, "Right single trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Right single trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "Right single trim is the same as the non-padded original.")
	assert(text_right_single_trim != tmpCopy, "Right single trim doesn't point to the original.")
	assert(text_no_trim != tmpCopy, "Right single trim doesn't point to the non-padded original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Right single trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Right single trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with multi char right trim
	tmpCopy = text_trimA(text_right_multi_trim, '_');
	
	assert(tmpCopy != NULL, "Right multi trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Right multi trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "Right multi trim is the same as the non-padded original.")
	assert(text_right_multi_trim != tmpCopy, "Right multi trim doesn't point to the original.")
	assert(text_no_trim != tmpCopy, "Right multi trim doesn't point to the non-padded original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Right multi trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Right multi trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with trim on both sides char right trim
	tmpCopy = text_trimA(text_both_trim, '_');
	
	assert(tmpCopy != NULL, "Dual-side trim isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Dual-side trim has `13` chars.")
	assert(strcmp(text_no_trim, tmpCopy) == 0, "Dual-side trim is the same as the non-padded original.")
	assert(text_both_trim != tmpCopy, "Dual-side trim doesn't point to the original.")
	assert(text_no_trim != tmpCopy, "Dual-side trim doesn't point to the non-padded original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Dual-side trim's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Dual-side trim's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing edge-cases
	assert(text_trimA(text_empty_trim, '_') == NULL,
		   "Trim on non-NULL empty string returned NULL.")
	assert(text_trimA(text_full_trim, '_') == NULL,
		   "Trim on non-empty string that would be empty after trimming returned NULL.")
	
	
	// Testing edgier-case
	tmpCopy = text_trimA(text_single_char_trim, '_');
	assert(tmpCopy != NULL, "Trim with a single non-trimmed character isn't NULL")
	
	assert(strlen(tmpCopy) == 1, "Trim with a single non-trimmed character has `1` chars.")
	assert(strcmp(text_single_char_trim, tmpCopy) == 0, "Trim with a single non-trimmed character is the same as the original.")
	assert(text_single_char_trim != tmpCopy, "Trim with a single non-trimmed character doesn't point to the original.")
	
	#ifndef NP_OS_WINDOWS
		assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (1 + 1), "DTrim with a single non-trimmed character's memory size is `>=2` chars long.")
	#else
		assert(memUtils_getSize(tmpCopy) == sizeof(char) * (1 + 1), "Trim with a single non-trimmed character's memory size is `==2` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	return 0;
}
