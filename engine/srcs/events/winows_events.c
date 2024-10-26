/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 02-10-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  windows_events.c        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

# include "../../includes/engine.h"

bl8	    skipTurnResize = false;
bl8     mouse_on_line_vert      			= false;
bl8     mouse_on_line_vert_ct   			= false;
bl8     mouse_on_line_vert_hyerarchy      	= false;
bl8     mouse_on_line_vert_hyerarchy_ct  	= false;
bl8     mouse_on_line_hori_right_panels 	= false;
bl8     mouse_on_line_hori_right_panels_ct  = false;
bl8     mouse_on_line_hori_center_panels	= false;
bl8     mouse_on_line_hori_center_panels_ct = false;
bl8	mouse_clicked							= false;
Vector2 mouse_on_line_pos     				= (Vector2){0, 0};
Vector2 mouse_on_line_pos_old 				= (Vector2){0, 0};
int     line_hori_right_width         		= 4;
int     line_vert_right_width         		= 4;
int     line_hori_center_width        		= 4;
int     line_vert_hierarchy_width     		= 4;

void    reset_resize_values(Engine *engine)
{
	mouse_on_line_vert      				= false;
	mouse_on_line_vert_ct   				= false;
	mouse_on_line_vert_hyerarchy      		= false;
	mouse_on_line_vert_hyerarchy_ct   		= false;
	mouse_on_line_hori_right_panels 		= false;
	mouse_on_line_hori_right_panels_ct  	= false;
	mouse_on_line_hori_center_panels 		= false;
	mouse_on_line_hori_center_panels_ct 	= false;
	mouse_on_line_pos 						= (Vector2){0, 0};
	mouse_on_line_pos_old 					= (Vector2){0, 0};
	line_hori_right_width 					= 4;
	line_vert_right_width 					= 4;
	line_hori_center_width         			= 4;
	line_vert_hierarchy_width       		= 4;
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	mouse_clicked = false;
	engine->allStates.blockMouseStates = false;
	// DE_DEBUG("RESET");
}

void	reset_camera_options(Camera2D camera)
{
	camera.offset = (Vector2){0, 0};
	camera.target = (Vector2){0, 0};
	camera.rotation = 0;
	camera.zoom = 1.0f;
}

void	reload_texture(NeedBy3DCam *cam)
{
	UnloadRenderTexture(cam->textForCam);
	cam->textForCam = LoadRenderTexture(cam->rectForCam.width, cam->rectForCam.height);
}

// Add position and size to camera texure and reload texture if size changed
void    adjust_camera_pos_size(NeedBy3DCam *camera, Vector2 pos, Vector2 diff)
{
	camera->rectForCam.x += pos.x;
	camera->rectForCam.y += pos.y;
	if (diff.x != 0 || diff.y != 0)
	{
		camera->rectForCam.width += diff.x;
		camera->rectForCam.height += diff.y;
		reload_texture(camera);

		reset_camera_options(camera->camera2D);
	}
}

// Set position and size to camera texure and reload texture if size changed
void	set_camera_pos_size(NeedBy3DCam *camera, Vector2 pos, Vector2 size)
{
	camera->rectForCam.x = pos.x;
	camera->rectForCam.y = pos.y;
	if (size.x != 0 || size.y != 0)
	{
		camera->rectForCam.width = size.x;
		camera->rectForCam.height = size.y;
		reload_texture(camera);

		reset_camera_options(camera->camera2D);
	}
}

// Set size to camera texure and reload texture
void	set_camera_size(NeedBy3DCam *camera, Vector2 size)
{
	camera->rectForCam.width = size.x;
	camera->rectForCam.height = size.y;
	reload_texture(camera);

	reset_camera_options(camera->camera2D);
}
 
 // Adjust size to camera texure and reload texture
void	adjust_camera_size(NeedBy3DCam *camera, Vector2 size)
{
	camera->rectForCam.width += size.x;
	camera->rectForCam.height += size.y;
	reload_texture(camera);

	reset_camera_options(camera->camera2D);
}

// Set position to camera texure
void	set_camera_pos(NeedBy3DCam *camera, Vector2 pos)
{
	camera->rectForCam.x = pos.x;
	camera->rectForCam.y = pos.y;
}

// Add position to camera texure
void	adjust_camera_pos(NeedBy3DCam *camera, Vector2 pos)
{
	camera->rectForCam.x += pos.x;
	camera->rectForCam.y += pos.y;
}

