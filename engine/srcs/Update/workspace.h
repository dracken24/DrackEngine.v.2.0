/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    25-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         workspace.h             *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#ifndef WORKSPACE_H
# define WORKSPACE_H

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "../../library/extern/raygizmo/include/raygizmo.h"

#define CAMERA_ROT_SPEED 0.003f
#define CAMERA_MOVE_SPEED 0.01f
#define CAMERA_ZOOM_SPEED 1.0f

void	draw_grid(int slices, float spacing, Color color);
void    update_camera(Camera3D *camera);

#endif
