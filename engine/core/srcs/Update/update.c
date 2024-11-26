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

#include "../../includes/engine.h"
#include "../../includes/struct_globale.h"
#include "../../includes/Config/menus.h"
#include "../ui/panels/window07/file_dialog.h"
#include "../ui/panels/window07/window07.h"

#include <fcntl.h>
#include "rlgl.h" 
#include "workspace.h"

void    check_mouse_state(Engine *engine);
void    resize_screen(Engine *engine);

// extern FileDialog g_fileDialog;

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
		switch (engine->allStates.currentStateView)
		{
			case STATE_VIEW_ENGINE:
				engine->exitCt = true;
				break;
			// case STATE_VIEW_SUB_WINDOW:
			// 	g_fileDialog.shouldClose = false;
			// 	break;
			default:
				quit_menu_window(engine);
				break;
		}
	}

	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		if (IsKeyPressed(KEY_C))
		{
			change_view(engine, STATE_VIEW_EDIT_COPY, false, null, null);
		}
		else if (IsKeyPressed(KEY_V))
		{
			change_view(engine, STATE_VIEW_EDIT_PASTE, false, null, null);
		}
		else if (IsKeyPressed(KEY_X))
		{
			change_view(engine, STATE_VIEW_EDIT_CUT, false, null, null);
		}
		else if (IsKeyPressed(KEY_Z))
		{
			change_view(engine, STATE_VIEW_EDIT_UNDO, false, null, null);
		}
		else if (IsKeyPressed(KEY_Y))
		{
			change_view(engine, STATE_VIEW_EDIT_REDO, false, null, null);
		}
	}

	// int keyPress = GetKeyPressed();
	// if (keyPress != 0)
	// 	DE_DEBUG("Key Pressed: %d", keyPress);
}

