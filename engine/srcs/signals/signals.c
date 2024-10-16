/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackEngine   PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    12-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 signals.c       	    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "signals.h"

void cleanup_handler(int signum)
{
    DE_INFO("Received SIGNAL in engine signals.c signal %d", signum);
    // For the launcher to send the signal to the engine to exit cleanly
    if (signum == SIGNAL_CLEANUP && g_engine != NULL)
    {
        DE_WARNING("SIGNAL_CLEANUP in engine signals.c signal %d", signum);
        dr_exit(g_engine);
        print_memory_usage("EXIT");
        shutdown_memory();
        exit(EXIT_SUCCESS);
    }
}

void sigchld_handler(int signum)
{
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        DE_INFO("Processus enfant %d terminé", pid);
        // Parcourez votre tableau de PID et mettez à jour le statut
        for (int i = 0; i < SUB_MENU_FILES_LENGTH; i++) {
            if (g_engine->new_window_pid[i].engine_pid == pid) {
                g_engine->new_window_pid[i].engine_running = false;
                g_engine->new_window_pid[i].engine_pid = -1;
                break;
            }
        }
    }
}