// Resize screen function
void    resize_screen(Engine *engine)
{
	DE_DEBUG("Adjust Menu Camera");
	if (IsWindowMaximized())
	{
		// DE_DEBUG("Maximize Window");
	}
	else if (IsWindowFocused())
	{
		// DE_DEBUG("Minimize Window");
	}
	
	Vector2 diff = (Vector2){engine->screenSize.x - engine->lastScreenSize.x, engine->screenSize.y - engine->lastScreenSize.y};

	Rectangle *rec01 = &engine->allCameras->camera01.rectForCam;
	Rectangle *rec02 = &engine->allCameras->camera02.rectForCam;
	Rectangle *rec03 = &engine->allCameras->camera03.rectForCam;
	Rectangle *rec04 = &engine->allCameras->camera04.rectForCam;
	Rectangle *rec05 = &engine->allCameras->camera05.rectForCam;

	adjust_camera_pos_size(&engine->allCameras->camera01, (Vector2){diff.x / 3 * 2, 0}, (Vector2){diff.x / 3, diff.y / 2});
	adjust_camera_pos_size(&engine->allCameras->camera02, (Vector2){diff.x / 3 * 2, diff.y / 2}, (Vector2){diff.x / 3, diff.y / 2});
	adjust_camera_pos_size(&engine->allCameras->camera03, (Vector2){0, 0}, (Vector2){diff.x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera04, (Vector2){0, 0}, (Vector2){0, diff.y});
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){0, diff.y}, (Vector2){diff.x / 3 * 2, 0});

	// Adjust screen size if too small
	if (engine->screenSize.x < 920)
	{
		SetWindowSize(920, engine->screenSize.y);
		engine->lastScreenSize = engine->screenSize;
		engine->screenSize.x = 920;
		skipTurnResize = true;
		resize_screen(engine);
	}
	if (engine->screenSize.y < 600)
	{
		SetWindowSize(engine->screenSize.x, 600);
		engine->lastScreenSize = engine->screenSize;
		engine->screenSize.y = 600;
		skipTurnResize = true;
		resize_screen(engine);
	}

	if (rec04->width > engine->screenSize.x - 600)
	{
		DE_WARNING("RESIZE MAX 1");
		
		rec05->width = 300;
		rec04->width = engine->screenSize.x - 600;

		rec05->x = rec04->width;

		reload_texture(&engine->allCameras->camera04);
		reload_texture(&engine->allCameras->camera05);
	}
	else if (rec01->width > engine->screenSize.x - 600)
	{
		DE_WARNING("RESIZE MAX 2");
		
		rec01->width = engine->screenSize.x - 600;
		rec02->width = engine->screenSize.x - 600;
		rec04->width = 300;
		rec05->width = 300;

		rec01->x = 600;
		rec02->x = 600;
		rec05->x = rec04->width;

		reload_texture(&engine->allCameras->camera01);
		reload_texture(&engine->allCameras->camera02);
		reload_texture(&engine->allCameras->camera04);
		reload_texture(&engine->allCameras->camera05);
	}
	// DE_DEBUG("engine screen size x: %f y: %f", engine->screenSize.x, engine->screenSize.y);

	// Adjust buttons menus
	button_set_position(engine->buttonsMenuUp.play, (Vector2){engine->screenSize.x /2 - 15, 2});
	button_set_position(engine->buttonsMenuUp.stop, (Vector2){engine->screenSize.x /2 + 15, 2});
}

void    adjust_right_panel_vert(Engine *engine, int x)
{
	DE_DEBUG("Adjust Right Panel Vert");
	adjust_camera_pos(&engine->allCameras->camera02, (Vector2){x, 0});
	adjust_camera_pos(&engine->allCameras->camera01, (Vector2){x, 0});
	adjust_camera_size(&engine->allCameras->camera02, (Vector2){-x, 0});
	adjust_camera_size(&engine->allCameras->camera01, (Vector2){-x, 0});
	adjust_camera_size(&engine->allCameras->camera05, (Vector2){x, 0});

	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	if (rec05.width < 200)
	{
		DE_INFO("Resize Right 7");
		adjust_camera_pos(&engine->allCameras->camera02, (Vector2){-x, 0});
		adjust_camera_pos(&engine->allCameras->camera01, (Vector2){-x, 0});
		adjust_camera_size(&engine->allCameras->camera02, (Vector2){x, 0});
		adjust_camera_size(&engine->allCameras->camera01, (Vector2){x, 0});
		adjust_camera_size(&engine->allCameras->camera05, (Vector2){-x, 0});
		skipTurnResize = true;

		reset_resize_values(engine);
	}
}

