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
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../../library/drackengine_lib/drackengine_lib.h"

#define SIGNAL_CLEANUP SIGUSR1

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
    if (IsKeyPressed(KEY_ENTER) && !launcher->engine_running)
    {
        launcher->engine_pid = fork();
        if (launcher->engine_pid == 0)
        {
            // Processus enfant
            chdir("../engine");
            system("make re");
            execl("./DrackEngine", "DrackEngine", NULL);
            exit(EXIT_FAILURE);  // En cas d'échec de execl
        }
        else if (launcher->engine_pid < 0)
        {
            // Erreur lors du fork
            perror("Erreur lors du fork");
        }
        else
        {
            // Processus parent
            launcher->engine_running = true;
        }
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        launcher->exitCt = true;
    }
}

void    window_events(Launcher *launcher)
{
    if (IsWindowResized())
    {
        // SetWindowMinSize(800, 600);
        launcher->screenSize.x = GetScreenWidth();
        launcher->screenSize.y = GetScreenHeight();
        SetWindowSize(launcher->screenSize.x, launcher->screenSize.y);
        DE_INFO("Window resized in luncher");
    }
}

void check_engine_status(Launcher *launcher)
{
    if (launcher->engine_running)
    {
        int status;
        pid_t result = waitpid(launcher->engine_pid, &status, WNOHANG);
        if (result == launcher->engine_pid)
        {
            // Le processus enfant s'est terminé
            launcher->engine_running = false;
            launcher->engine_pid = -1;
        }
        else if (result == -1)
        {
            // Erreur lors de la vérification du statut
            perror("Erreur lors de la vérification du statut du processus enfant");
            launcher->engine_running = false;
            launcher->engine_pid = -1;
        }
    }
}

void    dr_launcher_update(Launcher *launcher)
{
    input_events(launcher);
    check_engine_status(launcher);
    window_events(launcher);

    draw();
}

// void cleanup_engine(void)
// {
//     if (engine_running)
//     {
//         kill(engine_pid, SIGTERM);
//         waitpid(engine_pid, NULL, 0);
//         engine_running = false;
//     }
// }
