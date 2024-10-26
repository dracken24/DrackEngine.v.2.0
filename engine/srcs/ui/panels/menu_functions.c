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

#define CAM07_BORDER_TICK 8
#define CAM07_BORDER_COLOR DARKGREEN
#define CAM07_MAIN_TEXT_COLOR DARKBLUE
#define CAM07_SPACING 1
#define CAM07_DEFAULT_FONT engine->fonts.defaultFont

bl8 refresh_frame = true;

//******************************************************************************//
//***                              Files Menu                                ***//
//******************************************************************************//

void    quit_menu_window(Engine *engine)
{
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
    keys_events(engine);

	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(GRAY);
		BeginMode2D(engine->allCameras->camera07.camera2D);

            DrawTextEx(CAM07_DEFAULT_FONT, "New Project !", (Vector2){20, 20}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

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

void    menu_files_open(Engine *engine)
{
    Vector2 mpos = GetMousePosition();
    keys_events(engine);

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
