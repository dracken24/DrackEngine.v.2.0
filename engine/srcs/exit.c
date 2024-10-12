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

void    free_engine(Engine *engine);

void    dr_exit(Engine *engine)
{
    (void)engine;

    free_engine(engine);

    CloseWindow();
}

void    free_engine(Engine *engine)
{
    button_unload(engine->buttonsMenuUp.play);
    button_unload(engine->buttonsMenuUp.stop);
    de_free(engine->allCameras, sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
	de_free(engine->engine_pid, sizeof(d_Pid) * 10, MEMORY_TAG_ENGINE);
}
