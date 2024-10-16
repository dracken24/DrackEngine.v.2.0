/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 exit.c       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/engine.h"
# include "memory/dmemory.h"
# include "utility/buttons.h"
# include "signals/signals.h"

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void    free_engine(Engine *engine);
void    close_open_windows(Engine *engine);

void    dr_exit(Engine *engine)
{
    (void)engine;

    DE_INFO("Closing open windows in engine");
    close_open_windows(engine);

    usleep(1200000);  // Attendre 1000ms
    // DE_WARNING("engine Files EXIT PID: %d", engine->new_window_pid[FILES_NEW].engine_pid);
    // DE_WARNING("engine Open EXIT PID: %d", engine->new_window_pid[FILES_OPEN].engine_pid);

    DE_INFO("Freeing engine in engine");
    free_engine(engine);

    DE_INFO("Waiting for 1000ms in engine");

    DE_INFO("Closing window in engine");
    CloseWindow();
}

// In engine, we need to close all the windows that are open
void    close_open_windows(Engine *engine)
{
    DE_INFO("Closing open windows");
    for (int i = 0; i < SUB_MENU_FILES_LENGTH; i++)
    {
        DE_TRACE("Checking if %d is running", engine->new_window_pid[i].engine_pid);
        if (engine->new_window_pid[i].engine_running)
        {
            DE_INFO("Sending signal from engine to %d", engine->new_window_pid[i].engine_pid);
            usleep(200000);  // Attendre 200ms
            if (kill(engine->new_window_pid[i].engine_pid, SIGNAL_CLEANUP_OTHERS_WINDOWS) == -1)
            {
                perror("Erreur lors de l'envoi du signal");
            }
            // Attendre que le processus enfant se termine
            int status;
            waitpid(engine->new_window_pid[i].engine_pid, &status, 0);
            
            engine->new_window_pid[i].engine_running = false;
            engine->new_window_pid[i].engine_pid = -1;
        }
        else
        {
            DE_DEBUG("Processus %d is not running", engine->new_window_pid[i].engine_pid);
        }
    }
}

void    free_engine(Engine *engine)
{
    button_unload(engine->buttonsMenuUp.play);
    button_unload(engine->buttonsMenuUp.stop);
    de_free(engine->allCameras, sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
	// de_free(engine->engine_pid, sizeof(d_Pid) * 10, MEMORY_TAG_ENTITY);
}
