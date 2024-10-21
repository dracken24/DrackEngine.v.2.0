# include "../../includes/engine.h"
# include "../../includes/struct_globale.h"

#define CAMERA_UP_BAR 30

bl8     mouse_on_line_vert      = false;
bl8     mouse_on_line_vert_ct   = false;
bl8     mouse_on_line_hori_right_panels = false;
bl8     mouse_on_line_hori_right_panels_ct   = false;
bl8     mouse_on_line_hori_center_panels = false;
bl8     mouse_on_line_hori_center_panels_ct = false;
Vector2 mouse_on_line_pos     	= (Vector2){0, 0};
Vector2 mouse_on_line_pos_old 	= (Vector2){0, 0};
int     line_hori_width         = 4;
int     line_vert_width         = 4;

void    reset_resize_values(Engine *engine)
{
	mouse_on_line_vert_ct = false;
	mouse_on_line_hori_right_panels_ct = false;
	mouse_on_line_hori_center_panels_ct = false;
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	mouse_on_line_pos = (Vector2){0, 0};
	mouse_on_line_vert = false;
	mouse_on_line_hori_right_panels = false;
	mouse_on_line_hori_center_panels = false;
	line_hori_width = 4;
	line_vert_width = 4;
}

void    adjust_camera_pos_size(NeedBy3DCam *camera, Vector2 pos, Vector2 diff)
{
	if (diff.x != 0 || diff.y != 0)
	{
		camera->rectForCam.width += diff.x;
		camera->rectForCam.height += diff.y;
		camera->textForCam = LoadRenderTexture(camera->rectForCam.width, camera->rectForCam.height);
	}
	camera->rectForCam.x += pos.x;
	camera->rectForCam.y += pos.y;
}

void	set_camera_pos_size(NeedBy3DCam *camera, Vector2 pos, Vector2 size)
{
	if (size.x != 0 || size.y != 0)
	{
		camera->rectForCam.width = size.x;
		camera->rectForCam.height = size.y;
		camera->textForCam = LoadRenderTexture(camera->rectForCam.width, camera->rectForCam.height);
	}
	camera->rectForCam.x = pos.x;
	camera->rectForCam.y = pos.y;
}

void	set_camera_size(NeedBy3DCam *camera, Vector2 size)
{
	camera->rectForCam.width = size.x;
	camera->rectForCam.height = size.y;
	camera->textForCam = LoadRenderTexture(camera->rectForCam.width, camera->rectForCam.height);
}

void	set_camera_pos(NeedBy3DCam *camera, Vector2 pos)
{
	camera->rectForCam.x = pos.x;
	camera->rectForCam.y = pos.y;
}

// Resize screen
void    adjust_menu_camera(Engine *engine)
{
	// DE_DEBUG("Adjust Menu Camera");
	Vector2 diff = (Vector2){engine->screenSize.x - engine->lastScreenSize.x, engine->screenSize.y - engine->lastScreenSize.y};

	adjust_camera_pos_size(&engine->allCameras->camera00, (Vector2){0, 0}, (Vector2){diff.x / 2, diff.y});
	adjust_camera_pos_size(&engine->allCameras->camera01, (Vector2){diff.x / 2, 0}, (Vector2){diff.x / 2, diff.y / 2});
	adjust_camera_pos_size(&engine->allCameras->camera02, (Vector2){diff.x / 2, diff.y / 2}, (Vector2){diff.x / 2, diff.y / 2});
	adjust_camera_pos_size(&engine->allCameras->camera03, (Vector2){0, 0}, (Vector2){diff.x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera04, (Vector2){0, 0}, (Vector2){0, diff.y});
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){0, diff.y}, (Vector2){diff.x / 2, 0});

	// Adjust screen size if too small
	if (engine->screenSize.x < 920)
	{
		SetWindowSize(920, engine->screenSize.y);
		engine->lastScreenSize = engine->screenSize;
		engine->screenSize.x = 920;
		adjust_menu_camera(engine);
	}
	if (engine->screenSize.y < 600)
	{
		SetWindowSize(engine->screenSize.x, 600);
		engine->lastScreenSize = engine->screenSize;
		engine->screenSize.y = 600;
		adjust_menu_camera(engine);
	}

	// Adjust buttons menus
	button_set_position(engine->buttonsMenuUp.play, (Vector2){engine->screenSize.x /2 - 15, 2});
	button_set_position(engine->buttonsMenuUp.stop, (Vector2){engine->screenSize.x /2 + 15, 2});
}

