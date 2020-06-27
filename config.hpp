#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <stdio.h>
#include <stdarg.h>

#define VERSION_2_0

#define VERY_SMALL_DOUBLE 0.000000000001 // 10^-12

#define OUTPUT_PRECISION 10

#define DEBUG_MODE 0

#if DEBUG_MODE
# define DEBUG_PRINT(str, args...) debug_print(str, ##args)
#else
# define DEBUG_PRINT(...)
#endif // DEBUG_MODE

extern void debug_print(const char *, ...);

extern void debug_print_no_timestamp(const char *, ...);

#endif // CONFIG_HPP_INCLUDED
