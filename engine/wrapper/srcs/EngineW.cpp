#include "../includes/EngineW.hpp"
#include "../../core/srcs/memory/dmemory.h"

#include <iostream>

using namespace DrackEngine;

EngineW::EngineW() : w_isInitialized(false)
{
    // Initialisation des membres à zéro
    memset(&coreInfos, 0, sizeof(CoreInfos));
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

// void	EngineW::initButtonsMenuUp(void)
// {
// 	w_engine.buttonsMenuUp.play = button_init((Vector2){w_engine.screenSize.x /2 - 15, 2}, (Vector2){25, 25}, RED, WHITE, "../assets/buttons/play_00.png", "", 0.085, 0);
// 	button_set_texture(&w_engine.buttonsMenuUp.play, LoadTexture("../assets/buttons/play_00.png"));
// 	w_engine.buttonsMenuUp.play.texture_hover = LoadTexture("../assets/buttons/play_00_selected.png");
// 	w_engine.buttonsMenuUp.play.texture_click = LoadTexture("../assets/buttons/play_00_selected.png");
// 	w_engine.buttonsMenuUp.stop = button_init((Vector2){w_engine.screenSize.x /2 + 15, 2}, (Vector2){25, 25}, RED, WHITE, "../assets/buttons/stop_00.png", "", 0.085, 0);
// 	button_set_texture(&w_engine.buttonsMenuUp.stop, LoadTexture("../assets/buttons/stop_00.png"));
// 	w_engine.buttonsMenuUp.stop.texture_hover = LoadTexture("../assets/buttons/stop_00_selected.png");
// 	w_engine.buttonsMenuUp.stop.texture_click = LoadTexture("../assets/buttons/stop_00_selected.png");
// 	// DE_DEBUG("Play texture : %f, %f", engine->buttonsMenuUp.play->texture.width, engine->buttonsMenuUp.play->texture.height);

// }

bool EngineW::Init()
{
    DE_DEBUG("w_isInitialized: %d", w_isInitialized);
    if (w_isInitialized)
    {
        return false;
    }

    initialize_memory();
    if (!dr_init(&w_engine, &coreInfos))
    {
        DE_DEBUG("Failed to initialize engine 1");
        return false;
    }

    engineButtons.setEngineRef(&w_engine);

    w_isInitialized = true;
    return true;
}

void EngineW::Update()
{
    if (!w_isInitialized)
        return;
    
    dr_update(&w_engine, &coreInfos);
    engineButtons.DrawUpButtons();
}

void EngineW::Shutdown()
{
    if (!w_isInitialized)
        return;

    dr_exit(&w_engine, &coreInfos);
    shutdown_memory();
    w_isInitialized = false;
}

//******************************************************************************//
//***                              EngineButtons                             ***//
//******************************************************************************//

EngineButtons::EngineButtons(void)
{
    // setPlayButton();
    // setStopButton();
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
    play.draw();
    stop.draw();
}
