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

# include "../../includes/engine.h"
# include "../../includes/struct_globale.h"
# include "../../includes/Config/menus.h"

# include <fcntl.h>
# include "../../../library/extern/raylib/src/rlgl.h" 


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
	if (IsKeyPressed(KEY_M))
	{
		print_memory_usage("Update");
	}
}

void    draw_rectangle_borders(Rectangle rectangle, Color color, int thickness)
{
	DrawLineEx((Vector2){rectangle.x, rectangle.y}, (Vector2){rectangle.x + rectangle.width, rectangle.y}, thickness, color); // Line up
	DrawLineEx((Vector2){rectangle.x + rectangle.width, rectangle.y + rectangle.height}, (Vector2){rectangle.x, rectangle.y + rectangle.height}, thickness, color); // Line down
	DrawLineEx((Vector2){rectangle.x + rectangle.width, rectangle.y}, (Vector2){rectangle.x + rectangle.width, rectangle.y + rectangle.height}, thickness, color); // Line right
	DrawLineEx((Vector2){rectangle.x, rectangle.y + rectangle.height}, (Vector2){rectangle.x, rectangle.y}, thickness, color); // Line left
}

void    ftControlMainPanel(Engine *engine)
{
	
}

void    update_main_view(Engine *engine)
{
//--------------------------------------------------------------------------------------
// Update
//----------------------------------------------------------------------------------
	// UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FREE);
	//** Drawning **//

	// Draw Workspace
	Rectangle rec00 = engine->allCameras->camera00.rectForCam;
	BeginTextureMode(engine->allCameras->camera00.textForCam);
		ClearBackground(LIGHTGRAY);
		BeginMode3D(engine->allCameras->camera00.camera3D);

			ftControlMainPanel(engine);
			// DrawText("Workspace !", 20, 20, 20, BLUE);

		EndMode3D();

	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side up
	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
	BeginTextureMode(engine->allCameras->camera01.textForCam);
		ClearBackground(DARKGRAY);
		BeginMode2D(engine->allCameras->camera01.camera2D);

			// ftSideUpMenu2D(game);
			DrawText("Control Panel side up !", rec01.width / 2 - MeasureText("Control Panel side up !", 20) / 2, rec01.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side down
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	BeginTextureMode(engine->allCameras->camera02.textForCam);
		ClearBackground(DARKGRAY2);
		BeginMode2D(engine->allCameras->camera02.camera2D);

			// ftSideDownMenu3D(game);
			DrawText("Control Panel side down !", rec02.width / 2 - MeasureText("Control Panel side down !", 20) / 2, rec02.height / 2 - 10, 20, BLUE);
		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel Up
	Rectangle rec03 = engine->allCameras->camera03.rectForCam;
	BeginTextureMode(engine->allCameras->camera03.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera03.camera2D);

			ftUpMenu2D(engine, &engine->allCameras->camera03.camera2D);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Hyerarchy Left
	Rectangle rec04 = engine->allCameras->camera04.rectForCam;
	BeginTextureMode(engine->allCameras->camera04.textForCam);
		ClearBackground(DARKGRAY3);
		BeginMode2D(engine->allCameras->camera04.camera2D);

			DrawText("Hyerarchy Left !", rec04.width / 2 - MeasureText("Hyerarchy Left !", 20) / 2, rec04.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Console Log center down
	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	BeginTextureMode(engine->allCameras->camera05.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera05.camera2D);

			DrawText("Console Log center down !", rec05.width / 2 - MeasureText("Console Log center down !", 20) / 2, rec05.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw render textures to the screen for all cameras
	BeginDrawing();
		ClearBackground(BLACK);
		
		Rectangle rec_00 = engine->allCameras->camera00.rectForCam;
		Rectangle rec_01 = engine->allCameras->camera01.rectForCam;
		Rectangle rec_02 = engine->allCameras->camera02.rectForCam;
		Rectangle rec_03 = engine->allCameras->camera03.rectForCam;
		Rectangle rec_04 = engine->allCameras->camera04.rectForCam;
		Rectangle rec_05 = engine->allCameras->camera05.rectForCam;

		rec_00.height *= -1;
		rec_01.height *= -1;
		rec_02.height *= -1;
		rec_03.height *= -1;
		rec_04.height *= -1;
		rec_05.height *= -1;

		DrawTextureRec(engine->allCameras->camera00.textForCam.texture, rec_00, (Vector2){rec_00.x, rec_00.y}, WHITE);
		DrawTextureRec(engine->allCameras->camera01.textForCam.texture, rec_01, (Vector2){rec_01.x, rec_01.y}, WHITE);
		DrawTextureRec(engine->allCameras->camera02.textForCam.texture, rec_02, (Vector2){rec_02.x, rec_02.y}, WHITE);
		DrawTextureRec(engine->allCameras->camera03.textForCam.texture, rec_03, (Vector2){rec_03.x, rec_03.y}, WHITE);
		DrawTextureRec(engine->allCameras->camera04.textForCam.texture, rec_04, (Vector2){rec_04.x, rec_04.y}, WHITE);
		DrawTextureRec(engine->allCameras->camera05.textForCam.texture, rec_05, (Vector2){rec_05.x, rec_05.y}, WHITE);

		rec_00.height *= -1;
		rec_01.height *= -1;
		rec_02.height *= -1;
		rec_03.height *= -1;
		rec_04.height *= -1;
		rec_05.height *= -1;

		draw_rectangle_borders(rec_00, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(rec_01, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(rec_02, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(rec_03, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(rec_04, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(rec_05, BORDER_COLOR, BORDER_THICK);

		// draw_rectangle_borders(rec_00, BLUE, 3);
		// draw_rectangle_borders(rec01, RED, 3);
		// draw_rectangle_borders(rec02, PURPLE, 3);
		// draw_rectangle_borders(rec03, GREEN, 3);
		// draw_rectangle_borders(rec04, ORANGE, 3);
		// draw_rectangle_borders(rec05, DARKPURPLE2, 3);

		// Rectangle test = (Rectangle){100, 100, 200, 200};
		// draw_rectangle_borders(test, RED, 3);

		ftDrawDropdownMenu(engine);
	EndDrawing();
}

ViewState   state_for_window_resize = VIEW_MAIN;

void    dr_update(Engine *engine)
{
	

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
		switch(engine->currentView)
        {
            case VIEW_MAIN:
				input_events(engine);
				window_events(engine);
				update_main_view(engine);
                break;
            case VIEW_NEW_PROJECT:
                menu_files_new(engine);
                break;
            case VIEW_OPEN_PROJECT:
                menu_files_open(engine);
                break;
        }
	}
}
