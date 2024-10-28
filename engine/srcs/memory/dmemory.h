/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 dmemory.h              *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#ifndef DMEMORY_H
# define DMEMORY_H

#include "../../includes/engine_defines.h"

typedef enum memory_tag
{
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ENGINE,
    MEMORY_TAG_UI,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_TEXTBOX,
    MEMORY_TAG_BUTTONS,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

DE_API void initialize_memory();
DE_API void shutdown_memory();

DE_API void* de_allocate(uint64 size, memory_tag tag);

DE_API void de_free(void* block, uint64 size, memory_tag tag);

DE_API void* de_zero_memory(void* block, uint64 size);

DE_API void* de_copy_memory(void* dest, const void* source, uint64 size);

DE_API void* de_set_memory(void* dest, sint32 value, uint64 size);

DE_API char* get_memory_usage_str(const char* type);

#endif // DMEMORY_H
