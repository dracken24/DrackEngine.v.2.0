#ifndef DSTRING_H
# define DSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../includes/engine_defines.h"

// Returns the length of the given string.
DE_API uint64 string_length(const char* str);

DE_API char* string_duplicate(const char* str);

// Case-sensitive string comparison. True if the same, otherwise false.
DE_API bl8 strings_equal(const char* str0, const char* str1);

#ifdef __cplusplus
}
#endif

#endif
