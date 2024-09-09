/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         utility.c               *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "../memory/dmemory.h"
#include "../../library/drackengine_lib/logger.h"

void    print_memory_usage(const char* phase)
{
    char* mem_usage = get_memory_usage_str(phase);
    DE_INFO(mem_usage);
    de_free(mem_usage, strlen(mem_usage) + 1, MEMORY_TAG_STRING);
}