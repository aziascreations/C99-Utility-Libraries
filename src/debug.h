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

#else

#define debug_print(fmt, ...)

#define debug_println(fmt, ...)

#define error_print(fmt, ...)

#define error_println(fmt, ...)

#define trace_print(fmt, ...)

#define trace_println(fmt, ...)

#endif
