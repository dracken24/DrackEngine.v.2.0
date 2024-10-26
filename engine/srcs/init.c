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
#include "../../library/extern/raylib/src/rlgl.h"
#include <stdlib.h>
#include <stdio.h>

MultipleCam3D	*ftInitCameras(Engine *engine, MultipleCam3D *allCameras);
void			init_buttons_menu_up(Engine *engine);
void			init_fonts(Engine *engine);
void			init_workspace(Engine *engine);

void    dr_init(Engine *engine)
{
    engine->exitCt = false;
	engine->currentStateView = STATE_VIEW_ENGINE;
    engine->screenSize = (Vector2){1500, 750};
	engine->screenSizeWindow = WINDOW_OTHERS;

#ifdef DE_PLATFORM_LINUX
	setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 1);
    setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);
#endif
    open_window(engine->screenSize, engine->screenSize, "DrackEngine", true);
	SetTargetFPS(60);

    // DE_DEBUG("init %f", 1);

    engine->allCameras = (MultipleCam3D *)de_allocate(sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
    engine->allCameras = ftInitCameras(engine, engine->allCameras);
	
	engine->introCt = true;

	// Init Buttons 
	init_buttons_menu_up(engine);

	engine->ray.ray = (Ray){0};
	engine->ray.collision = (RayCollision){0};
    // DE_DEBUG("init %f", 2);
	
	Image imgTest = LoadImage("../assets/ichigo.png");
	engine->testTexture = LoadTextureFromImage(imgTest);
	UnloadImage(imgTest);

	init_workspace(engine);
	init_fonts(engine);
}

void	init_gizmo(Engine *engine)
{
	engine->testWorkspace.gizmo = rgizmo_create();;
	engine->testWorkspace.model = LoadModelFromMesh(GenMeshTorus(0.3, 1.5, 16.0, 16.0));
	engine->testWorkspace.modelCube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
}

void	init_fonts(Engine *engine)
{
	engine->fonts.defaultFont = LoadFontEx("../assets/fonts/HighlandGothicFLF.ttf", 20, 0, 0);
}

void	init_workspace(Engine *engine)
{
	init_gizmo(engine);
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
	// allCameras->camera00.camera2D = (Camera2D){0};
	// allCameras->camera00.camera2D.target = (Vector2){0, 0};
	// allCameras->camera00.camera2D.offset = (Vector2){0.0f, 0.0f};
	// allCameras->camera00.camera2D.rotation = 0.0f;
	// allCameras->camera00.camera2D.zoom = 1.0f;
	// allCameras->camera00.textForCam = LoadRenderTexture(engine->screenSize.x - 600, engine->screenSize.y - 30 -120);
	// allCameras->camera00.rectForCam = (Rectangle){
	// 	300,
	// 	30,
	// 	allCameras->camera00.textForCam.texture.width,
	// 	allCameras->camera00.textForCam.texture.height
	// };

    // Define the camera to look into 3d world
	allCameras->camera00.camera3D = (Camera){ 0 };
	allCameras->camera00.camera3D.position = (Vector3){ 10.0f, 10.0f, -10.0f }; // Camera position
	allCameras->camera00.camera3D.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	allCameras->camera00.camera3D.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	allCameras->camera00.camera3D.fovy = 60.0f;                                // Camera field-of-view Y
	allCameras->camera00.camera3D.projection = CAMERA_PERSPECTIVE;             // Camera mode type
	allCameras->camera00.textForCam = LoadRenderTexture(engine->screenSize.x - 600, engine->screenSize.y - 30 -120);
	allCameras->camera00.rectForCam = (Rectangle){
		300.0f,
		30.0f,
		allCameras->camera00.textForCam.texture.width,
		allCameras->camera00.textForCam.texture.height};

	// Camera panel side up
	allCameras->camera01.camera2D = (Camera2D){0};
	allCameras->camera01.camera2D.target = (Vector2){0, 0};
	allCameras->camera01.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera2D.rotation = 0.0f;
	allCameras->camera01.camera2D.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, engine->screenSize.y / 2);
	allCameras->camera01.rectForCam = (Rectangle){
		engine->screenSize.x - 300.0f,
		30,
		allCameras->camera01.textForCam.texture.width,
		allCameras->camera01.textForCam.texture.height
	};

	// Camera panel side down
	allCameras->camera02.camera2D = (Camera2D){0};
	allCameras->camera02.camera2D.target = (Vector2){0, 0};
	allCameras->camera02.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera2D.rotation = 0.0f;
	allCameras->camera02.camera2D.zoom = 1.0f;
	// allCameras->camera02.image = LoadImage("../assets/buttons/colorSideUpSelected.png");
	allCameras->camera02.textForCam = LoadRenderTexture(300, engine->screenSize.y / 2 - 30);
	allCameras->camera02.rectForCam = (Rectangle){
		engine->screenSize.x - 300.0f,
		engine->screenSize.y / 2 + 30,
		allCameras->camera02.textForCam.texture.width,
		allCameras->camera02.textForCam.texture.height
	};

	// Camera panel up
	allCameras->camera03.camera2D = (Camera2D){0};
	allCameras->camera03.camera2D.target = (Vector2){0, 0};
	allCameras->camera03.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera2D.rotation = 0.0f;
	allCameras->camera03.camera2D.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 30);
	allCameras->camera03.rectForCam = (Rectangle){
		0.0f,
		0.0f,
		allCameras->camera03.textForCam.texture.width,
		allCameras->camera03.textForCam.texture.height
	};

	// Camera Hyerarchy Left
	allCameras->camera04.camera2D = (Camera2D){0};
	allCameras->camera04.camera2D.target = (Vector2){0, 0};
	allCameras->camera04.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera04.camera2D.rotation = 0.0f;
	allCameras->camera04.camera2D.zoom = 1.0f;
	allCameras->camera04.textForCam = LoadRenderTexture(300, engine->screenSize.y - 30);
	allCameras->camera04.rectForCam = (Rectangle){
		0.0f,
		30.0f,
		allCameras->camera04.textForCam.texture.width,
		allCameras->camera04.textForCam.texture.height
	};

	// Console log, down center
	// Camera Hyerarchy Left
	allCameras->camera05.camera2D = (Camera2D){0};
	allCameras->camera05.camera2D.target = (Vector2){0, 0};
	allCameras->camera05.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera05.camera2D.rotation = 0.0f;
	allCameras->camera05.camera2D.zoom = 1.0f;
	// allCameras->camera02.image = LoadImage("../assets/test.png");
	allCameras->camera05.textForCam = LoadRenderTexture(allCameras->camera00.rectForCam.width, 120);
	allCameras->camera05.rectForCam = (Rectangle){
		engine->allCameras->camera04.rectForCam.width,
		engine->allCameras->camera00.rectForCam.height + engine->allCameras->camera03.rectForCam.height,
		allCameras->camera05.textForCam.texture.width,
		allCameras->camera05.textForCam.texture.height
	};

	// Camera New Window (New Project, Open Project ...)
	allCameras->camera07.camera2D = (Camera2D){0};
	allCameras->camera07.camera2D.target = (Vector2){0, 0};
	allCameras->camera07.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera07.camera2D.rotation = 0.0f;
	allCameras->camera07.camera2D.zoom = 1.0f;
	allCameras->camera07.textForCam = LoadRenderTexture(800, 500);
	allCameras->camera07.rectForCam = (Rectangle){
		0,
		0,
		allCameras->camera07.textForCam.texture.width,
		allCameras->camera07.textForCam.texture.height
	};
	
	return (allCameras);
}