void    adjust_right_panel_vert(Engine *engine, int x)
{
	adjust_camera_pos_size(&engine->allCameras->camera02, (Vector2){x, 0}, (Vector2){-x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera01, (Vector2){x, 0}, (Vector2){-x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera00, (Vector2){0, 0}, (Vector2){x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){0, 0}, (Vector2){x, 0});
}

void    adjust_hori_right_panels(Engine *engine, int y)
{
	adjust_camera_pos_size(&engine->allCameras->camera02, (Vector2){0, y}, (Vector2){0, -y});
	adjust_camera_pos_size(&engine->allCameras->camera01, (Vector2){0, 0}, (Vector2){0, y});
}

void    adjust_hori_center_panels(Engine *engine, int y)
{
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){0, y}, (Vector2){0, -y});
	adjust_camera_pos_size(&engine->allCameras->camera00, (Vector2){0, 0}, (Vector2){0, y});
}

bl8		check_max_min_panels(Engine *engine)
{
	Rectangle *rec00 = &engine->allCameras->camera00.rectForCam;
	Rectangle *rec01 = &engine->allCameras->camera01.rectForCam;
	Rectangle *rec02 = &engine->allCameras->camera02.rectForCam;
	Rectangle *rec03 = &engine->allCameras->camera03.rectForCam;
	Rectangle *rec04 = &engine->allCameras->camera04.rectForCam;
	Rectangle *rec05 = &engine->allCameras->camera05.rectForCam;

	if (rec01->width > engine->screenSize.x - 600)
	{
		DE_INFO("Resize Right 1");
		set_camera_pos_size(&engine->allCameras->camera01, (Vector2){600, rec01->y},
			(Vector2){engine->screenSize.x - 600, rec01->height});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){600, rec02->y},
			(Vector2){engine->screenSize.x - 600, rec02->height});
		set_camera_size(&engine->allCameras->camera00, (Vector2){engine->screenSize.x - rec01->width
			- rec04->width, engine->screenSize.y - rec05->height - CAMERA_UP_BAR});
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, rec05->y},
			(Vector2){engine->screenSize.x - rec01->width - rec04->width, rec05->height});

		reset_resize_values(engine);
		return (true);
	}
	else if (rec01->width < 300)
	{
		DE_INFO("Resize Right 2");
		set_camera_pos_size(&engine->allCameras->camera01, (Vector2){engine->screenSize.x - 300, rec01->y}, (Vector2){300, rec01->height});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){engine->screenSize.x - 300, rec02->y}, (Vector2){300, rec02->height});
		set_camera_size(&engine->allCameras->camera00, (Vector2){engine->screenSize.x - rec01->width -
			rec04->width, engine->screenSize.y - rec05->height - CAMERA_UP_BAR});
		set_camera_size(&engine->allCameras->camera05, (Vector2){engine->screenSize.x - rec01->width - rec04->width, rec05->height});

		reset_resize_values(engine);
		return (true);
	}

	if (rec02->height > engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR)
	{
		DE_INFO("Resize Right 3");
		set_camera_size(&engine->allCameras->camera01, (Vector2){rec01->width, engine->screenSize.y / 4});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){rec02->x, engine->screenSize.y / 4 + CAMERA_UP_BAR},
			(Vector2){rec02->width, engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR});
		reset_resize_values(engine);
		return (true);
	}
	else if (rec02->height < 200)
	{
		DE_INFO("Resize Right 4");
		set_camera_size(&engine->allCameras->camera01, (Vector2){rec01->width, engine->screenSize.y - 200 - CAMERA_UP_BAR});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){rec02->x, rec01->height + rec03->height}, (Vector2){rec02->width, 200});

		reset_resize_values(engine);
		return (true);
	}

	if (rec05->height > engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR)
	{
		DE_INFO("Resize Right 5");
		set_camera_size(&engine->allCameras->camera00, (Vector2){rec00->width, engine->screenSize.y / 4});
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, engine->screenSize.y / 4 + CAMERA_UP_BAR},
			(Vector2){rec05->width, engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR});

		reset_resize_values(engine);
		return (true);
	}
	else if (rec05->height < 70)
	{
		DE_INFO("Resize Right 6");
		set_camera_size(&engine->allCameras->camera00, (Vector2){rec00->width, engine->screenSize.y - 70 - CAMERA_UP_BAR});
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, rec00->height + rec03->height}, (Vector2){rec05->width, 70});

		reset_resize_values(engine);
		return (true);
	}
	return (false);
}

