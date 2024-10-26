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
    // DE_DEBUG("Win Size x: %f y: %f mouse pos x: %f y: %f", engine->screenSizeWindow.x, engine->screenSizeWindow.y, mpos.x, mpos.y);
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("New Project !", 20, 20, 20, PINK);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_files_open(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Open !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Open Project !", 20, 20, 20, BORDER_COLOR);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_files_save(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Save !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Save !", 20, 20, 20, YELLOW);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_files_save_as(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Save as !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Save as !", 20, 20, 20, BLUE);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_files_export(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Export !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Export !", 20, 20, 20, BLUE);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
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
    // DE_DEBUG("Option selected: %s", "Theme !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Language !", 20, 20, 20, PINK);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_settings_theme(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Theme !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Theme !", 20, 20, 20, BLUE);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_settings_options(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Options !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Options !", 20, 20, 20, RED);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_help_about(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "About !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("About !", 20, 20, 20, GREEN);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_help_documentation(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Documentation !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Documentation !", 20, 20, 20, RED);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}

void    menu_help_support(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Support !");
    keys_events(engine);

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Support !", 20, 20, 20, PURPLE);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, BORDER_COLOR, BORDER_THICK);
    EndDrawing();
}
