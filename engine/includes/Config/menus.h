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

typedef enum  MainMenus
{
    FILES,
    EDIT,
    VIEW,
    HELP
}   MainMenus;

typedef enum  SubMenusFiles
{
    NEW,
    OPEN,
    SAVE,
    SAVE_AS,
    EXPORT
}   SubMenusFiles;

typedef enum  SubMenusEdit
{
    UNDO,
    REDO,
    CUT,
    COPY,
    PASTE
}   SubMenusEdit;

typedef enum  SubMenusSettings
{
    LANGUAGE,
    THEME,
    OPTIONS
}   SubMenusSettings;

typedef enum  SubMenusHelp
{
    ABOUT,
    SUPPORT,
    DOCUMENTATION
}   SubMenusHelp;

#endif
