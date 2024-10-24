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
	if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
	{
		switch (engine->currentStateView)
		{
		case 0:
			engine->exitCt = true;
			break;
		default:
			quit_menu_window(engine);
			break;
		}
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

void	use_image(Engine *engine, Rectangle rect, Vector2 offset)
{
	if (engine->testTexture.id == 0)
	{
		Image testImage = LoadImage("../assets/ichigo.png");
		engine->testTexture = LoadTextureFromImage(testImage);
		UnloadImage(testImage);
	}

	DrawTextureRec(
		engine->testTexture,
		(Rectangle){ 0, 0, rect.width, rect.height },
		(Vector2){ offset.x, offset.y },
		WHITE
	);
}

void draw_gizmo_2D(Vector2 position, float scale, Matrix cameraMatrix)
{
	Vector3 right = { cameraMatrix.m0, cameraMatrix.m4, cameraMatrix.m8 };
	Vector3 forward = { cameraMatrix.m2, cameraMatrix.m6, cameraMatrix.m10 };
    Vector3 up = { cameraMatrix.m1, cameraMatrix.m5, cameraMatrix.m9 };
	int thick = 3;
    // Dessiner l'axe X en rouge
    DrawLineEx(position, (Vector2){ position.x - right.x * scale, position.y + right.y * scale }, thick, RED);
    // Dessiner l'axe Y en vert
    DrawLineEx(position, (Vector2){ position.x + up.x * scale, position.y + up.y * scale }, thick, GREEN);
    // Dessiner l'axe Z en bleu (simulé en 2D)
    DrawLineEx(position, (Vector2){ position.x + (right.x + forward.x) * scale, position.y + (right.y + forward.y) * scale }, thick, BLUE);
}

void    update_main_view(Engine *engine)
{
//--------------------------------------------------------------------------------------
// Update
//----------------------------------------------------------------------------------
	// UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FREE);
	//** Drawning **//
	Vector2 zero = (Vector2){0, 0};

	// Draw Workspace
	Rectangle rec00 = engine->allCameras->camera00.rectForCam;
	BeginTextureMode(engine->allCameras->camera00.textForCam);

		ClearBackground(LIGHTGRAY);
		// BeginMode2D(engine->allCameras->camera00.camera2D);
		// 	use_image(engine, rec00, zero);
		// EndMode2D();
		BeginMode3D(engine->allCameras->camera00.camera3D);

			ftControlMainPanel(engine);
			// DrawText("Workspace !", rec00.width / 2 - MeasureText("Workspace !", 20) / 2, rec00.height / 2 - 10, 20, BLUE);

		EndMode3D();

			Matrix cameraMatrix = GetCameraMatrix(engine->allCameras->camera00.camera3D);
        	draw_gizmo_2D((Vector2){ 500, 500  }, 50, cameraMatrix);
		BeginMode2D(engine->allCameras->camera00.camera2D);


			DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);
            DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);

        EndMode2D();

			

	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side up
	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
			
	BeginTextureMode(engine->allCameras->camera01.textForCam);
		ClearBackground(DARKGRAY);
		BeginMode2D(engine->allCameras->camera01.camera2D);

			// ftSideUpMenu2D(game);
			// use_image(engine, rec01, (Vector2){0, 0});
			DrawText("Panel side up !", rec01.width / 2 - MeasureText("Panel side up !", 20) / 2, rec01.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side down
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	BeginTextureMode(engine->allCameras->camera02.textForCam);
		ClearBackground(DARKGRAY2);
		BeginMode2D(engine->allCameras->camera02.camera2D);

			// ftSideDownMenu3D(game);
			// use_image(engine, rec02, zero);
			DrawText("Panel side down !", rec02.width / 2 - MeasureText("Panel side down !", 20) / 2, rec02.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel Up
	Rectangle rec03 = engine->allCameras->camera03.rectForCam;
	BeginTextureMode(engine->allCameras->camera03.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera03.camera2D);

			ftUpMenu2D(engine, &engine->allCameras->camera03.camera2D);
			// use_image(engine, rec03, zero);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Hyerarchy Left
	Rectangle rec04 = engine->allCameras->camera04.rectForCam;
	BeginTextureMode(engine->allCameras->camera04.textForCam);
		ClearBackground(DARKGRAY3);
		BeginMode2D(engine->allCameras->camera04.camera2D);

			// use_image(engine, rec04, zero);
			DrawText("Hyerarchy Left !", rec04.width / 2 - MeasureText("Hyerarchy Left !", 20) / 2, rec04.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Console Log center down
	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	BeginTextureMode(engine->allCameras->camera05.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera05.camera2D);

			// use_image(engine, rec05, zero);
			DrawText("Console Log center down !", rec05.width / 2 - MeasureText("Console Log center down !", 20) / 2, rec05.height / 2 - 10, 20, BLUE);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw render textures to the screen for all cameras
	BeginDrawing();
		ClearBackground(BLACK);
		
		// use rectForCam for each camera
		DrawTextureRec(engine->allCameras->camera00.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera00.rectForCam.width, -engine->allCameras->camera00.rectForCam.height},
					(Vector2){engine->allCameras->camera00.rectForCam.x, engine->allCameras->camera00.rectForCam.y}, 
					WHITE);
		
		DrawTextureRec(engine->allCameras->camera01.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera01.rectForCam.width, -engine->allCameras->camera01.rectForCam.height},
					(Vector2){engine->allCameras->camera01.rectForCam.x, engine->allCameras->camera01.rectForCam.y}, 
					WHITE);
		
		DrawTextureRec(engine->allCameras->camera02.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera02.rectForCam.width, -engine->allCameras->camera02.rectForCam.height},
					(Vector2){engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y}, 
					WHITE);
		
		DrawTextureRec(engine->allCameras->camera03.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera03.rectForCam.width, -engine->allCameras->camera03.rectForCam.height},
					(Vector2){engine->allCameras->camera03.rectForCam.x, engine->allCameras->camera03.rectForCam.y}, 
					WHITE);
		
		DrawTextureRec(engine->allCameras->camera04.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera04.rectForCam.width, -engine->allCameras->camera04.rectForCam.height},
					(Vector2){engine->allCameras->camera04.rectForCam.x, engine->allCameras->camera04.rectForCam.y}, 
					WHITE);
		
		DrawTextureRec(engine->allCameras->camera05.textForCam.texture, 
					(Rectangle){0, 0, engine->allCameras->camera05.rectForCam.width, -engine->allCameras->camera05.rectForCam.height},
					(Vector2){engine->allCameras->camera05.rectForCam.x, engine->allCameras->camera05.rectForCam.y}, 
					WHITE);

		// Draw borders
		draw_rectangle_borders(engine->allCameras->camera00.rectForCam, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(engine->allCameras->camera01.rectForCam, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(engine->allCameras->camera02.rectForCam, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(engine->allCameras->camera03.rectForCam, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(engine->allCameras->camera04.rectForCam, BORDER_COLOR, BORDER_THICK);
		draw_rectangle_borders(engine->allCameras->camera05.rectForCam, BORDER_COLOR, BORDER_THICK);

		ftDrawDropdownMenu(engine);
	EndDrawing();
}

ViewState   state_for_window_resize = STATE_VIEW_ENGINE;

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
		switch(engine->currentStateView)
        {
            case STATE_VIEW_ENGINE:
				input_events(engine);
				window_events(engine);
				update_main_view(engine);
                break;
            case STATE_VIEW_FILES_NEW_PROJECT:
                menu_files_new(engine);
                break;
            case STATE_VIEW_FILES_OPEN_PROJECT:
                menu_files_open(engine);
                break;
			case STATE_VIEW_FILES_SAVE:
                menu_files_save(engine);
                break;
			case STATE_VIEW_FILES_SAVE_AS:
                menu_files_save_as(engine);
                break;
			case STATE_VIEW_FILES_EXPORT:
                menu_files_export(engine);
                break;
			case STATE_VIEW_EDIT_UNDO:
            	menu_edit_undo(engine);
                break;
			case STATE_VIEW_EDIT_REDO:
            	menu_edit_redo(engine);
                break;
			case STATE_VIEW_EDIT_CUT:
            	menu_edit_cut(engine);
                break;
			case STATE_VIEW_EDIT_COPY:
            	menu_edit_copy(engine);
                break;
			case STATE_VIEW_EDIT_PASTE:
            	menu_edit_paste(engine);
                break;
			case STATE_VIEW_SETTINGS_LANGUAGE:
                menu_settings_language(engine);
                break;
			case STATE_VIEW_SETTINGS_THEME:
                menu_settings_theme(engine);
                break;
			case STATE_VIEW_SETTINGS_OPTIONS:
                menu_settings_options(engine);
                break;
			case STATE_VIEW_HELP_ABOUT:
                menu_help_about(engine);
                break;
			case STATE_VIEW_HELP_SUPPORT:
				menu_help_support(engine);
                break;
			case STATE_VIEW_HELP_DOCUMENTATION:
                menu_help_documentation(engine);
                break;
        }
	}
}


