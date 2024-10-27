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

#include <raylib.h>

void    print_memory_usage(const char* phase)
{
    char* mem_usage = get_memory_usage_str(phase);
    DE_INFO(mem_usage);
    de_free(mem_usage, strlen(mem_usage) + 1, MEMORY_TAG_STRING);
}

void	open_window(Vector2 screenSize, Vector2 minSize, char *title, bool resizable)
{
	InitWindow(screenSize.x, screenSize.y, title);
	if (minSize.x > 0 && minSize.y > 0)
	{
		DE_DEBUG("Setting min size to %f, %f", minSize.x, minSize.y);
		SetWindowMinSize(minSize.x, minSize.y);
	}
	if (resizable)
		SetWindowState(FLAG_WINDOW_RESIZABLE);
    
}

Rectangle rectangle_addition(Rectangle rect01, Rectangle rect02)
{
	Rectangle rect_return;
	
	rect_return.x = rect01.x + rect02.x;
	rect_return.y = rect01.y + rect02.y;
	rect_return.width = rect01.width + rect02.width;
	rect_return.height = rect01.height + rect02.height;

	return rect_return;
}
