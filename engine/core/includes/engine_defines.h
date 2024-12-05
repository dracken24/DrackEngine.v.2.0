/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:      engine_defines.h        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Unsigned int types.
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed int types.
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

// Floating point types
typedef float fl32;
typedef double dbl64;

// Boolean types
typedef int bl32;
typedef char bl8;

// Properly define static assertions.
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define STATIC_ASSERT _Static_assert
#elif defined(__cplusplus) && __cplusplus >= 201103L
#define STATIC_ASSERT static_assert
#else
#define STATIC_ASSERT(cond, msg) typedef char static_assertion_##__LINE__[(cond) ? 1 : -1]
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(uint8) == 1, "Expected uint8 to be 1 byte.");
STATIC_ASSERT(sizeof(uint16) == 2, "Expected uint16 to be 2 bytes.");
STATIC_ASSERT(sizeof(uint32) == 4, "Expected uint32 to be 4 bytes.");
STATIC_ASSERT(sizeof(uint64) == 8, "Expected uint64 to be 8 bytes.");

STATIC_ASSERT(sizeof(sint8) == 1, "Expected sint8 to be 1 byte.");
STATIC_ASSERT(sizeof(sint16) == 2, "Expected sint16 to be 2 bytes.");
STATIC_ASSERT(sizeof(sint32) == 4, "Expected sint32 to be 4 bytes.");
STATIC_ASSERT(sizeof(sint64) == 8, "Expected sint64 to be 8 bytes.");

STATIC_ASSERT(sizeof(fl32) == 4, "Expected fl32 to be 4 bytes.");
STATIC_ASSERT(sizeof(dbl64) == 8, "Expected dbl64 to be 8 bytes.");

# define true 1
# define false 0
# define null NULL

// # ifndef nullptr
// #  define nullptr 0
// # endif

// Platform detection
# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define DE_PLATFORM_WINDOWS 1
# ifndef _WIN64
#  error "64-bit is required on Windows!"
# endif
# elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#  define DE_PLATFORM_LINUX 1
# if defined(__ANDROID__)
#  define DE_PLATFORM_ANDROID 1
# endif
# elif defined(__unix__)
// Catch anything not caught by the above.
#define DE_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#  define DE_PLATFORM_POSIX 1
# elif __APPLE__
// Apple platforms
#  define DE_PLATFORM_APPLE 1
#  include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#  define DE_PLATFORM_IOS 1
#  define DE_PLATFORM_IOS_SIMULATOR 1
# elif TARGET_OS_IPHONE
#  define DE_PLATFORM_IOS 1
// iOS device
# elif TARGET_OS_MAC
// Other kinds of Mac OS
# else
#  error "Unknown Apple platform"
# endif
# else
#  error "Unknown platform!"
# endif

# ifdef DE_EXPORT
// Exports
# ifdef _MSC_VER
#  define DE_API __declspec(dllexport)
# else
#  define DE_API __attribute__((visibility("default")))
# endif
# else
// Imports
#  ifdef _MSC_VER
#   define DE_API __declspec(dllimport)
#  else
#   define DE_API
#  endif
# endif

# define DE_CLAMP(value, min, max) (value <= min) ? min : (value >= max) ? max : value;

// Inlining
# ifdef _MSC_VER
#  define DE_INLINE __forceinline
#  define DE_NOINLINE __declspec(noinline)
# else
#  define DE_INLINE static inline
#  define DE_NOINLINE
# endif

#define GIBIBYTES(amount) ((amount) * 1024ULL * 1024ULL * 1024ULL)
#define MEBIBYTES(amount) ((amount) * 1024ULL * 1024ULL)
#define KIBIBYTES(amount) ((amount) * 1024ULL)

#define GIGABYTES(amount) ((amount) * 1000ULL * 1000ULL * 1000ULL)
#define MEGABYTES(amount) ((amount) * 1000ULL * 1000ULL)
#define KILOBYTES(amount) ((amount) * 1000ULL)

typedef struct range
{
    uint64 offset;
    uint64 size;
} range;

DE_INLINE uint64 get_aligned(uint64 operand, uint64 granularity) 
{
    return ((operand + (granularity - 1)) & ~(granularity - 1));
}

DE_INLINE range get_aligned_range(uint64 offset, uint64 size, uint64 granularity) 
{
    return (range){get_aligned(offset, granularity), get_aligned(size, granularity)};
}

#ifdef __cplusplus
}
#endif
