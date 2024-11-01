/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:      menu_functions.c           *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07/window07.h"

bl8 window_in_operation = false;
bl8 refresh_frame = true;

//******************************************************************************//
//***                              Files Menu                                ***//
//******************************************************************************//

void    quit_menu_window(Engine *engine)
{
	DE_DEBUG("quit_menu_window()");
	switch (engine->allStates.currentStateView)
	{
		case STATE_VIEW_FILES_NEW_PROJECT:
			new_project_clean();
			new_project_destroy();
			break;
		case STATE_VIEW_FILES_OPEN_PROJECT:
			open_project_clean();
			open_project_destroy();
			break;
		case STATE_VIEW_FILES_SAVE:
			save_project_clean();
			save_project_destroy();
			break;
		case STATE_VIEW_FILES_SAVE_AS:
			save_as_project_clean();
			save_as_project_destroy();
			break;
		case STATE_VIEW_FILES_EXPORT:
			export_project_clean();
			export_project_destroy();
			break;
		case STATE_VIEW_EDIT_UNDO:
			break;
		case STATE_VIEW_EDIT_REDO:
			break;
		case STATE_VIEW_EDIT_CUT:
			break;
		case STATE_VIEW_EDIT_COPY:
			break;
		case STATE_VIEW_EDIT_PASTE:
			break;
		case STATE_VIEW_SETTINGS_ENGINE:
			settings_engine_clean();
			settings_engine_destroy();
			break;
		case STATE_VIEW_SETTINGS_PROJECT:
			settings_project_clean();
			settings_project_destroy();
			break;
		case STATE_VIEW_SETTINGS_OPTIONS:
			settings_options_clean();
			settings_options_destroy();
			break;
		case STATE_VIEW_HELP_ABOUT:
			help_about_clean();
			help_about_destroy();
			break;
		case STATE_VIEW_HELP_SUPPORT:
			help_support_clean();
			help_support_destroy();
			break;
		case STATE_VIEW_HELP_DOCUMENTATION:
			help_doc_clean();
			help_doc_destroy();
			break;
		
		default:
			break;
	}
	if (engine->allStates.currentStateView != STATE_VIEW_SUB_WINDOW)
	{
		engine->allStates.lastStateView = engine->allStates.currentStateView;
		engine->allStates.currentStateView = STATE_VIEW_ENGINE;
		SetWindowSize(engine->screenSize.x, engine->screenSize.y);
		window_in_operation = false;
	}
}

void    keys_events(Engine *engine)
{
	// DE_DEBUG("Debug 10");
	if ((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()  || engine->inputEventCt == true) &&
		!engine->allStates.currentStateView != STATE_VIEW_SUB_WINDOW)
	{
		DE_DEBUG("Debug 1: %d", engine->allStates.currentStateView);
		quit_menu_window(engine);
		DE_DEBUG("Debug 2");
		g_engine->inputEventCt = false;
	}
}

void    menu_files_new(Engine *engine, CoreInfos const *coreInfos)
{
	new_project_update(coreInfos);
}

void    menu_files_open(Engine *engine)
{
	open_project_update();
}

void    menu_files_save(Engine *engine)
{
	save_project_update();
}

void    menu_files_save_as(Engine *engine)
{
	save_as_project_update();
}

void    menu_files_export(Engine *engine)
{
	export_project_update();
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_edit_undo(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Undo !");
	quit_menu_window(engine);
}

void    menu_edit_redo(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Redo !");
	quit_menu_window(engine);
}

void    menu_edit_cut(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Cut !");
	quit_menu_window(engine);
}

void    menu_edit_copy(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Copy !");
	quit_menu_window(engine);
}

void    menu_edit_paste(Engine *engine)
{
	DE_DEBUG("Option selected: %s", "Paste !");
	quit_menu_window(engine);
}

//******************************************************************************//
//***                             Settings Menu                              ***//
//******************************************************************************//

void    menu_settings_engine(Engine *engine)
{
	settings_engine_update();
}

void    menu_settings_project(Engine *engine)
{
	settings_project_update();
}

void    menu_settings_options(Engine *engine)
{
	settings_options_update();
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_help_about(Engine *engine)
{
	help_about_update();
}

void    menu_help_support(Engine *engine)
{
	help_support_update();
}

void    menu_help_documentation(Engine *engine)
{
	help_doc_update();
}
