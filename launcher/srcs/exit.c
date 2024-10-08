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

# include "../includes/launcher.h"
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SIGNAL_CLEANUP SIGUSR1

void    dr_launcher_exit(Launcher *launcher)
{
    (void)launcher;

    if (launcher->engine_running)
    {
        // Envoyer le signal de nettoyage au processus enfant
        kill(launcher->engine_pid, SIGNAL_CLEANUP);
        
        // Attendre que le processus enfant se termine
        int status;
        waitpid(launcher->engine_pid, &status, 0);
        
        launcher->engine_running = false;
        launcher->engine_pid = -1;
    }

    CloseWindow();
}
