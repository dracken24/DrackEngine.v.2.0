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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "../../../../library/extern/raygizmo/include/raygizmo.h"

#define CAMERA_ROT_SPEED 0.003f
#define CAMERA_MOVE_SPEED 0.02f
#define CAMERA_ZOOM_SPEED 1.5f

void	draw_grid(int slices, float spacing, float thickness, Color color);
void    update_camera(Camera3D *camera);

#ifdef __cplusplus
}
#endif
