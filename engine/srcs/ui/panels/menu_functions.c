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

#include "../../../includes/Config/menus.h"

//******************************************************************************//
//***                              Files Menu                                ***//
//******************************************************************************//

void    menu_files_new(Engine *engine)
{
    DE_DEBUG("Option selected: %s", "New !");
    if (engine->new_window_pid[FILES_NEW].engine_pid > 0)
    {
        return;
    }

    fork_for_new_window(&engine->new_window_pid[FILES_NEW], (SubMenus)FILES_NEW, "New Project");
    // DrawText("New Project !", 20, 20, 20, PINK);
}

void    menu_files_open(Engine *engine)
{
    DE_DEBUG("Option selected: %s", "Open !");
    if (engine->new_window_pid[FILES_OPEN].engine_pid > 0)
    {
        return;
    }

    fork_for_file_open(&engine->new_window_pid[FILES_OPEN], (SubMenus)FILES_OPEN, "Open Project");
    // DrawText("Open Project !", 20, 20, 20, PINK);
}

void    menu_files_save(void)
{
    DE_DEBUG("Option selected: %s", "Save !");
}

void    menu_files_save_as(void)
{
    DE_DEBUG("Option selected: %s", "Save as !");
}

void    menu_files_export(void)
{
    DE_DEBUG("Option selected: %s", "Export !");
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_edit_undo(void)
{
    DE_DEBUG("Option selected: %s", "Undo !");
}

void    menu_edit_redo(void)
{
    DE_DEBUG("Option selected: %s", "Redo !");
}

void    menu_edit_cut(void)
{
    DE_DEBUG("Option selected: %s", "Cut !");
}

void    menu_edit_copy(void)
{
    DE_DEBUG("Option selected: %s", "Copy !");
}

void    menu_edit_paste(void)
{
    DE_DEBUG("Option selected: %s", "Paste !");
}

//******************************************************************************//
//***                             Settings Menu                              ***//
//******************************************************************************//

void    menu_settings_language(void)
{
    DE_DEBUG("Option selected: %s", "Language !");
}

void    menu_settings_theme(void)
{
    DE_DEBUG("Option selected: %s", "Theme !");
}

void    menu_settings_options(void)
{
    DE_DEBUG("Option selected: %s", "Options !");
}

//******************************************************************************//
//***                               Edit Menu                                ***//
//******************************************************************************//

void    menu_help_about(void)
{
    DE_DEBUG("Option selected: %s", "About !");
}

void    menu_help_documentation(void)
{
    DE_DEBUG("Option selected: %s", "Documentation !");
}

void    menu_help_support(void)
{
    DE_DEBUG("Option selected: %s", "Support !");
}
