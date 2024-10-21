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

#endif
