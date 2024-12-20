/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher  PAR: Dracken24 *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:          27-10-2024             *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         open_project.c          *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"

FilesOpen g_files_open;

void    open_project_init(void)
{
    Rectangle rec = { 20, 65, 300, 22};
	g_files_open.projectNameEntry = create_textBox(rec, 64);
}

void    open_project_update(Engine *engine)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = engine->allCameras->camera07;
	Rectangle rect = camera_07.rectForCam;

	if (window_in_operation == false)
	{
		open_project_init();
		window_in_operation = true;
	}

	keys_events(engine);

	Rectangle adjust = {rect.x, rect.y, 0, 0};

	update_textBox(&g_files_open.projectNameEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);

	// Update all cameras
	mount_all_cameras_engine(engine);
	draw_cameras_textures(engine);

	// Mount current texture camera 07
	BeginTextureMode(engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "Open Project", (Vector2){rect.width / 2 - MeasureText("Open Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Name", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_open.projectNameEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);

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

void    open_project_clean(void)
{
    g_files_open.projectNameEntry.text[0] = '\0';
	g_files_open.projectNameEntry.textSize = 0;
}

void    open_project_destroy(void)
{
    destroy_textBox(&g_files_open.projectNameEntry);
}