void    adjust_hori_right_panels(Engine *engine, int y)
{
	adjust_camera_size(&engine->allCameras->camera01, (Vector2){0, y});
	adjust_camera_size(&engine->allCameras->camera02, (Vector2){0, -y});
	adjust_camera_pos(&engine->allCameras->camera02, (Vector2){0, y});
}

void    adjust_hori_center_panels(Engine *engine, int y)
{
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){0, y}, (Vector2){0, -y});
}

void	adjust_vert_hyerarchy_panels(Engine *engine, int x)
{
	// DE_WARNING("Adjust Vert Hyerarchy Panels");
	adjust_camera_size(&engine->allCameras->camera04, (Vector2){x, 0});
	adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){x, 0}, (Vector2){-x, 0});

	Rectangle rec04 = engine->allCameras->camera04.rectForCam;
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	Rectangle rec05 = engine->allCameras->camera05.rectForCam;
	// DE_WARNING("rec04.width: %f", rec04.width);
	if (rec04.width < 200 || rec05.width < 200)
	{
		// DE_INFO("Resize Right 7");
		adjust_camera_size(&engine->allCameras->camera04, (Vector2){-x, 0});
		adjust_camera_pos_size(&engine->allCameras->camera05, (Vector2){-x, 0}, (Vector2){x, 0});
		skipTurnResize = true;

		reset_resize_values(engine);
	}
}

bl8		check_max_min_panels(Engine *engine)
{
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
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, rec05->y},
			(Vector2){engine->screenSize.x - rec01->width - rec04->width, rec05->height});

		reset_resize_values(engine);
		return (true);
	}
	else if (rec01->width < 300)
	{
		// DE_INFO("Resize Right 2");
		set_camera_pos_size(&engine->allCameras->camera01, (Vector2){engine->screenSize.x - 300, rec01->y}, (Vector2){300, rec01->height});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){engine->screenSize.x - 300, rec02->y}, (Vector2){300, rec02->height});
		set_camera_size(&engine->allCameras->camera05, (Vector2){engine->screenSize.x - rec01->width - rec04->width, rec05->height});

		reset_resize_values(engine);
		return (true);
	}

	if (rec02->height > engine->screenSize.y - 100 - CAMERA_UP_BAR)
	{
		// DE_INFO("Resize Right 3");
		set_camera_size(&engine->allCameras->camera01, (Vector2){rec01->width, 100});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){rec02->x, 100 + CAMERA_UP_BAR},
			(Vector2){rec02->width, engine->screenSize.y - 100 - CAMERA_UP_BAR});
		reset_resize_values(engine);
		return (true);
	}
	else if (rec02->height < 100)
	{
		// DE_INFO("Resize Right 4");
		set_camera_size(&engine->allCameras->camera01, (Vector2){rec01->width, engine->screenSize.y - 100 - CAMERA_UP_BAR});
		set_camera_pos_size(&engine->allCameras->camera02, (Vector2){rec02->x, rec01->height + rec03->height}, (Vector2){rec02->width, 100});

		reset_resize_values(engine);
		return (true);
	}

	if (rec05->height > engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR)
	{
		// DE_INFO("Resize Right 5");
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, engine->screenSize.y / 4 + CAMERA_UP_BAR},
			(Vector2){rec05->width, engine->screenSize.y / 4 * 3 - CAMERA_UP_BAR});

		reset_resize_values(engine);
		return (true);
	}
	else if (rec05->height < 70)
	{
		// DE_INFO("Resize Right 6");
		set_camera_pos_size(&engine->allCameras->camera05, (Vector2){rec05->x, engine->screenSize.y - 70}, (Vector2){rec05->width, 70});

		reset_resize_values(engine);
		return (true);
	}

	return (false);
}

