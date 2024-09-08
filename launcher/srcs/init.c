/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 init.c       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/launcher.h"

void    dr_init(Launcher *launcher)
{
    launcher->exitCt = false;
    launcher->screenSize = (Vector2){1200, 750};

    InitWindow(launcher->screenSize.x, launcher->screenSize.y, "DrackLauncher");

    // ToggleBorderlessWindowed();
    SetWindowMinSize(800, 600);
    // SetWindowMaxSize(1920, 1080);
    // ToggleFullscreen();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
}
