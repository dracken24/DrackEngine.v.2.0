/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher  PAR: Dracken24 *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:          27-10-2024             *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         save_project.c          *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"

FilesSave g_files_save;

void    save_project_init(void)
{
    Rectangle rec = { 20, 65, 300, 22};
	g_files_save.testEntry = create_textBox(rec, 64);
}

void    save_project_update(void)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = g_engine->allCameras->camera07;
	Rectangle rect = camera_07.rectForCam;

	if (window_in_operation == false)
	{
		save_project_init();
		window_in_operation = true;
	}

	keys_events(g_engine);

	Rectangle adjust = {rect.x, rect.y, 0, 0};

	update_textBox(&g_files_save.testEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(g_engine);
	draw_cameras_textures(g_engine);

	// Mount current texture camera 07
	BeginTextureMode(g_engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(g_engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Save Project", (Vector2){rect.width / 2 - MeasureText("Save Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			DrawTextEx(CAM07_DEFAULT_FONT, "Test TextEntry", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_save.testEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);

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

void    save_project_clean(void)
{
    g_files_save.testEntry.text[0] = '\0';
	g_files_save.testEntry.textSize = 0;
}

void    save_project_destroy(void)
{
    destroy_textBox(&g_files_save.testEntry);
}
