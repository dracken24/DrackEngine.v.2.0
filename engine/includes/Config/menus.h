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

//******************************************************************************//
//***                             menu_functions.c                           ***//
//******************************************************************************//

void    menu_files_new(struct Engine *engine);
void    menu_files_open(struct Engine *engine);
void    menu_files_save(struct Engine *engine);
void    menu_files_save_as(struct Engine *engine);
void    menu_files_export(struct Engine *engine);

void    menu_edit_undo(Engine *engine);
void    menu_edit_redo(Engine *engine);
void    menu_edit_cut(Engine *engine);
void    menu_edit_copy(Engine *engine);
void    menu_edit_paste(Engine *engine);

void    menu_settings_language(Engine *engine);
void    menu_settings_theme(Engine *engine);
void    menu_settings_options(Engine *engine);

void    menu_help_about(Engine *engine);
void    menu_help_documentation(Engine *engine);
void    menu_help_support(Engine *engine);

#endif
