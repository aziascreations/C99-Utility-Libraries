#pragma once

#include <stdio.h>

#ifdef NP_DEBUG_LOGGING

#define debug_print(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

#define debug_println(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

#define error_print(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

#define error_println(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

#define trace_print(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__)

#define trace_println(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            printf(fmt, __VA_ARGS__); \
            printf("\n")

#ifdef NP_WIN32

#define debug_wprint(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

#define debug_wprintln(fmt, ...) \
            printf("D> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")

#define error_wprint(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

#define error_wprintln(fmt, ...) \
            printf("E> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")

#define trace_wprint(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__)

#define trace_wprintln(fmt, ...) \
            printf("T> %s:%d:%s() - ", __FILE__, __LINE__, __func__); \
            wprintf(L##fmt, __VA_ARGS__); \
            printf("\n")
#endif

#else

#define debug_print(fmt, ...)

#define debug_println(fmt, ...)

#define error_print(fmt, ...)

#define error_println(fmt, ...)

#define trace_print(fmt, ...)

#define trace_println(fmt, ...)

#ifdef NP_WIN32

#define debug_wprint(fmt, ...)

#define debug_wprintln(fmt, ...)

#define error_wprint(fmt, ...)

#define error_wprintln(fmt, ...)

#define trace_wprint(fmt, ...)

#define trace_wprintln(fmt, ...)

#endif

#endif
