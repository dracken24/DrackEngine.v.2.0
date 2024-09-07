/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 29-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     input.cpp       *--*                  | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/input.hpp"
#include "core/event.hpp"
#include "core/deMemory.hpp"
#include "core/logger.hpp"

typedef struct	keyboardState
{
	bl8		keys[256];
}	keyboardState;

typedef struct	mouseState
{
	sint16	x;
	sint16	y;
	uint8	buttons[BUTTON_MAX_BUTTONS];
}	mouseState;

typedef struct	inputState
{
	keyboardState	keyboardCurrent;
	keyboardState	keyboardPrevious;
	mouseState		mouseCurrent;
	mouseState		mousePrevious;
}	inputState;

// Internal input state
static inputState	*statePtr;

void	DE_InputInit(uint64* memoryRequirement, void* state)
{
	*memoryRequirement = sizeof(inputState);
	if (state == 0)
	{
		return;
	}
	SetMemory(state, sizeof(inputState));
	statePtr = (inputState *)state;

	DE_INFO("Input subsystem initialized.");
}

void	DE_InputShutdown(void* state)
{
	// TODO: Add shutdown routines when needed.
	statePtr = 0;
}

void	DE_InputUpdate(dbl64 deltaTime)
{
	if (!statePtr)
	{
		return;
	}

	// Copy current states to previous states.
	CopyMemory(&statePtr->keyboardPrevious, &statePtr->keyboardCurrent, sizeof(keyboardState));
	CopyMemory(&statePtr->mousePrevious, &statePtr->mouseCurrent, sizeof(mouseState));
}

void	InputProcessKey(keys key, bl8 pressed)
{
	// Only handle this if the state actually changed.
	if (statePtr && statePtr->keyboardCurrent.keys[key] != pressed)
	{
		// Update internal state.
		statePtr->keyboardCurrent.keys[key] = pressed;

		// Fire off an event for immediate processing.
		eventContext context;
		context.data.uint16[0] = key;
		EventFire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0, context);
	}
}

void	DE_InputProcessButton(buttons button, bl8 pressed)
{
	// If the state changed, fire an event.
	if (statePtr->mouseCurrent.buttons[button] != pressed)
	{
		statePtr->mouseCurrent.buttons[button] = pressed;

		// Fire the event.
		eventContext context;
		context.data.uint16[0] = button;
		EventFire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, context);
	}
}

void	DE_InputProcessMouseMove(sint16 x, sint16 y)
{
	// Only process if actually different
	if (statePtr->mouseCurrent.x != x || statePtr->mouseCurrent.y != y)
	{
		// NOTE: Enable this if debugging.
		// DE_DEBUG("Mouse pos: %i, %i!", x, y);

		// Update internal state.
		statePtr->mouseCurrent.x = x;
		statePtr->mouseCurrent.y = y;

		// Fire the event.
		eventContext context;
		context.data.uint16[0] = x;
		context.data.uint16[1] = y;
		EventFire(EVENT_CODE_MOUSE_MOVED, 0, context);
	}
}

void	DE_OnMouseWheel(bl8 z_delta)
{
	// NOTE: no internal state to update.

	// Fire the event.
	eventContext context;
	context.data.c[0] = z_delta;
	if (z_delta > 0)
	{
		EventFire(EVENT_CODE_MOUSE_WHEEL_UP, 0, context);
	}
	else
	{
		EventFire(EVENT_CODE_MOUSE_WHEEL_DOWN, 0, context);
	}
}

bl8		DE_OnKeyDown(keys key)
{
	if (!statePtr)
	{
		return false;
	}
	return statePtr->keyboardCurrent.keys[key] == true;
}

bl8		DE_OnKeyUP(keys key)
{
	if (!statePtr)
	{
		return true;
	}
	return statePtr->keyboardCurrent.keys[key] == false;
}

bl8		DE_OnKeyPress(keys key)
{
	if (!statePtr)
	{
		return false;
	}
	return statePtr->keyboardPrevious.keys[key] == true;
}

bl8		DE_OnKeyRelease(keys key)
{
	if (!statePtr)
	{
		return true;
	}
	return statePtr->keyboardPrevious.keys[key] == false;
}

// mouse input
bl8 DE_OnMouseButtonPress(buttons button)
{
	if (!statePtr) {
		return false;
	}
	return statePtr->mouseCurrent.buttons[button] == true;
}

bl8 DE_OnMouseButtonRelease(buttons button)
{
	if (!statePtr)
	{
		return true;
	}
	return statePtr->mouseCurrent.buttons[button] == false;
}

bl8 DE_OnMouseButtonDown(buttons button)
{
	if (!statePtr)
	{
		return false;
	}
	return statePtr->mousePrevious.buttons[button] == true;
}

bl8 DE_OnMouseButtonUp(buttons button)
{
	if (!statePtr)
	{
		return true;
	}
	return statePtr->mousePrevious.buttons[button] == false;
}

void DE_GetMousePosition(sint32* x, sint32* y)
{
	if (!statePtr)
	{
		*x = 0;
		*y = 0;
		return;
	}
	*x = statePtr->mouseCurrent.x;
	*y = statePtr->mouseCurrent.y;
}

void DE_GetPreviousMousePosition(sint32* x, sint32* y)
{
	if (!statePtr)
	{
		*x = 0;
		*y = 0;
		return;
	}
	*x = statePtr->mousePrevious.x;
	*y = statePtr->mousePrevious.y;
}

bl8 DE_OnWindowResize(sint16 width, sint16 height)
{
	// NOTE: no internal state to update.
	// Fire the event.
	// DE_DEBUG("CODE: %i", code);
	eventContext context;

	context.data.uint16[0] = width;
	context.data.uint16[1] = height;

	EventFire(EVENT_CODE_RESIZED, 0, context);

	return true;
}
