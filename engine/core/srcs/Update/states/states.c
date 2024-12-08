/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--* PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* DATE:		     26-10-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* FILE: 	      states.c            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../includes/engine.h"

void	check_engine_mouse_state(Engine *engine);

#define LINE_WIDTH 4

extern	bl8 g_reset_workspace;

void	change_state_mouse(Engine *engine, MouseState mouse_state)
{
	if (engine->allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE && mouse_state != MOUSE_STATE_ON_WORKSPACE)
	{
		g_reset_workspace = true;
		engine->mouseOnWorkspaceCpp = false;
		// DE_DEBUG("Exit Workspace");
	}
	else if (engine->allStates.currentStateMouse != MOUSE_STATE_ON_WORKSPACE && mouse_state == MOUSE_STATE_ON_WORKSPACE)
	{
		// DE_DEBUG("Enter Workspace");
		engine->mouseOnWorkspaceCpp = true;
	}
	engine->allStates.lastStateMouse = engine->allStates.currentStateMouse;
	engine->allStates.currentStateMouse = mouse_state;
	// DE_DEBUG("CT: %d", engine->mouseOnWorkspaceCpp);
}

void    check_mouse_state(Engine *engine)
{
	bl8	block_mouse = engine->allStates.blockMouseStates;
	if (engine->allStates.currentStateView == STATE_VIEW_ENGINE && block_mouse == false)
	{
		check_engine_mouse_state(engine);
	}
}

void	check_engine_mouse_state(Engine *engine)
{
	Rectangle	rec01 = engine->allCameras->camera01.rectForCam;
	Rectangle	rec02 = engine->allCameras->camera02.rectForCam;
	Rectangle	rec03 = engine->allCameras->camera03.rectForCam;
	Rectangle	rec04 = engine->allCameras->camera04.rectForCam;
	Rectangle	rec05 = engine->allCameras->camera05.rectForCam;

	Vector2		mouse_pos = GetMousePosition();

	// Check collision with cameras separation lines
	// Line Verticale separation 03 et Workspace panels
	if (CheckCollisionPointLine(GetMousePosition(), (Vector2){rec03.x, rec03.y + rec03.height},
		(Vector2){rec03.x + rec03.width, rec03.y + rec03.height}, LINE_WIDTH))
	{
		// DE_DEBUG("Mouse Hit Separation line UP");
		change_state_mouse(engine, MOUSE_STATE_ON_RESIZE_LINES_UP);
		return;
	}
	// Line horizontale separation workspace et 05 panels
	else if (CheckCollisionPointLine(mouse_pos, (Vector2){rec05.x, rec05.y},
		(Vector2){rec05.x + rec05.width, rec05.y}, LINE_WIDTH))
	{
		// DE_DEBUG("Mouse Hit Separation line DOWN");
		change_state_mouse(engine, MOUSE_STATE_ON_RESIZE_LINES_DOWN);
		return;
	}
	// Line verticale separation workspace et 01/02 panels
	else if (CheckCollisionPointLine(mouse_pos, (Vector2){rec01.x, rec01.y}, (Vector2){rec01.x, rec01.y + rec01.height}, LINE_WIDTH)
			|| CheckCollisionPointLine(mouse_pos, (Vector2){rec02.x, rec02.y}, (Vector2){rec02.x, rec02.y + rec02.height}, LINE_WIDTH))
	{
		// DE_DEBUG("Mouse Hit Separation line RIGHT");
		change_state_mouse(engine, MOUSE_STATE_ON_RESIZE_LINES_RIGHT);
		return;
	}
	// Line Verticale separation 04 et Workspace panels
	else if (CheckCollisionPointLine(mouse_pos, (Vector2){rec04.x + rec04.width, rec04.y},
		(Vector2){rec04.x + rec04.width, rec04.y + rec04.height}, LINE_WIDTH))
	{
		// DE_DEBUG("Mouse Hit Separation line LEFT");
		change_state_mouse(engine, MOUSE_STATE_ON_RESIZE_LINES_LEFT);
		return;
	}

	// Check collision with menus
	// Mouse hit menu square 01
	else if (CheckCollisionPointRec(mouse_pos, rec01))
	{
		// DE_INFO("Mouse Hit Rec 01");
		change_state_mouse(engine, MOUSE_STATE_ON_MENU_01);
	}
	// Mouse hit menu square 02
	else if (CheckCollisionPointRec(mouse_pos, rec02))
	{
		// DE_INFO("Mouse Hit Rec 02");
		change_state_mouse(engine, MOUSE_STATE_ON_MENU_02);
	}
	// Mouse hit menu square 03
	else if (CheckCollisionPointRec(mouse_pos, rec03))
	{
		// DE_INFO("Mouse Hit Rec 03");
		change_state_mouse(engine, MOUSE_STATE_ON_MENU_03);
	}
	// Mouse hit menu square 04
	else if (CheckCollisionPointRec(mouse_pos, rec04))
	{
		// DE_INFO("Mouse Hit Rec 04");
		change_state_mouse(engine, MOUSE_STATE_ON_MENU_04);
	}
	// Mouse hit menu square 05
	else if (CheckCollisionPointRec(mouse_pos, rec05))
	{
		// DE_INFO("Mouse Hit Rec 05");
		change_state_mouse(engine, MOUSE_STATE_ON_MENU_05);
	}
	else
	{
		// DE_INFO("Your on Workspace");
		change_state_mouse(engine, MOUSE_STATE_ON_WORKSPACE);
	}
}
