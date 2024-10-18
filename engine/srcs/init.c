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
void	init_buttons_menu_up(Engine *engine);
void	init_windows_pid(Engine *engine);

void    dr_init(Engine *engine)
{
    engine->exitCt = false;
    engine->screenSize = (Vector2){1500, 750};

    open_window(engine->screenSize, (Vector2){600, 400}, "DrackEngine", true);
	SetTargetFPS(60);

	engine->engine_pid_ct = 0;

    // DE_DEBUG("init %f", 1);
    engine->allCameras = (MultipleCam3D *)de_allocate(sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
	// engine->engine_pid = (d_Pid *)de_allocate(sizeof(d_Pid) * SUB_MENU_FILES_LENGTH, MEMORY_TAG_ENTITY);
	init_windows_pid(engine);
    engine->allCameras = ftInitCameras(engine, engine->allCameras);
    engine->introCt = true;

	// Init Buttons 
	init_buttons_menu_up(engine);
    // DE_DEBUG("init %f", 2);
}

void	init_windows_pid(Engine *engine)
{
	for (int i = 0; i < SUB_MENU_FILES_LENGTH; i++)
	{
		engine->new_window_pid[i].engine_running = false;
		engine->new_window_pid[i].engine_pid = -24;
	}
}

void	init_buttons_menu_up(Engine *engine)
{
	engine->buttonsMenuUp.play = button_init((Vector2){engine->screenSize.x /2 - 15, 2}, (Vector2){100, 100}, RED, WHITE, "../assets/buttons/play_00.png", 0.085, 0);
	engine->buttonsMenuUp.play->texture_hover = LoadTexture("../assets/buttons/play_00_selected.png");
	engine->buttonsMenuUp.stop = button_init((Vector2){engine->screenSize.x /2 + 15, 2}, (Vector2){100, 100}, RED, WHITE, "../assets/buttons/stop_00.png", 0.085, 0);
	engine->buttonsMenuUp.stop->texture_hover = LoadTexture("../assets/buttons/stop_00_selected.png");
	// DE_DEBUG("Play texture : %f, %f", engine->buttonsMenuUp.play->texture.width, engine->buttonsMenuUp.play->texture.height);

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
	allCameras->camera00.textForCam = LoadRenderTexture(engine->screenSize.x - 300, engine->screenSize.y - 30);
	allCameras->camera00.rectForCam = (Rectangle){0.0f, 30.0f, (float)allCameras->camera00.textForCam.texture.width,
		(float)-allCameras->camera00.textForCam.texture.height * -1};

	// Camera panel side up
	allCameras->camera01.camera2D = (Camera2D){0};
	allCameras->camera01.camera2D.target = (Vector2){0, 0};
	allCameras->camera01.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera2D.rotation = 0.0f;
	allCameras->camera01.camera2D.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3);
	allCameras->camera01.rectForCam = (Rectangle){(float)engine->screenSize.x - 300.0f, 30, (float)allCameras->camera01.textForCam.texture.width,
		(float)-allCameras->camera01.textForCam.texture.height * -1};

	// Camera panel side down
	allCameras->camera02.camera2D = (Camera2D){0};
	allCameras->camera02.camera2D.target = (Vector2){0, 0};
	allCameras->camera02.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera2D.rotation = 0.0f;
	allCameras->camera02.camera2D.zoom = 1.0f;
	// allCameras->camera02.image = LoadImage("../assets/buttons/colorSideUpSelected.png");
	allCameras->camera02.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3 * 2 - 30);
	allCameras->camera02.rectForCam = (Rectangle){(float)engine->screenSize.x - 300.0f, (float)engine->screenSize.y / 3 + 30, (float)allCameras->camera02.textForCam.texture.width,
		(float)-allCameras->camera02.textForCam.texture.height * -1};

	// Camera panel up
	allCameras->camera03.camera2D = (Camera2D){0};
	allCameras->camera03.camera2D.target = (Vector2){0, 0};
	allCameras->camera03.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera2D.rotation = 0.0f;
	allCameras->camera03.camera2D.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 30);
	allCameras->camera03.rectForCam = (Rectangle){0.0f, 0.0f, (float)allCameras->camera03.textForCam.texture.width,
		(float)-allCameras->camera03.textForCam.texture.height * -1};
	
	return (allCameras);
}
