# include "../../includes/engine.h"
# include "../../includes/struct_globale.h"

bl8     mouse_on_line_vert      = false;
bl8     mouse_on_line_vert_ct   = false;
bl8     mouse_on_line_hori      = false;
bl8     mouse_on_line_hori_ct   = false;
Vector2 mouse_on_line_pos     	= (Vector2){0, 0};
Vector2 mouse_on_line_pos_old 	= (Vector2){0, 0};
int     line_hori_width         = 4;
int     line_vert_width         = 4;

// Resize screen
void    adjust_menu_camera(Engine *engine)
{
	// DE_DEBUG("Adjust Menu Camera");

	Vector2 diff = (Vector2){engine->screenSize.x - engine->lastScreenSize.x, engine->screenSize.y - engine->lastScreenSize.y};

	Rectangle rec00 = engine->allCameras->camera00.rectForCam;
	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	Rectangle rec03 = engine->allCameras->camera03.rectForCam;
	Rectangle rec04 = engine->allCameras->camera04.rectForCam;

	engine->allCameras->camera04.rectForCam = (Rectangle){rec04.x, rec04.y,
		rec04.width, rec04.height + diff.y};

	engine->allCameras->camera03.rectForCam = (Rectangle){0.0f, 0.0f,
		rec03.width + diff.x, rec03.height};
	engine->allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 30);
	
	engine->allCameras->camera02.rectForCam = (Rectangle){rec02.x + diff.x / 2, rec02.y + diff.y / 2,
		rec02.width + diff.x / 2, rec02.height + diff.y / 2};
	engine->allCameras->camera02.textForCam = LoadRenderTexture(rec02.width, rec02.height);

	engine->allCameras->camera01.rectForCam = (Rectangle){rec01.x + diff.x / 2, rec01.y,
		rec01.width + diff.x / 2, rec01.height + diff.y / 2};
	engine->allCameras->camera01.textForCam = LoadRenderTexture(rec01.width, rec01.height);

	engine->allCameras->camera00.rectForCam = (Rectangle){rec00.x, rec00.y,
		rec00.width + diff.x / 2, rec00.height + diff.y};
	engine->allCameras->camera00.textForCam = LoadRenderTexture(rec00.width, rec00.height);

	// Adjust buttons menus
	button_set_position(engine->buttonsMenuUp.play, (Vector2){engine->screenSize.x /2 - 15, 2});
	button_set_position(engine->buttonsMenuUp.stop, (Vector2){engine->screenSize.x /2 + 15, 2});
}

void    adjust_right_panel_vert(Engine *engine, int x)
{
	engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
	engine->allCameras->camera02.rectForCam.width -= x;
	engine->allCameras->camera02.rectForCam.x += x;

	engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);
	engine->allCameras->camera01.rectForCam.width -= x;
	engine->allCameras->camera01.rectForCam.x += x;

	engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->allCameras->camera00.rectForCam.height);
	engine->allCameras->camera00.rectForCam.width += x;
}

void    adjust_right_panel_hori(Engine *engine, int y)
{
	// DE_INFO("Adjust Right Panel Horisontal");
	// DE_INFO("Y: %d", y);
	// DE_INFO("Height: %d", engine->allCameras->camera02.rectForCam.height);

	engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
	engine->allCameras->camera02.rectForCam.height -= y;
	engine->allCameras->camera02.rectForCam.y += y;

	engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);
	engine->allCameras->camera01.rectForCam.height += y;
}

void    reset_resize_values(Engine *engine)
{
	mouse_on_line_vert_ct = false;
	mouse_on_line_hori_ct = false;
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	mouse_on_line_pos = (Vector2){0, 0};
	mouse_on_line_vert = false;
	mouse_on_line_hori = false;
	line_hori_width = 4;
	line_vert_width = 4;
}

void    resize_right_panel(Engine *engine)
{
	if (engine->allCameras->camera01.rectForCam.width > engine->screenSize.x - 600)
	{
		// DE_INFO("Resize Right Panel Up");
		engine->allCameras->camera01.rectForCam.width = engine->screenSize.x - 601;
		engine->allCameras->camera01.rectForCam.x = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
		engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

		engine->allCameras->camera02.rectForCam.width = engine->screenSize.x - 601;
		engine->allCameras->camera02.rectForCam.x = engine->screenSize.x - engine->allCameras->camera02.rectForCam.width;
		engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height - 30);

		engine->allCameras->camera00.rectForCam.width = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width - engine->allCameras->camera04.rectForCam.width;
		engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->screenSize.y - 30);

		reset_resize_values(engine);
		return;
	}
	else if (engine->allCameras->camera01.rectForCam.width < 300)
	{
		// DE_INFO("Resize Right Panel Down");
		engine->allCameras->camera01.rectForCam.width = 301;
		engine->allCameras->camera01.rectForCam.x = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
		engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

		engine->allCameras->camera02.rectForCam.width = 301;
		engine->allCameras->camera02.rectForCam.x = engine->screenSize.x - engine->allCameras->camera02.rectForCam.width;
		engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height - 30);

		engine->allCameras->camera00.rectForCam.width = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width - engine->allCameras->camera04.rectForCam.width;
		engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->screenSize.y - 30);

		reset_resize_values(engine);
		return;
	}

	if (engine->allCameras->camera02.rectForCam.height > engine->screenSize.y / 4 * 3 - 30)
	{
		// DE_INFO("Resize Right Panel Down");
		engine->allCameras->camera01.rectForCam.height = engine->screenSize.y / 4;
		engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

		engine->allCameras->camera02.rectForCam.height = engine->screenSize.y / 4 * 3 - 30;
		engine->allCameras->camera02.rectForCam.y = engine->screenSize.y / 4 + 30;
		engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
		reset_resize_values(engine);
	}
	else if (engine->allCameras->camera02.rectForCam.height < 200)
	{
		// DE_INFO("Resize Right Panel Up");
		engine->allCameras->camera01.rectForCam.height = engine->screenSize.y / 4 * 3 -30;
		engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

		engine->allCameras->camera02.rectForCam.height = 200;
		engine->allCameras->camera02.rectForCam.y = engine->screenSize.y / 4 * 3;
		engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
		reset_resize_values(engine);
	}

	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec01.x, rec01.y}, (Vector2){rec01.x, rec01.y + rec01.height}, line_vert_width)
			|| CheckCollisionPointLine(GetMousePosition(), (Vector2){rec02.x, rec02.y}, (Vector2){rec02.x, rec02.y + rec02.height}, line_vert_width))
	{
		// DE_INFO("Mouse Hit Line");
		mouse_on_line_vert_ct = true;
		mouse_on_line_hori_ct = false;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	else if (mouse_on_line_vert_ct && !mouse_on_line_hori_ct)
	{
		// DE_INFO("Mouse not on line");
		reset_resize_values(engine);
	}

	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y},
		(Vector2){engine->allCameras->camera02.rectForCam.x + engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.y}, line_hori_width))
	{
		// DE_INFO("Mouse Hit Horizontal Line");
		mouse_on_line_hori_ct = true;
		mouse_on_line_vert_ct = false;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	else if (mouse_on_line_hori_ct && !mouse_on_line_vert_ct)
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
			line_vert_width = 1000;
		}
		mouse_on_line_pos_old = mouse_on_line_pos;
	}
	else if (mouse_on_line_hori_ct)
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			// DE_INFO("Click on line");
			if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
			{
				// DE_INFO("Mouse move on line");
				adjust_right_panel_hori(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
			}
			line_hori_width = 1000;
		}
		mouse_on_line_pos_old = mouse_on_line_pos;
	}

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
