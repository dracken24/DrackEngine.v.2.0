/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher  PAR: Dracken24 *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:          27-10-2024             *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:       settings_project.c        *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"

SettingsProject g_settings_project;

void    settings_project_init(void)
{
    Rectangle rec = { 20, 65, 300, 22};
	g_settings_project.testEntry = create_textBox(rec, 64);
}

void    settings_project_update(Engine *engine)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = engine->allCameras->camera07;
	Rectangle rect = camera_07.rectForCam;

	if (window_in_operation == false)
	{
		settings_project_init();
		window_in_operation = true;
	}

	keys_events(engine);

	Rectangle adjust = {rect.x, rect.y, 0, 0};

	update_textBox(&g_settings_project.testEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current texture camera 07
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Settings Project", (Vector2){rect.width / 2 - MeasureText("Settings Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			DrawTextEx(CAM07_DEFAULT_FONT, "Test TextEntry", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_settings_project.testEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);

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

void    settings_project_clean(void)
{
    g_settings_project.testEntry.text[0] = '\0';
	g_settings_project.testEntry.textSize = 0;
}

void    settings_project_destroy(void)
{
    destroy_textBox(&g_settings_project.testEntry);
}