void    resize_right_panel(Engine *engine)
{
	if (skipTurnResize)
	{
		skipTurnResize = false;
		return;
	}
	if (check_max_min_panels(engine))
	{
		return;
	}

	Rectangle rec01 = engine->allCameras->camera01.rectForCam;
	Rectangle rec02 = engine->allCameras->camera02.rectForCam;
	Rectangle rec04 = engine->allCameras->camera04.rectForCam;
	Rectangle rec05 = engine->allCameras->camera05.rectForCam;

	// Line verticale separation 00/05 et 01/02 panels
	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec01.x, rec01.y}, (Vector2){rec01.x, rec01.y + rec01.height}, line_vert_right_width)
			|| CheckCollisionPointLine(GetMousePosition(), (Vector2){rec02.x, rec02.y}, (Vector2){rec02.x, rec02.y + rec02.height}, line_vert_right_width))
	{
		// DE_INFO("Mouse Hit Line Right vertical 01");
		mouse_on_line_vert_ct = true;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	// Line horizontale separation 01 et 02 panels
	else if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec02.x, rec02.y},
		(Vector2){rec02.x + rec02.width, rec02.y}, line_hori_right_width))
	{
		// DE_INFO("Mouse Hit Horizontal Line Right 02");
		mouse_on_line_hori_right_panels_ct = true;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	// Line horizontale separation 00 et 05 panels
	else if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec05.x, rec05.y},
		(Vector2){rec05.x + rec05.width, rec05.y}, line_hori_center_width))
	{
		// DE_INFO("Mouse Hit Horizontal central Line");
		mouse_on_line_hori_center_panels_ct = true;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	// Line Verticale separation 04 et 00/05 panels
	else if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec04.x + rec04.width, rec04.y},
		(Vector2){rec04.x + rec04.width, rec04.y + rec04.height}, line_vert_hierarchy_width))
	{
		// DE_INFO("Mouse Hit verticale Line hyerarchy");
		mouse_on_line_vert_hyerarchy_ct = true;
		mouse_on_line_pos = GetMousePosition();
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	else if (mouse_on_line_vert_hyerarchy_ct || mouse_on_line_hori_center_panels_ct
		|| mouse_on_line_hori_right_panels_ct || mouse_on_line_vert_ct)
	{
		// DE_INFO("Mouse not on line");
		reset_resize_values(engine);
	}

	if (mouse_clicked == true)
	{
		if (mouse_on_line_vert_ct)
		{
			// DE_INFO("Click on line Vertical Right");
			line_vert_right_width = 500;
			engine->allStates.blockMouseStates = true;
			if (mouse_on_line_pos.x != mouse_on_line_pos_old.x)
			{
				// DE_INFO("Mouse move on line");
				adjust_right_panel_vert(engine, mouse_on_line_pos.x - mouse_on_line_pos_old.x);
			}
		}
		else if (mouse_on_line_hori_right_panels_ct)
		{
			line_hori_right_width = 500;
			engine->allStates.blockMouseStates = true;
			if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
			{
				// DE_INFO("Mouse move on line");
				adjust_hori_right_panels(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
			}
		}
		else if (mouse_on_line_hori_center_panels_ct)
		{
			// DE_INFO("Click on line horizontal center");
			line_hori_center_width = 500;
			engine->allStates.blockMouseStates = true;
			if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
			{
				// DE_INFO("Mouse move on line");
				adjust_hori_center_panels(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
			}
		}
		else if (mouse_on_line_vert_hyerarchy_ct)
		{
			// DE_INFO("Click on line vertical hyerarchie");
			line_vert_hierarchy_width = 500;
			engine->allStates.blockMouseStates = true;
			if (mouse_on_line_pos.x != mouse_on_line_pos_old.x)
			{
				// DE_INFO("Mouse move on line");
				adjust_vert_hyerarchy_panels(engine, mouse_on_line_pos.x - mouse_on_line_pos_old.x);
			}
		}
	}

	mouse_on_line_pos_old = mouse_on_line_pos;

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (mouse_on_line_vert_hyerarchy_ct || mouse_on_line_hori_center_panels_ct
		|| mouse_on_line_hori_right_panels_ct || mouse_on_line_vert_ct))
	{
		mouse_clicked = true;
	}
	else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && (mouse_on_line_vert_hyerarchy_ct || mouse_on_line_hori_center_panels_ct
		|| mouse_on_line_hori_right_panels_ct || mouse_on_line_vert_ct))
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

		resize_screen(engine);
		// DE_INFO("Window resized in engine");
	}

	resize_right_panel(engine);
}
