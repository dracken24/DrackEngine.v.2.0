/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackEngine   PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 Main.c       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#define _XOPEN_SOURCE 700

# include "../includes/engine.h"
# include "../../library/drackengine_lib/drackengine_lib.h"
# include "../../library/drackengine_lib/utility/colors.h"
# include "../includes/temp_for_build.h"
# include "memory/dmemory.h"

// Déclaration globale de l'engine
Engine *g_engine = NULL;

void test_log(void);

int main(void)
{
    Engine engine;
    g_engine = &engine;
    ViewState currentView = STATE_VIEW_ENGINE;

    initialize_memory();
    dr_init(&engine);
    print_memory_usage("INIT");
    // test_log();

    while (!engine.exitCt)
    {
        dr_update(&engine);
    }

    dr_exit(&engine);
    shutdown_memory();
    print_memory_usage("EXIT");

    return 0;
}
