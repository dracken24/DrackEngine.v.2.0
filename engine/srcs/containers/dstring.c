#include "dstring.h"
#include "../memory/dmemory.h"

#include <string.h>

uint64 string_length(const char* str)
{
    return strlen(str);
}

char* string_duplicate(const char* str)
{
    uint64 length = string_length(str);
    char* copy = de_allocate(length + 1, MEMORY_TAG_STRING);
    de_copy_memory(copy, str, length + 1);
    return copy;
}

// Case-sensitive string comparison. True if the same, otherwise false.
bl8 strings_equal(const char* str0, const char* str1)
{
    return strcmp(str0, str1) == 0;
}
