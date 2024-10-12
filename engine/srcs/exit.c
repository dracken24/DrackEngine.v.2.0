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

void    free_engine(Engine *engine);

void    dr_exit(Engine *engine)
{
    (void)engine;

    close_open_windows(engine);

    free_engine(engine);

    CloseWindow();
}

void    close_open_windows(Engine *engine)
{
    for (int i = 0; i < SUB_MENU_FILES_LENGTH; i++)
    {
        // DE_DEBUG("Checking if %d is running", engine->new_window_pid[i].engine_pid);
        if (engine->new_window_pid[i].engine_running)
        {
            DE_INFO("Sending signal to %d", engine->new_window_pid[i].engine_pid);
            kill(engine->new_window_pid[i].engine_pid, SIGNAL_CLEANUP);
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
