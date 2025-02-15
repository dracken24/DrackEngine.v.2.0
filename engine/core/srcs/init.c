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

#include "../includes/engine.h"
#include "memory/dmemory.h"
#include "utility/text_entry.h"

#include "rlgl.h"

#include <stdlib.h>
#include <stdio.h>

MultipleCam3D	*ftInitCameras(Engine *engine, MultipleCam3D *allCameras);
void			init_fonts(Engine *engine);
// void			init_workspace(Engine *engine);
void			init_all_other_windows_textBox(void);

bl8    dr_init(Engine *engine, CoreInfos *coreInfos)
{
	DE_DEBUG("Init Core");
	// init Engine
	{
		engine->exitCt = false;
		engine->allStates.currentStateView = STATE_VIEW_ENGINE;
		engine->allStates.currentStateMouse = MOUSE_STATE_ON_WORKSPACE;
		engine->allStates.blockMouseStates = false;
		engine->screenSize = (Vector2){1500, 750};
		engine->screenSizeWindow = WINDOW_OTHERS;
		engine->inputEventCt = false;
		engine->resizeCppCt = false;
		engine->mouseOnWorkspaceCpp = true;
	}
	// Init CoreInfos
	{
		coreInfos->coreVersion = de_allocate(sizeof(char) * 10, MEMORY_TAG_STRING);
		ft_strlcpy(coreInfos->coreVersion, "v.1.0.0.0", 10);
	}

#ifdef DE_PLATFORM_LINUX
	setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 1);
    setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);
#endif
    open_window(engine->screenSize, engine->screenSize, "DrackEngine", true);
	SetTargetFPS(60);
	engine->userSettings.currentFPS = 60;

    // DE_DEBUG("init %f", 1);

    engine->allCameras = (MultipleCam3D *)de_allocate(sizeof(MultipleCam3D), MEMORY_TAG_ENGINE);
    engine->allCameras = ftInitCameras(engine, engine->allCameras);
	
	engine->introCt = true;

	engine->ray.ray = (Ray){0};
	engine->ray.collision = (RayCollision){0};
    // DE_DEBUG("init %f", 2);
	
	Image imgTest = LoadImage("../assets/ichigo.png");
	engine->testTexture = LoadTextureFromImage(imgTest);
	UnloadImage(imgTest);

	// init_workspace(engine);
	init_fonts(engine);
	// init_all_other_windows_textBox();
	// change_language(engine, "en");
	// DE_DEBUG("In init Language: %s", engine->language.dropdown_menus_03[0][0]);

	return true;
}


void	init_fonts(Engine *engine)
{
	engine->fonts.defaultFont = LoadFontEx("../assets/fonts/HighlandGothicFLF.ttf", 20, 0, 0);
}

MultipleCam3D	*ftInitCameras(Engine *engine, MultipleCam3D *allCameras)
{
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
		engine->screenSize.x / 2 - allCameras->camera07.textForCam.texture.width /2,
		engine->screenSize.y / 2 - allCameras->camera07.textForCam.texture.height /2,
		allCameras->camera07.textForCam.texture.width,
		allCameras->camera07.textForCam.texture.height
	};
	
	return (allCameras);
}
