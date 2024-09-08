/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 update.c               *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/engine.h"
# include "../includes/struct_globale.h"

void    draw_msg_intro(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    Vector2 center_text = (Vector2){GetScreenWidth() / 2 - MeasureText("Welcome to the", 40) / 2, GetScreenHeight() / 2 - 75};
    Vector2 center_text2 = (Vector2){GetScreenWidth() / 2 - MeasureText("DrackEngine", 60) / 2, GetScreenHeight() / 2 - 20};

    DrawText("Welcome to the", center_text.x, center_text.y, 40, BLACK);
    DrawText("DrackEngine", center_text2.x, center_text2.y, 60, BLACK);
    
    EndDrawing();
}

void    input_events(Engine *engine)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine->exitCt = true;
    }
}

void    adjust_menu_camera(Engine *engine)
{
    engine->allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 40);
    engine->allCameras->camera03.rectForCam = (Rectangle){0.0f, 0.0f, (float)engine->allCameras->camera03.textForCam.texture.width,
    (float)-engine->allCameras->camera03.textForCam.texture.height};
    
    engine->allCameras->camera02.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3 * 2 - 40);
    engine->allCameras->camera02.rectForCam = (Rectangle){0.0f, 0.0f, (float)engine->allCameras->camera02.textForCam.texture.width,
    (float)-engine->allCameras->camera02.textForCam.texture.height};

    engine->allCameras->camera01.textForCam = LoadRenderTexture(300, engine->screenSize.y / 3);
    engine->allCameras->camera01.rectForCam = (Rectangle){0.0f, 0.0f, (float)engine->allCameras->camera01.textForCam.texture.width,
    (float)-engine->allCameras->camera01.textForCam.texture.height};

    engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->screenSize.x - 300, engine->screenSize.y - 40);
    engine->allCameras->camera00.rectForCam = (Rectangle){0.0f, 0.0f, (float)engine->allCameras->camera00.textForCam.texture.width,
    (float)-engine->allCameras->camera00.textForCam.texture.height};
}

void    window_events(Engine *engine)
{
    if (IsWindowResized()) // Resize window events
    {
        engine->screenSize.x = GetScreenWidth();
        engine->screenSize.y = GetScreenHeight();

        adjust_menu_camera(engine);
    }
}

void	ftDrawBoarders(Engine *engine)
{
	DrawLineEx((Vector2){(float)engine->screenSize.y - 302, 40}, (Vector2){(float)engine->screenSize.x - 302, (float)engine->screenSize.y}, 5, DARKGRAY1);
	DrawLineEx((Vector2){(float)engine->screenSize.x - 2, 0}, (Vector2){(float)engine->screenSize.x - 2, (float)engine->screenSize.y}, 5, DARKGRAY1);
	DrawLineEx((Vector2){(float)engine->screenSize.x - 300, (float)engine->screenSize.y / 3 + 40}, (Vector2){(float)engine->screenSize.x, (float)engine->screenSize.y / 3 + 40}, 5, DARKGRAY1);
	DrawLineEx((Vector2){0, 40}, (Vector2){(float)engine->screenSize.x - 305, 40}, 5, DARKGRAY1);
	DrawLineEx((Vector2){(float)engine->screenSize.x - 300, (float)engine->screenSize.y - 2}, (Vector2){(float)engine->screenSize.x, (float)engine->screenSize.y - 2}, 5, DARKGRAY1);
}

void    draw_events(Engine *engine)
{
//--------------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    // UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FREE);
    //** Drawning **//

    // Draw Workspace
    BeginTextureMode(engine->allCameras->camera00.textForCam);
        ClearBackground(LIGHTGRAY);
        BeginMode3D(engine->allCameras->camera00.camera3D);

            // ftControlMainPanel(engine, &cube01, engine->allCameras);

        EndMode3D();

    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel side up
    BeginTextureMode(engine->allCameras->camera01.textForCam);
        ClearBackground(DARKGRAY);
        BeginMode2D(engine->allCameras->camera01.camera2D);

            // ftSideUpMenu3D(game);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel side down
    BeginTextureMode(engine->allCameras->camera02.textForCam);
        ClearBackground(DARKGRAY2);
        BeginMode2D(engine->allCameras->camera02.camera2D);

            // ftSideDownMenu3D(game);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel Up
    BeginTextureMode(engine->allCameras->camera03.textForCam);
        ClearBackground(DARKGRAY1);
        BeginMode2D(engine->allCameras->camera03.camera2D);

            // ftUpMenu3D(game);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw render textures to the screen for all cameras
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(engine->allCameras->camera00.textForCam.texture, engine->allCameras->camera00.rectForCam, (Vector2){0, 40}, WHITE);
        DrawTextureRec(engine->allCameras->camera01.textForCam.texture, engine->allCameras->camera01.rectForCam, (Vector2){(float)engine->screenSize.x - 300.0f, 40}, WHITE);
        DrawTextureRec(engine->allCameras->camera02.textForCam.texture, engine->allCameras->camera02.rectForCam, (Vector2){(float)engine->screenSize.x - 300.0f, (float)engine->screenSize.y / 3 + 40}, WHITE);
        DrawTextureRec(engine->allCameras->camera03.textForCam.texture, engine->allCameras->camera03.rectForCam, (Vector2){0, 0}, WHITE);
        // ftDrawBoarders(engine);
    EndDrawing();
}

void    dr_update(Engine *engine)
{
    input_events(engine);
    window_events(engine);

    // put intro screen
    if (engine->introCt)
    {
        static double startTime = 0;
        
        if (startTime == 0)
        {
            startTime = GetTime(); // Initialize time
        }
        
        draw_msg_intro();
        
        if (GetTime() - startTime >= 1.0) // Check time passed
        {
            engine->introCt = false;
            startTime = 0; // Reset for future use if needed
        }
    }
    else
    {
        draw_events(engine);
    }
}
