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

void    menu_files_new(Engine *engine)
{
    Vector2 mpos = GetMousePosition();
    // DE_DEBUG("Win Size x: %f y: %f mouse pos x: %f y: %f", engine->screenSizeWindow.x, engine->screenSizeWindow.y, mpos.x, mpos.y);
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine->lastView = engine->currentView;
        engine->currentView = VIEW_MAIN;
        SetWindowSize(engine->screenSize.x, engine->screenSize.y);
    }

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
        draw_rectangle_borders(camera_07.rectForCam, RED, BORDER_THICK);
    EndDrawing();
}

void    menu_files_open(Engine *engine)
{
    // DE_DEBUG("Option selected: %s", "Open !");
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine->lastView = engine->currentView;
        engine->currentView = VIEW_MAIN;
        SetWindowSize(engine->screenSize.x, engine->screenSize.y);
    }

    // Camera 05 for other windows
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(DARKGRAY1);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawText("Open Project !", 20, 20, 20, BLUE);

		EndMode2D();
	EndTextureMode();

    BeginDrawing();
        NeedBy3DCam camera_07 = engine->allCameras->camera07;
        camera_07.rectForCam.height *= -1;
        DrawTextureRec(camera_07.textForCam.texture, camera_07.rectForCam, (Vector2){0, 0}, WHITE);
        draw_rectangle_borders(camera_07.rectForCam, RED, BORDER_THICK);
    EndDrawing();
}

void    menu_files_save(void)
{
    DE_DEBUG("Option selected: %s", "Save !");
}

void    menu_files_save_as(void)
{
    DE_DEBUG("Option selected: %s", "Save as !");
}

void    menu_files_export(void)
{
    DE_DEBUG("Option selected: %s", "Export !");
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_edit_undo(void)
{
    DE_DEBUG("Option selected: %s", "Undo !");
}

void    menu_edit_redo(void)
{
    DE_DEBUG("Option selected: %s", "Redo !");
}

void    menu_edit_cut(void)
{
    DE_DEBUG("Option selected: %s", "Cut !");
}

void    menu_edit_copy(void)
{
    DE_DEBUG("Option selected: %s", "Copy !");
}

void    menu_edit_paste(void)
{
    DE_DEBUG("Option selected: %s", "Paste !");
}

//******************************************************************************//
//***                             Settings Menu                              ***//
//******************************************************************************//

void    menu_settings_language(void)
{
    DE_DEBUG("Option selected: %s", "Language !");
}

void    menu_settings_theme(void)
{
    DE_DEBUG("Option selected: %s", "Theme !");
}

void    menu_settings_options(void)
{
    DE_DEBUG("Option selected: %s", "Options !");
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_help_about(void)
{
    DE_DEBUG("Option selected: %s", "About !");
}

void    menu_help_documentation(void)
{
    DE_DEBUG("Option selected: %s", "Documentation !");
}

void    menu_help_support(void)
{
    DE_DEBUG("Option selected: %s", "Support !");
}
