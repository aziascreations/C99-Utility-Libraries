/** @file */

#if !defined(NP_ONCE_C99_GOODIES_DEBUG)
#define NP_ONCE_C99_GOODIES_DEBUG

#include <stdio.h>

#include "platform.h"

/** @defgroup group_np_debug Debug printing
 *
 * All macros print a given string in the following format:<br>
 *  `{LEVEL}> {SRC_PATH}:{LINE}:{FCT}() - {TEXT}`<br>
 * The `{LEVEL}` can be `D` for debug, `E` for error, and `T` for trace.<br>
 * The `{SRC_PATH}:{LINE}:{FCT}` should allow you to quickly jump to the line that prints the text in modern IDEs.<br>
 * The `{TEXT}` represents the text you're giving after it is formatted.
 *
 * <b>Warning:</b><br>
 * Unless `NP_DEBUG_LOGGING` is defined, all macros will be expanded to an empty statement regardless of other defined
 *  constants.<br>
 *
 * Unless `NP_WIN32` is defined, all macros that have a `w` before the `print` part won't be accessible.<br>
 * This is due to the fact that `wchar_t` is only accessible easily on Windows platforms.
 *
 * \see https://cplusplus.com/reference/cstdio/printf/
 *
 * @{
 */

// Unicode macros
#if defined(NP_UNICODE)
	#define debug_print debug_printW
	#define debug_println debug_printlnW
	#define error_print error_printW
	#define error_println error_printlnW
	#define trace_print trace_printW
	#define trace_println trace_printlnW
#else
	#define debug_print debug_printA
	#define debug_println debug_printlnA
	#define error_print error_printA
	#define error_println error_printlnA
	#define trace_print trace_printA
	#define trace_println trace_printlnA
#endif

// TODO: Add a special option to explicitly use the Win32 versions of these functions for UCRT-less linking.
// Keep this for a future branch that starts off the coming 1.0.0

#ifdef NP_DEBUG_LOGGING

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_printA(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_printlnA(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_printA(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_printlnA(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_printA(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_printlnA(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, ##__VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_printW(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_printlnW(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_printW(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_printlnW(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_printW(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_printlnW(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, ##__VA_ARGS__); \
            printf("\n")

#else

#define debug_printA(fmt, ...)

#define debug_printlnA(fmt, ...)

#define error_printA(fmt, ...)

#define error_printlnA(fmt, ...)

#define trace_printA(fmt, ...)

#define trace_printlnA(fmt, ...)

#define debug_printW(fmt, ...)

#define debug_printlnW(fmt, ...)

#define error_printW(fmt, ...)

#define error_printlnW(fmt, ...)

#define trace_printW(fmt, ...)

#define trace_printlnW(fmt, ...)

#endif


/** @} */ // end of group_np_debug

#endif /* !NP_ONCE_C99_GOODIES_DEBUG */
