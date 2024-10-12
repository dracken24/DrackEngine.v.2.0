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
# include "signals/signals.h"
# include "memory/dmemory.h"

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>


// Déclaration globale de l'engine
Engine *g_engine = NULL;

int main(void)
{
    Engine engine;
    g_engine = &engine;

    initialize_memory();
    dr_init(&engine);
    print_memory_usage("INIT");

    struct sigaction sa;
    sa.sa_handler = cleanup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGNAL_CLEANUP, &sa, NULL);

    // test_log();
    while (!WindowShouldClose() && !engine.exitCt)
	{
        dr_update(&engine);
	}

    dr_exit(&engine);
    print_memory_usage("EXIT");
    shutdown_memory();

    return (0);
}
