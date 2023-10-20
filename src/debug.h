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

#ifdef NP_DEBUG_LOGGING

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_print(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_println(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_print(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_println(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_print(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` is defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_println(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_wprint(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define debug_wprintln(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_wprint(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define error_wprintln(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_wprint(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

/*!
 * Only available if `NP_DEBUG_LOGGING` and `NP_WIN32` are defined during compilation.
 * \param fmt A `char` string using standard `printf` formatting.
 * \param ... The additional argument(s).
 */
#define trace_wprintln(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")

#else

#define debug_print(fmt, ...)

#define debug_println(fmt, ...)

#define error_print(fmt, ...)

#define error_println(fmt, ...)

#define trace_print(fmt, ...)

#define trace_println(fmt, ...)

#define debug_wprint(fmt, ...)

#define debug_wprintln(fmt, ...)

#define error_wprint(fmt, ...)

#define error_wprintln(fmt, ...)

#define trace_wprint(fmt, ...)

#define trace_wprintln(fmt, ...)

#endif

/** @} */ // end of group_np_debug

#endif /* !NP_ONCE_C99_GOODIES_DEBUG */
