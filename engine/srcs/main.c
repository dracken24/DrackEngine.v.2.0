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

void test_log(void);

int main(void)
{
    Engine engine;
    g_engine = &engine;

    test_log();

    initialize_memory();
    dr_init(&engine);
    print_memory_usage("INIT");

    struct sigaction sa;
    sa.sa_handler = cleanup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGNAL_CLEANUP, &sa, NULL);

    if (sigaction(SIGNAL_CLEANUP, &sa, NULL) == -1)
    {
        DE_ERROR("Erreur lors de la configuration du gestionnaire de signal");
        perror("sigaction");
        return 1;
    }

    struct sigaction sa2;
    sa2.sa_handler = sigchld_handler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa2, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    DE_INFO("Gestionnaire de signal configuré pour SIGNAL_CLEANUP");

    // Débloquer le signal
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGNAL_CLEANUP);
    if (sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
    {
        DE_ERROR("Erreur lors du déblocage du signal");
        perror("sigprocmask");
        return 1;
    }
    DE_INFO("Signal SIGNAL_CLEANUP_OTHERS_WINDOWS débloqué");

    // test_log();
    while (!WindowShouldClose() && !engine.exitCt)
	{
        dr_update(&engine);
        // DE_DEBUG("engine Files PID: %d", engine.new_window_pid[FILES_NEW].engine_pid);
        // DE_DEBUG("engine Open PID: %d", engine.new_window_pid[FILES_OPEN].engine_pid);
        if (engine.exitCt)
        {
            DE_INFO("Signal reçu, sortie de la boucle");
        }
	}

    dr_exit(&engine);
    print_memory_usage("EXIT");
    shutdown_memory();

    return (0);
}