void    resize_right_panel(Engine *engine)
{
	if (check_max_min_panels(engine))
	{
		return;
	}


	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec01.x, rec01.y}, (Vector2){rec01.x, rec01.y + rec01.height}, line_vert_width)
			|| CheckCollisionPointLine(GetMousePosition(), (Vector2){rec02.x, rec02.y}, (Vector2){rec02.x, rec02.y + rec02.height}, line_vert_width))
	{
		// DE_INFO("Mouse Hit Line");
		mouse_on_line_vert_ct = true;
		mouse_on_line_hori_right_panels_ct = false;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	else if (mouse_on_line_vert_ct && !mouse_on_line_hori_right_panels_ct)
	{
		// DE_INFO("Mouse not on line");
		reset_resize_values(engine);
	}

	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec02.x, rec02.y}, (Vector2){rec02.x + rec02.width, rec02.y}, line_hori_width))
	{
		// DE_INFO("Mouse Hit Horizontal Line");
		mouse_on_line_hori_right_panels_ct = true;
		mouse_on_line_vert_ct = false;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	else if (mouse_on_line_hori_right_panels_ct && !mouse_on_line_vert_ct)
	{
		// DE_INFO("Mouse not on line");
		reset_resize_values(engine);
	}

	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec05.x, rec05.y},
		(Vector2){rec05.x + rec05.width, rec05.y}, line_hori_width))
	{
		// DE_INFO("Mouse Hit Horizontal Line");
		mouse_on_line_hori_center_panels_ct = true;
		mouse_on_line_vert_ct = false;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	else if (mouse_on_line_hori_center_panels_ct && !mouse_on_line_vert_ct)
	{
		// DE_INFO("Mouse not on line");
		reset_resize_values(engine);
	}

	if (mouse_on_line_vert_ct)
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			// DE_INFO("Click on line");
			if (mouse_on_line_pos.x != mouse_on_line_pos_old.x)
			{
				// DE_INFO("Mouse move on line");
				adjust_right_panel_vert(engine, mouse_on_line_pos.x - mouse_on_line_pos_old.x);
			}
			line_vert_width = 350;
		}
	}
	else if (mouse_on_line_hori_right_panels_ct)
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			// DE_INFO("Click on line");
			if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
			{
				// DE_INFO("Mouse move on line");
				adjust_hori_right_panels(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
			}
			line_hori_width = 350;
		}
	}
	else if (mouse_on_line_hori_center_panels_ct)
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			// DE_INFO("Click on line");
			if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
			{
				// DE_INFO("Mouse move on line");
				adjust_hori_center_panels(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
			}
			line_hori_width = 350;
		}
	}

	mouse_on_line_pos_old = mouse_on_line_pos;

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		reset_resize_values(engine);
	}
}

void    window_events(Engine *engine)
{
	if (IsWindowResized()) // Resize window events
	{
		engine->lastScreenSize = engine->screenSize;
		engine->screenSize.x = GetScreenWidth();
		engine->screenSize.y = GetScreenHeight();

		adjust_menu_camera(engine);
		// DE_INFO("Window resized in engine");
	}

	resize_right_panel(engine);
}
