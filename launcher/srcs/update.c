/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 update.c               *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/launcher.h"

void    draw(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    Vector2 center_text = (Vector2){GetScreenWidth() / 2 - MeasureText("DrackLauncher", 60) / 2, GetScreenHeight() / 2 - 20};
    Vector2 center_text2 = (Vector2){GetScreenWidth() / 2 - MeasureText("Press enter to start", 40) / 2, GetScreenHeight() / 2 - 75};

    DrawText("DrackLauncher", center_text.x, center_text.y, 60, BLACK);
    DrawText("Press enter to start", center_text2.x, center_text2.y, 40, BLACK);
    
    EndDrawing();
}

void    input_events(Launcher *launcher)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        // TODO: Need a fork to keep the launcher running while the engine is running
        system("cd ../engine && make && ./DrackEngine");
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        launcher->exitCt = true;
    }
}

void    window_events(Launcher *launcher)
{
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (IsWindowResized())
        {
            launcher->screenSize.x = GetScreenWidth();
            launcher->screenSize.y = GetScreenHeight();
            SetWindowSize(launcher->screenSize.x, launcher->screenSize.y);
        }
    }
}

void    dr_launcher_update(Launcher *launcher)
{
    input_events(launcher);
    window_events(launcher);

    draw();
}
