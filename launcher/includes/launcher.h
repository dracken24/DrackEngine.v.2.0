/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     Launcher.h           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef LAUNCHER_H
# define LAUNCHER_H

# include "../../library/extern/raylib/src/raylib.h"
# include "../../library/libft/libft.h"

typedef struct  Launcher
{
    Vector2   screenSize;

    pid_t engine_pid;
    bool engine_running;
    
    bool exitCt;
}   Launcher;

void    dr_launcher_init(Launcher *launcher);
void    dr_launcher_update(Launcher *launcher);
void    dr_launcher_exit(Launcher *launcher);

#endif