void    draw_rectangle_borders(Rectangle rect, Color color, int thickness)
{
	DrawLineEx((Vector2){rect.x - thickness/2, rect.y}, (Vector2){rect.x + rect.width + thickness/2, rect.y}, thickness, color); // Line up
	DrawLineEx((Vector2){rect.x + rect.width + thickness/2, rect.y + rect.height}, (Vector2){rect.x - thickness/2, rect.y + rect.height}, thickness, color); // Line down
	DrawLineEx((Vector2){rect.x + rect.width, rect.y - thickness/2}, (Vector2){rect.x + rect.width, rect.y + rect.height + thickness/2}, thickness, color); // Line right
	DrawLineEx((Vector2){rect.x, rect.y + rect.height + thickness/2}, (Vector2){rect.x, rect.y - thickness/2}, thickness, color); // Line left
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

void	draw_cameras_textures(Engine *engine)
{
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
	// draw_rectangle_borders(engine->allCameras->camera00.rectForCam, BORDER_COLOR, BORDER_THICK);
	draw_rectangle_borders(engine->allCameras->camera01.rectForCam, BORDER_COLOR, BORDER_THICK);
	draw_rectangle_borders(engine->allCameras->camera02.rectForCam, BORDER_COLOR, BORDER_THICK);
	draw_rectangle_borders(engine->allCameras->camera03.rectForCam, BORDER_COLOR, BORDER_THICK);
	draw_rectangle_borders(engine->allCameras->camera04.rectForCam, BORDER_COLOR, BORDER_THICK);
	draw_rectangle_borders(engine->allCameras->camera05.rectForCam, BORDER_COLOR, BORDER_THICK);

	draw_drop_down_menu(engine);
}

#define MAIN_BG_COLOR	CLITERAL(Color){ 105, 104, 111, 188 }
#define MAIN_BG_COLOR2	CLITERAL(Color){ 96, 96, 100, 188 }
#define MAIN_TEXT_COLOR VERRYDARKGRAY

void	mount_all_cameras_engine(Engine *engine)
{
	// Draw Workspace
	Camera3D *camera = &engine->allCameras->camera00.camera3D;

	if (engine->allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE)
	{
		update_camera(camera);
	}
		control_main_panel(engine, camera);

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side up
	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
			
	BeginTextureMode(engine->allCameras->camera01.textForCam);
		ClearBackground(MAIN_BG_COLOR);
		BeginMode2D(engine->allCameras->camera01.camera2D);

			// ftSideUpMenu2D(game);
			// use_image(engine, rec01, (Vector2){0, 0});
			DrawText("Panel side up !", rec01.width / 2 - MeasureText("Panel side up !", 20) / 2, rec01.height / 2 - 10, 20, MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel side down
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	BeginTextureMode(engine->allCameras->camera02.textForCam);
		ClearBackground(MAIN_BG_COLOR2);
		BeginMode2D(engine->allCameras->camera02.camera2D);

			// ftSideDownMenu3D(game);
			// use_image(engine, rec02, zero);
			DrawText("Panel side down !", rec02.width / 2 - MeasureText("Panel side down !", 20) / 2, rec02.height / 2 - 10, 20, MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Control Panel Up
	Rectangle rec03 = engine->allCameras->camera03.rectForCam;
	BeginTextureMode(engine->allCameras->camera03.textForCam);
		// ClearBackground(MAIN_BG_COLOR);
		BeginMode2D(engine->allCameras->camera03.camera2D);

			up_menu(engine, &engine->allCameras->camera03.camera2D);
			// use_image(engine, rec03, zero);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Draw Hyerarchy Left
	Rectangle rec04 = engine->allCameras->camera04.rectForCam;
	BeginTextureMode(engine->allCameras->camera04.textForCam);
		ClearBackground(MAIN_BG_COLOR2);
		BeginMode2D(engine->allCameras->camera04.camera2D);

			// use_image(engine, rec04, zero);
			DrawText("Hyerarchy Left !", rec04.width / 2 - MeasureText("Hyerarchy Left !", 20) / 2, rec04.height / 2 - 10, 20, MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

//--------------------------------------------------------------------------------------//

	// Console Log center down
	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	BeginTextureMode(engine->allCameras->camera05.textForCam);
		ClearBackground(MAIN_BG_COLOR);
		BeginMode2D(engine->allCameras->camera05.camera2D);

			// use_image(engine, rec05, zero);
			DrawText("Console Log center down !", rec05.width / 2 - MeasureText("Console Log center down !", 20) / 2, rec05.height / 2 - 10, 20, MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();
}

void    update_main_view(Engine *engine)
{
//--------------------------------------------------------------------------------------
// Update
//----------------------------------------------------------------------------------
	
	//** Drawning **//
	mount_all_cameras_engine(engine);

//--------------------------------------------------------------------------------------//

	// Draw render textures to the screen for all cameras
	BeginDrawing();
		draw_cameras_textures(engine);
	EndDrawing();
}

ViewState   state_for_window_resize = STATE_VIEW_ENGINE;

void    dr_update(Engine *engine, CoreInfos const *coreInfos)
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
		engine->mouse.pos = GetMousePosition();
		check_mouse_state(engine);
		// DE_WARNING("Mouse Current State: %d", engine->allStates.currentStateMouse);
		// DE_WARNING("VIEW Current State: %d", engine->allStates.currentStateView);
		// Andle resize in others windows than Build mode
		if (IsWindowResized() && engine->allStates.currentStateView != STATE_VIEW_ENGINE)
		{
			DE_WARNING("Resize window in MOUSE_STATE_ON_OTHER_WINDOW");
			engine->lastScreenSize = engine->screenSize;
			engine->screenSize.x = GetScreenWidth();
			engine->screenSize.y = GetScreenHeight();
			resize_screen(engine);

			Rectangle *rec07 = &engine->allCameras->camera07.rectForCam;
			rec07->x = engine->screenSize.x / 2 - rec07->width / 2;
			rec07->y = engine->screenSize.y / 2 - rec07->height / 2;
		}
		if (refresh_frame)
		{
			DE_WARNING("refresh_frame");
			refresh_frame = false;
			update_main_view(engine);
		}

		// DE_DEBUG("currentStateMouse update.c: %d", engine->allStates.currentStateMouse);

		switch(engine->allStates.currentStateView)
        {
            case STATE_VIEW_ENGINE:
				input_events(engine);
				window_events(engine);
				update_main_view(engine);
                break;
            case STATE_VIEW_FILES_NEW_PROJECT:
                menu_files_new(engine, coreInfos);
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
			case STATE_VIEW_SETTINGS_ENGINE:
                menu_settings_engine(engine);
                break;
			case STATE_VIEW_SETTINGS_PROJECT:
                menu_settings_project(engine);
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
			case STATE_VIEW_SUB_WINDOW:
				menu_files_new(engine, coreInfos);
                break;
        }

		engine->mouse.lastPos = engine->mouse.pos;
	}
}


