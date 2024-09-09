/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 init.c       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/engine.h"
# include "memory/dmemory.h"

MultipleCam3D	*ftInitCameras(Engine *engine, MultipleCam3D *allCameras);

void    dr_init(Engine *engine)
{
    engine->exitCt = false;
    engine->screenSize = (Vector2){1200, 750};

    InitWindow(engine->screenSize.x, engine->screenSize.y, "DrackEngine");

    SetWindowMinSize(800, 600);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

    // DE_DEBUG("init %f", 1);
    engine->allCameras = (MultipleCam3D *)de_allocate(sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
    engine->allCameras = ftInitCameras(engine, engine->allCameras);
    engine->introCt = true;
    // DE_DEBUG("init %f", 2);
}

MultipleCam3D	*ftInitCameras(Engine *engine, MultipleCam3D *allCameras)
{
    	// Define the camera to look into our 3d world
	allCameras->camera00.camera3D = (Camera){ 0 };
	allCameras->camera00.camera3D.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
	allCameras->camera00.camera3D.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	allCameras->camera00.camera3D.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	allCameras->camera00.camera3D.fovy = 45.0f;                                // Camera field-of-view Y
	allCameras->camera00.camera3D.projection = CAMERA_PERSPECTIVE;             // Camera mode type
	allCameras->camera00.textForCam = LoadRenderTexture(engine->screenSize.x - 300, engine->screenSize.y - 40);
	allCameras->camera00.rectForCam = (Rectangle){0.0f, 0.0f, (float)allCameras->camera00.textForCam.texture.width,
		(float)-allCameras->camera00.textForCam.texture.height};

	// Camera panel side up
	allCameras->camera01.camera2D = (Camera2D){0};
	allCameras->camera01.camera2D.target = (Vector2){0, 0};
	allCameras->camera01.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera2D.rotation = 0.0f;
	allCameras->camera01.camera2D.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3);
	allCameras->camera01.rectForCam = (Rectangle){0.0f, 0.0f, (float)allCameras->camera01.textForCam.texture.width,
		(float)-allCameras->camera01.textForCam.texture.height};

	// Camera panel side down
	allCameras->camera02.camera2D = (Camera2D){0};
	allCameras->camera02.camera2D.target = (Vector2){0, 0};
	allCameras->camera02.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera2D.rotation = 0.0f;
	allCameras->camera02.camera2D.zoom = 1.0f;
	allCameras->camera02.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3 * 2 - 40);
	allCameras->camera02.rectForCam = (Rectangle){0.0f, 0.0f, (float)allCameras->camera02.textForCam.texture.width,
		(float)-allCameras->camera02.textForCam.texture.height};

	// Camera panel up
	allCameras->camera03.camera2D = (Camera2D){0};
	allCameras->camera03.camera2D.target = (Vector2){0, 0};
	allCameras->camera03.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera2D.rotation = 0.0f;
	allCameras->camera03.camera2D.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 40);
	allCameras->camera03.rectForCam = (Rectangle){0.0f, 0.0f, (float)allCameras->camera03.textForCam.texture.width,
		(float)-allCameras->camera03.textForCam.texture.height};
	
	return (allCameras);
}
