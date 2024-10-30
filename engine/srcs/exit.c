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

# include "engine.h"
# include "memory/dmemory.h"
# include "utility/buttons.h"
#include "utility/text_entry.h"

// # include <signal.h>
// # include <sys/types.h>
// # include <sys/wait.h>
# include <unistd.h>

void    free_engine(Engine *engine);
// void	destroy_all_other_windows_textBox(void);

void    dr_exit(Engine *engine)
{
    // DE_WARNING("engine Files EXIT PID: %d", engine->new_window_pid[FILES_NEW].engine_pid);
    // DE_WARNING("engine Open EXIT PID: %d", engine->new_window_pid[FILES_OPEN].engine_pid);

    DE_INFO("Waiting for 350ms in engine");
    usleep(350000);  // Attendre 350ms

    rgizmo_unload();
    UnloadModel(engine->testWorkspace.model);
    UnloadModel(engine->testWorkspace.modelCube);

    // destroy_all_other_windows_textBox();
    
    DE_INFO("Freeing engine in engine");
    free_engine(engine);


    DE_INFO("Closing window in engine");
    CloseWindow();
}

void    free_engine(Engine *engine)
{
    button_unload(&engine->buttonsMenuUp.play);
    button_unload(&engine->buttonsMenuUp.stop);

    UnloadTexture(engine->testTexture);

    UnloadFont(engine->fonts.defaultFont);

    de_free(engine->allCameras, sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
	// de_free(engine->language.dropdown_menus_03, sizeof(char**), MEMORY_TAG_STRING);
	// de_free(engine->engine_pid, sizeof(d_Pid) * 10, MEMORY_TAG_ENTITY);
}
