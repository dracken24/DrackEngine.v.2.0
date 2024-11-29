/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     EngineW.cpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../includes/EngineW.hpp"
#include "../../core/srcs/memory/dmemory.h"

#include <iostream>

using namespace DrackEngine;

EngineW::EngineW() : w_isInitialized(false)
{
    memset(&w_coreInfos, 0, sizeof(CoreInfos));
    memset(&w_engine, 0, sizeof(Engine));
    Init();
}

EngineW::~EngineW()
{
    if (w_isInitialized)
    {
        Shutdown();
    }
    print_memory_usage("Exit");
}

void EngineW::DrawUI()
{
    engineButtons.DrawUpButtons();
}

static void UICallbackWrapper(void* userData)
{
    EngineW* engine = static_cast<EngineW*>(userData);
    engine->DrawUI();
}

bool EngineW::Init()
{
    DE_DEBUG("w_isInitialized: %d", w_isInitialized);
    if (w_isInitialized)
    {
        return false;
    }

    initialize_memory();
    if (!dr_init(&w_engine, &w_coreInfos))
    {
        DE_DEBUG("Failed to initialize engine 1");
        return false;
    }

    // Init for resize screen
    w_engine.uiCallback = UICallbackWrapper;
    w_engine.uiUserData = this;
    engineButtons.setEngineRef(&w_engine);

    w_uiLayer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    w_isInitialized = true;
    return true;
}

void EngineW::Update()
{
    if (!w_isInitialized)
        return;
    
    //*******************************************************************************//
    // Draw Workspace
	Camera3D *camera = &w_engine.allCameras->camera00.camera3D;

	if (w_engine.allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE)
	{
		update_camera(camera);
	}
	control_main_panel(&w_engine, camera);
    //*******************************************************************************//

    dr_update(&w_engine, &w_coreInfos);

    if (w_engine.resizeCppCt == true)
    {
        RenderTexture2D newLayer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        BeginTextureMode(newLayer);
            ClearBackground(BLANK);
            DrawTextureRec(w_uiLayer.texture,
                (Rectangle){ 0, 0, (float)w_uiLayer.texture.width, (float)-w_uiLayer.texture.height },
                (Vector2){ 0, 0 },
                WHITE);
        EndTextureMode();
        
        // Recreate the camera 03 texture during resize
        BeginTextureMode(w_engine.allCameras->camera03.textForCam);
            ClearBackground(CLITERAL(Color){ 105, 104, 111, 188 });
            BeginMode2D(w_engine.allCameras->camera03.camera2D);
                engineButtons.DrawUpButtons();
            EndMode2D();
        EndTextureMode();

        UnloadRenderTexture(w_uiLayer);
        w_uiLayer = newLayer;
        
        w_engine.resizeCppCt = false;
    }
    else
    {
        // Mount UI
        BeginTextureMode(w_uiLayer);
            ClearBackground(BLANK);
            engineButtons.DrawUpButtons();
        EndTextureMode();
    }
}

void EngineW::Shutdown()
{
    if (!w_isInitialized)
        return;

    UnloadRenderTexture(w_uiLayer);

    dr_exit(&w_engine, &w_coreInfos);
    shutdown_memory();
    w_isInitialized = false;
}

//******************************************************************************//
//******************************************************************************//
//***                              EngineButtons                             ***//
//******************************************************************************//
//******************************************************************************//

EngineButtons::EngineButtons(void)
{

}

EngineButtons::~EngineButtons(void)
{

}

void	EngineButtons::setEngineRef(Engine *engine)
{
    engineRef = engine;

    setPlayButton();
    setStopButton();
}

void	EngineButtons::setPlayButton(void)
{
    play.initButton((Vector2){engineRef->screenSize.x /2 - 15, 2}, (Vector2){25, 25}, RED, WHITE, "../assets/buttons/play_00.png", "", 0.085);
	play.setTextureHover(LoadTexture("../assets/buttons/play_00_selected.png"));
	play.setTextureClick(LoadTexture("../assets/buttons/play_00_selected.png"));
}

void	EngineButtons::setStopButton(void)
{
    stop.initButton((Vector2){engineRef->screenSize.x /2 + 15, 2}, (Vector2){25, 25}, RED, WHITE, "../assets/buttons/stop_00.png", "", 0.085);
	stop.setTextureHover(LoadTexture("../assets/buttons/stop_00_selected.png"));
	stop.setTextureClick(LoadTexture("../assets/buttons/stop_00_selected.png"));
}

void	EngineButtons::DrawUpButtons(void)
{
    if (IsWindowResized() || IsWindowMaximized() || IsWindowFocused())
    {
        Vector2 playPos = (Vector2){ engineRef->screenSize.x /2 - 15, 2 };
        Vector2 stopPos = (Vector2){ engineRef->screenSize.x /2 + 15, 2 };

        play.setPosition(playPos);
        stop.setPosition(stopPos);
    }

    Rectangle rec03 = engineRef->allCameras->camera03.rectForCam;
	BeginTextureMode(engineRef->allCameras->camera03.textForCam);
		ClearBackground(CLITERAL(Color){ 105, 104, 111, 188 });
		BeginMode2D(engineRef->allCameras->camera03.camera2D);

            play.draw();
            stop.draw();

		EndMode2D();
	EndTextureMode();
}
