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

#define MAIN_MENU_LENGTH 4
typedef enum  MainMenus
{
    FILES,
    EDIT,
    VIEW,
    HELP
}   MainMenus;

// #define SUB_MENU_FILES_LENGTH 5
// typedef enum  SubMenusFiles
// {
//     NEW,
//     OPEN,
//     SAVE,
//     SAVE_AS,
//     EXPORT
// }   SubMenusFiles;

// #define SUB_MENU_EDIT_LENGTH 5
// typedef enum  SubMenusEdit
// {
//     UNDO,
//     REDO,
//     CUT,
//     COPY,
//     PASTE
// }   SubMenusEdit;

// #define SUB_MENU_SETTINGS_LENGTH 3
// typedef enum  SubMenusSettings
// {
//     LANGUAGE,
//     THEME,
//     OPTIONS
// }   SubMenusSettings;

// #define SUB_MENU_HELP_LENGTH 3
// typedef enum  SubMenusHelp
// {
//     ABOUT,
//     SUPPORT,
//     DOCUMENTATION
// }   SubMenusHelp;

//******************************************************************************//
//***                             menu_functions.c                           ***//
//******************************************************************************//

void    menu_files_new(void);
void    menu_files_open(void);
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
