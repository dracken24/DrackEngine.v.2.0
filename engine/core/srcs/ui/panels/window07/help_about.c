/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher  PAR: Dracken24 *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:          27-10-2024             *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         help_about.c            *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"

// SettingsOptions g_settings_options;

void    help_about_init(void)
{
    // Rectangle rec = { 20, 65, 300, 22};
	// g_settings_options.testEntry = create_textBox(rec, 64);
}

void    help_about_update(Engine *engine)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = engine->allCameras->camera07;
	Rectangle rect = camera_07.rectForCam;

	if (window_in_operation == false)
	{
		help_about_init();
		window_in_operation = true;
	}

	keys_events(engine);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current texture camera 07
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "About", (Vector2){rect.width / 2 - MeasureText("About", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

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

void    help_about_clean(void)
{
    // g_settings_options.testEntry.text[0] = '\0';
	// g_settings_options.testEntry.textSize = 0;
}

void    help_about_destroy(void)
{
    // destroy_textBox(&g_settings_options.testEntry);
}
