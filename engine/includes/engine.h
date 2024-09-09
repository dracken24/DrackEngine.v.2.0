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

typedef struct ButtonsMenu
{
    Button*  play;
    Button*  stop;
}   ButtonsMenu;

typedef struct  Engine
{
    Vector2         screenSize;
    MultipleCam3D	*allCameras;

    // Buttons Menu Up Bar
    ButtonsMenu buttonsMenuUp;

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

void    print_memory_usage(const char* phase);

//******************************************************************************//
//***                              sideUpPanel.h                              ***//
//******************************************************************************//

void	ftUpMenu2D(Engine *engine, Camera2D *camera);
void    ftDrawDropdownMenu(Engine *engine);

#endif
