/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    28-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:        file_dialog.h            *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#ifndef FILE_DIALOG_H
# define FILE_DIALOG_H

#ifdef __cplusplus
}
#endif

# include "engine_defines.h"
# include "raylib.h"

typedef struct  FileDialog
{
    bl8 isOpen;
    char currentPath[512];
    char selectedPath[512];
    Vector2 position;
    Vector2 size;
    bl8 shouldClose;
    int scrollOffset;
} FileDialog;

void init_file_dialog(FileDialog* dialog, const char* initialPath, Rectangle camRect);
void draw_file_dialog(FileDialog* dialog, Vector2 camPos);
bl8 file_dialog_should_close(FileDialog* dialog);

#ifdef __cplusplus
}
#endif

#endif
