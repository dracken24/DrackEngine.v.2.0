/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:      menu_functions.c           *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "../../../includes/Config/menus.h"
#include "../../utility/text_entry.h"

void	mount_all_cameras_engine(Engine *engine);
void	draw_cameras_textures(Engine *engine);

#define CAM07_BORDER_TICK 8
#define CAM07_BORDER_COLOR VERRYDARKGRAY
#define CAM07_MAIN_TEXT_COLOR DARKBLUE
#define CAM07_CLEAR_BACKGROUND GRAYPURPLE
#define CAM07_SPACING 1
#define CAM07_DEFAULT_FONT engine->fonts.defaultFont

typedef struct FilesNew
{
	TextBox	textBoxTest;
}	FilesNew;

FilesNew files_new;
bl8 refresh_frame = true;

extern Engine *g_engine;

//******************************************************************************//
//***                              Files Menu                                ***//
//******************************************************************************//

void	init_all_other_windows_textBox(void)
{
	Vector2 camPosition;

	Rectangle rec = { 20, 65, 200, 22};
	files_new.textBoxTest = create_textBox(rec, 64);
}

void	destroy_all_other_windows_textBox(void)
{
	destroy_textBox(&files_new.textBoxTest);
}

void    quit_menu_window(Engine *engine)
{
	switch (engine->allStates.currentStateView)
	{
		case STATE_VIEW_FILES_NEW_PROJECT:
			files_new.textBoxTest.text[0] = '\0';
			files_new.textBoxTest.textSize = 0;
			break;
		case STATE_VIEW_FILES_OPEN_PROJECT:
			break;
		case STATE_VIEW_FILES_SAVE:
			break;
		case STATE_VIEW_FILES_SAVE_AS:
			break;
		case STATE_VIEW_FILES_EXPORT:
			break;
		case STATE_VIEW_EDIT_UNDO:
			break;
		case STATE_VIEW_EDIT_REDO:
			break;
		case STATE_VIEW_EDIT_CUT:
			break;
		case STATE_VIEW_EDIT_COPY:
			break;
		case STATE_VIEW_EDIT_PASTE:
			break;
		case STATE_VIEW_SETTINGS_LANGUAGE:
			break;
		case STATE_VIEW_SETTINGS_THEME:
			break;
		case STATE_VIEW_SETTINGS_OPTIONS:
			break;
		case STATE_VIEW_HELP_ABOUT:
			break;
		case STATE_VIEW_HELP_SUPPORT:
			break;
		case STATE_VIEW_HELP_DOCUMENTATION:
			break;
		
		default:
			break;
	}
	engine->allStates.lastStateView = engine->allStates.currentStateView;
	engine->allStates.currentStateView = STATE_VIEW_ENGINE;
	SetWindowSize(engine->screenSize.x, engine->screenSize.y);
}

void    keys_events(Engine *engine)
{
	if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
	{
		quit_menu_window(engine);
	}
}

void    menu_files_new(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = engine->allCameras->camera07;
	Rectangle rect = camera_07.rectForCam;

	keys_events(engine);

	Rectangle adjust = {rect.x, rect.y, 0, 0};

	update_textBox(&files_new.textBoxTest, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current texture camera 07
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "New Project", (Vector2){rect.width / 2 - MeasureText("New Project", 40) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Name", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(files_new.textBoxTest, CAM07_DEFAULT_FONT, CAM07_MAIN_TEXT_COLOR, CAM07_SPACING, (intptr_t)NULL);

		EndMode2D();
	EndTextureMode();

	// Draw camera 07 texture
	BeginDrawing();

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		DrawTextureRec(camera_07.textForCam.texture,
					(Rectangle){0, 0, camera_07.rectForCam.width, -camera_07.rectForCam.height},
					(Vector2){rect.x, rect.y},
					WHITE);

	EndDrawing();
}

void    menu_files_open(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Open Project !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_files_save(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Save !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_files_save_as(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Save as !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_files_export(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Export !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_edit_undo(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Undo !");
	quit_menu_window(engine);
}

void    menu_edit_redo(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Redo !");
	quit_menu_window(engine);
}

void    menu_edit_cut(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Cut !");
	quit_menu_window(engine);
}

void    menu_edit_copy(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Copy !");
	quit_menu_window(engine);
}

void    menu_edit_paste(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Paste !");
	quit_menu_window(engine);
}

//******************************************************************************//
//***                             Settings Menu                              ***//
//******************************************************************************//

void    menu_settings_language(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Language !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_settings_theme(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Theme !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_settings_options(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Options !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_help_about(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "About !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_help_documentation(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Documentation !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}

void    menu_help_support(Engine *engine)
{
	Vector2 mpos = GetMousePosition();
	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current window camera
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Support !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

		EndMode2D();
	EndTextureMode();

	BeginDrawing();

		NeedBy3DCam camera_07 = engine->allCameras->camera07;
		Rectangle rect = camera_07.rectForCam;

		rect.x = engine->screenSize.x / 2 - rect.width /2;
		rect.y = engine->screenSize.y / 2 - rect.height /2;

		draw_rectangle_borders(rect, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		camera_07.rectForCam.height *= -1;
		DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){rect.x, rect.y}, WHITE);

	EndDrawing();
}
