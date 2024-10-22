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

// # include <signal.h>
// # include <sys/types.h>
// # include <sys/wait.h>
# include <unistd.h>

void    free_engine(Engine *engine);

void    dr_exit(Engine *engine)
{
    // DE_WARNING("engine Files EXIT PID: %d", engine->new_window_pid[FILES_NEW].engine_pid);
    // DE_WARNING("engine Open EXIT PID: %d", engine->new_window_pid[FILES_OPEN].engine_pid);

    DE_INFO("Waiting for 750ms in engine");
    usleep(350000);  // Attendre 350ms
    
    DE_INFO("Freeing engine in engine");
    free_engine(engine);


    DE_INFO("Closing window in engine");
    CloseWindow();
}

void    free_engine(Engine *engine)
{
    button_unload(engine->buttonsMenuUp.play);
    button_unload(engine->buttonsMenuUp.stop);
    UnloadTexture(engine->testTexture);
    de_free(engine->allCameras, sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
	// de_free(engine->engine_pid, sizeof(d_Pid) * 10, MEMORY_TAG_ENTITY);
}
