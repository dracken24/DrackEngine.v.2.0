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

#include "../../../includes/engine.h"
#include "../../../includes/Config/menus.h"
#include <unistd.h>
#include <sys/wait.h>
//******************************************************************************//
//***                              Files Menu                                ***//
//******************************************************************************//

void    fork_for_new_window(d_Pid *pid_struct, int enum_link, const char *title)
{
    pid_struct->engine_pid = fork();
    if (pid_struct->engine_pid == 0)
    {
        // Processus enfant
        chdir("../windows_gestion/new_project");
        pid_struct->engine_running = true;
        if (system("./new_project 1000 650 \"New Project\"") == -1)
        {
            DE_ERROR("Error launching new_project");
            exit(EXIT_FAILURE);
        }
        pid_struct->engine_running = false;
        exit(EXIT_SUCCESS);
    }
    else if (pid_struct->engine_pid < 0)
    {
        // Erreur lors du fork
        perror("Erreur lors du fork");
    }
    else
    {
        // Processus parent
        pid_struct->enum_link = enum_link;
        pid_struct->engine_running = true;
    }
}

int    get_pid_tab_index(Engine *engine)
{
    return (engine->engine_pid_ct++);
}

void    menu_files_new(Engine *engine)
{
    DE_DEBUG("Option selected: %s", "New !");
    // int index = get_pid_tab_index(engine);
    // DE_DEBUG("Index: %d", index);

    fork_for_new_window(&engine->new_window_pid[FILES_NEW], (SubMenus)FILES_NEW, "New Project");
    DrawText("New Project !", 20, 20, 20, PINK);
}

void    menu_files_open(void)
{
    DE_DEBUG("Option selected: %s", "Open !");
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
