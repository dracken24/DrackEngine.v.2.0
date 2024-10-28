/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	      27-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 new_project.c          *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"

FilesNew g_files_new;

void	create_new_project(void *userData)
{
	DE_DEBUG("Button Clicked: %s", userData);
}

void    new_project_init(void)
{
	// Entry Types
    Rectangle rect = { 20, 62, 300, 22};
	g_files_new.projectNameEntry = create_textBox(rect, 64);
	rect.y += 52;
	g_files_new.versionEntry = create_textBox(rect, 32);

	// Button Start Project
	rect = g_engine->allCameras->camera07.rectForCam;
	Vector2 size = (Vector2){180, 50};
	Vector2 pos = (Vector2){rect.width / 2  - size.x / 2, rect.height - size.y - 40};
	g_files_new.confirmButton = button_init(pos, size, DARKGRAY, DARKPURPLE2, NULL, "Start Project", 1, 0);
	button_set_bg_hover_color(&g_files_new.confirmButton, GRAY);
	button_set_bg_click_color(&g_files_new.confirmButton, LIGHTGRAY);
	button_set_font(&g_files_new.confirmButton, g_engine->fonts.defaultFont);
	button_set_function(&g_files_new.confirmButton ,*create_new_project, g_files_new.projectNameEntry.text);
}

void    new_project_update(void)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = g_engine->allCameras->camera07;
	Rectangle rect07 = camera_07.rectForCam;

	// WARNING: For Debug
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// DE_WARNING("Mouse pos x: %f y: %f", mpos.x, mpos.y);
		// DE_WARNING("Text Name %s", g_files_new.projectNameEntry.text);
		// DE_WARNING("Text Name %s", g_files_new.versionEntry.text);
	}

	if (window_in_operation == false)
	{
		new_project_init();
		window_in_operation = true;
	}

	keys_events(g_engine);

	Rectangle adjust = {rect07.x, rect07.y, 0, 0};

	// Update TextBox
	update_textBox(&g_files_new.projectNameEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);
	update_textBox(&g_files_new.versionEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(g_engine);
	draw_cameras_textures(g_engine);

	// Mount current texture camera 07
	BeginTextureMode(g_engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(g_engine->allCameras->camera07.camera2D);

			// Draw Title
			DrawTextEx(CAM07_DEFAULT_FONT, "New Project", (Vector2){rect07.width / 2 - MeasureText("New Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

			// Draw and catch Project Name
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Name", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.projectNameEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);

			// Draw and catch Project Version
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Version", (Vector2){20, 92}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.versionEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);
			
			// Draw Confirm Button
			draw_button(&g_files_new.confirmButton, (intptr_t)NULL, 1, 2, CAM07_BORDER_COLOR, (Vector2){rect07.x, rect07.y});

		EndMode2D();
	EndTextureMode();

	// Draw camera 07 texture
	BeginDrawing();

		draw_rectangle_borders(rect07, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		DrawTextureRec(camera_07.textForCam.texture,
					(Rectangle){0, 0, camera_07.rectForCam.width, -camera_07.rectForCam.height},
					(Vector2){rect07.x, rect07.y},
					WHITE);

	EndDrawing();
}

void    new_project_clean(void)
{
    g_files_new.projectNameEntry.text[0] = '\0';
	g_files_new.projectNameEntry.textSize = 0;
}

void    new_project_destroy(void)
{
    destroy_textBox(&g_files_new.projectNameEntry);
	destroy_textBox(&g_files_new.versionEntry);
	button_unload(&g_files_new.confirmButton);
}
