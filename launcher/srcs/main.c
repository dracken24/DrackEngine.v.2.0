/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    09-11-2022  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 Main.h       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/launcher.h"

void    draw(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawText("Press Enter to start", 375, 250, 40, BLACK);
    DrawText("       Engine       ", 340, 320, 60, BLACK);
    
    EndDrawing();
}

void    dr_update(Launcher *launcher)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        system("cd ../engine && make && ./DrackEngine");
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        launcher->_exitCt = true;
    }

    draw();
}

void    dr_init(Launcher *launcher)
{
    InitWindow(1200, 750, "DrackLanucher");
	SetTargetFPS(60);
    launcher->_exitCt = false;
}

void    dr_exit(Launcher *launcher)
{
    (void)launcher;

    CloseWindow();
}

int main(void)
{
    Launcher   launcher;

    dr_init(&launcher);

    while (!WindowShouldClose() && !launcher._exitCt)
	{
        dr_update(&launcher);
	}

    dr_exit(&launcher);
	
    return (0);
}
