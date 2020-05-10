#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <stdio.h>
#include <stdarg.h>

#define CALCULATOR_VERSION_1_9

#define VERY_SMALL_DOUBLE 0.000000000001 // 10^-12

#define OUTPUT_PRECISION 10

#define DEBUG_MODE 1

enum TIME_STAMP{
    NO_STAMP = false,
    STAMP = true
};

#if DEBUG_MODE
# define DEBUG_PRINT(str, args...) debug_print(str, ##args)
# define DEBUG_PRINT_NO_TIMESTAMP(str, args...) debug_print_no_timestamp(str, ##args);
#else
# define DEBUG_PRINT(...)
# define DEBUG_PRINT_NO_TIMESTAMP(str, args...)
#endif // DEBUG_MODE

/*
#if DEBUG_MODE
# define DEBUG_PRINT_NO_HEADER(str, args...) print_no_header(str, ##args)
#else
# define DEBUG_PRINT_NO_HEADER(...)
#endif // DEBUG_MODE
*/

extern void debug_print(const char *, ...);

extern void debug_print_no_timestamp(const char *, ...);

#endif // CONFIG_HPP_INCLUDED
