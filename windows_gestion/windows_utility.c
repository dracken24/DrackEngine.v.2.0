/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackEngine   PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    12-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 windows_utility.c    	    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "windows_utility.h"

void cleanup_handler(int signum)
{
    DE_ERROR("Received signal in windows_utility #: %d", signum);
    // Pour que le lanceur envoie le signal au moteur pour quitter proprement
    if (signum == SIGNAL_CLEANUP)
    {
        DE_ERROR("SIGNAL_CLEANUP in windows_utility signal %d", signum);
        running = false;
    }
}
