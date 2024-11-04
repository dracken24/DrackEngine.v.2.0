/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	    dmemory.c               *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "dmemory.h"

#include "../../../../library/drackengine_lib/logger.h"
#include "../containers/dstring.h"
#include "../platform/platform.h"

#include "../../includes/engine_defines.h"

// TODO: Custom string lib
#include <string.h>
#include <stdio.h>

struct memory_stats
{
    uint64 total_allocated;
    uint64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ENGINE     ",
    "UI         ",
    "ARRAY      ",
    "DARRAY     ",
    "TEXTBOX    ",
    "BUTTONS    ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "};

static struct memory_stats stats;

void initialize_memory()
{
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory()
{
}

void* de_allocate(uint64 size, memory_tag tag)
{
    // DE_WARNING("de_allocate");
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        DE_WARNING("de_allocate called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    // TODO: Memory alignment
    void* block = platform_allocate(size, false);
    platform_zero_memory(block, size);
    return block;
}

void de_free(void* block, uint64 size, memory_tag tag)
{
    // DE_WARNING("de_free");
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        DE_WARNING("de_free called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    // TODO: Memory alignment
    platform_free(block, false);
}

void* de_zero_memory(void* block, uint64 size)
{
    return platform_zero_memory(block, size);
}

void* de_copy_memory(void* dest, const void* source, uint64 size)
{
    return platform_copy_memory(dest, source, size);
}

void* de_set_memory(void* dest, sint32 value, uint64 size)
{
    return platform_set_memory(dest, value, size);
}

char* get_memory_usage_str(const char* type)
{
    char buffer[8000] = "\n-----------------------------------\nSystem memory in use: ";
    strcat(buffer, type);
    strcat(buffer, "\n-----------------------------------\n");
    uint64 offset = strlen(buffer);

    for (uint32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i)
    {
        char unit[4] = "XiB";
        float amount = 1.0f;
        if (stats.tagged_allocations[i] >= GIBIBYTES(1))
        {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)GIBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= MEBIBYTES(1))
        {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)MEBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= KIBIBYTES(1))
        {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)KIBIBYTES(1);
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }

        sint32 length = snprintf(buffer + offset, 8000, "  %s: %.2f %s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    strcat(buffer, "-----------------------------------\n");
    char* out_string = string_duplicate(buffer);
    return out_string;
}
