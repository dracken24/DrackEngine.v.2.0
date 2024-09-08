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

typedef struct  Engine
{
    Vector2         screenSize;
    MultipleCam3D	*allCameras;

    bool    exitCt;
    bool    introCt;
}   Engine;

void    dr_init(Engine *engine);
void    dr_update(Engine *engine);
void    dr_exit(Engine *engine);

#endif
