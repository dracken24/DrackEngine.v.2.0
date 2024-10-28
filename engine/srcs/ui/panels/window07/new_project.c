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

void    new_project_init(void)
{
    Rectangle rect07 = { 20, 65, 300, 22};
	g_files_new.projectNameEntry = create_textBox(rect07, 64);

	rect07 = g_engine->allCameras->camera07.rectForCam;
	Vector2 size = (Vector2){180, 50};
	Vector2 pos = (Vector2){rect07.width / 2  - size.x / 2, rect07.height - size.y - 40};
	g_files_new.confirmButton = button_init(pos, size, DARKGRAY, DARKPURPLE2, NULL, "Start Project", 1, 0);
	button_set_bg_hover_color(&g_files_new.confirmButton, GRAY);
	button_set_bg_click_color(&g_files_new.confirmButton, LIGHTGRAY);
	button_set_font(&g_files_new.confirmButton, g_engine->fonts.defaultFont);
}

void    new_project_update(void)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = g_engine->allCameras->camera07;
	Rectangle rect07 = camera_07.rectForCam;

	if (window_in_operation == false)
	{
		new_project_init();
		window_in_operation = true;
	}

	keys_events(g_engine);

	Rectangle adjust = {rect07.x, rect07.y, 0, 0};

	update_textBox(&g_files_new.projectNameEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(g_engine);
	draw_cameras_textures(g_engine);

	// Mount current texture camera 07
	BeginTextureMode(g_engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(g_engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "New Project", (Vector2){rect07.width / 2 - MeasureText("New Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Name", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.projectNameEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);
			// DrawRectangleRec(g_files_new.confirmButton.rect, g_files_new.confirmButton.bg_color);
			draw_button(g_files_new.confirmButton, (intptr_t)NULL, 1, 2, CAM07_BORDER_COLOR, (Vector2){rect07.x, rect07.y});

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
	button_unload(&g_files_new.confirmButton);
}
