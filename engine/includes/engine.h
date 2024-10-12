/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      Engine.h            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ENGINE_H
# define ENGINE_H

# include "../../library/extern/raylib/src/raylib.h"
# include "../../library/libft/libft.h"
# include "struct_globale.h"
# include "../../library/drackengine_lib/drackengine_lib.h"
# include "../srcs/utility/buttons.h"
# include "Config/menus.h"

typedef struct ButtonsMenu
{
    Button*  play;
    Button*  stop;
}   ButtonsMenu;

typedef struct d_Pid
{
    bool    engine_running;
    int     enum_link;
    pid_t   engine_pid;
}   d_Pid;


typedef struct  Engine
{
    Vector2         screenSize;
    MultipleCam3D	*allCameras;

    // Buttons Menu Up Bar
    ButtonsMenu buttonsMenuUp;

    // PID for new window
    int     engine_pid_ct;
    d_Pid   new_window_pid[SUB_MENU_FILES_LENGTH];

    bool    exitCt;
    bool    introCt;
}   Engine;

//******************************************************************************//
//***                               engine.h                                 ***//
//******************************************************************************//

void    dr_init(Engine *engine);
void    dr_update(Engine *engine);
void    dr_exit(Engine *engine);

//******************************************************************************//
//***                              utility.h                                 ***//
//******************************************************************************//

void	open_window(Vector2 screenSize, Vector2 minSize, char *title, bool resizable);
void    print_memory_usage(const char* phase);

//******************************************************************************//
//***                              sideUpPanel.h                             ***//
//******************************************************************************//

void	ftUpMenu2D(Engine *engine, Camera2D *camera);
void    ftDrawDropdownMenu(Engine *engine);

#endif
