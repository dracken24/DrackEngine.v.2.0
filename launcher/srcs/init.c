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

void    dr_launcher_init(Launcher *launcher)
{
    launcher->exitCt = false;
    launcher->screenSize = (Vector2){1200, 750};
    launcher->engine_running = false;

    InitWindow(launcher->screenSize.x, launcher->screenSize.y, "DrackLauncher");

    // ToggleBorderlessWindowed();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(800, 600);
    // SetWindowMaxSize(1920, 1080);
    // ToggleFullscreen();
	SetTargetFPS(60);
}
