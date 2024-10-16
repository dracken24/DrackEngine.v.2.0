/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      menus.h             *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef MENUS_H
# define MENUS_H

#include "../engine.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct Engine;
struct d_Pid;

// #define MAIN_MENU_LENGTH 4
// typedef enum  MainMenus
// {
//     FILES,
//     EDIT,
//     VIEW,
//     HELP
// }   MainMenus;

// #define SUB_MENU_FILES_LENGTH 16
// typedef enum  SubMenus
// {
//     FILES_NEW,
//     FILES_OPEN,
//     FILES_SAVE,
//     FILES_SAVE_AS,
//     FILES_EXPORT,

//     EDIT_UNDO,
//     EDIT_REDO,
//     EDIT_CUT,
//     EDIT_COPY,
//     EDIT_PASTE,

//     SETTINGS_LANGUAGE,
//     SETTINGS_THEME,
//     SETTINGS_OPTIONS,

//     HELP_ABOUT,
//     HELP_SUPPORT,
//     HELP_DOCUMENTATION,
// }   SubMenus;

//******************************************************************************//
//***                             menu_functions.c                           ***//
//******************************************************************************//

void    menu_files_new(struct Engine *engine);
void    menu_files_open(struct Engine *engine);
void    menu_files_save(void);
void    menu_files_save_as(void);
void    menu_files_export(void);

void    menu_edit_undo(void);
void    menu_edit_redo(void);
void    menu_edit_cut(void);
void    menu_edit_copy(void);
void    menu_edit_paste(void);

void    menu_settings_language(void);
void    menu_settings_theme(void);
void    menu_settings_options(void);

void    menu_help_about(void);
void    menu_help_documentation(void);
void    menu_help_support(void);

//******************************************************************************//
//***                             up_panel_func_definitions.c                ***//
//******************************************************************************//

void    fork_for_new_window(d_Pid *pid_struct, int enum_link, const char *title);
void    fork_for_file_open(d_Pid *pid_struct, int enum_link, const char *title);

#endif
