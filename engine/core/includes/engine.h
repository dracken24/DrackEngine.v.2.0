/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      Engine.h            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ENGINE_H
# define ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

# include "raylib.h"
# include "raymath.h"
# include "rlgl.h"
# include "../../library/libft/libft.h"
# include "struct_globale.h"
# include "../../library/drackengine_lib/drackengine_lib.h"
# include "../srcs/utility/buttons.h"
// #include "../srcs/errors_manager/popUp/error_to_popUp.h"

// # include "Config/menus.h"
# include "../../library/extern/raygizmo/include/raygizmo.h"

# include <signal.h>

struct RGizmo;

// Windows define
# define BORDER_COLOR DARKPURPLE2
# define BORDER_THICK 3
# define WINDOW_OTHERS (Vector2){800, 500}
# define CAMERA_UP_BAR 30

# define VEC2_Zero (Vector2){0, 0}
# define REC_ZERO (Rectangle){0, 0, 0, 0}
# define REC_ERR_TO_POPUP_DEFAULT (Rectangle){GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 - 150, 400, 300}
# define REC_ERR_TO_POPUP_DEFAULT_CAM07 (Rectangle){get_camera07_rect().width / 2 - 200, get_camera07_rect().height / 2 - 150, 400, 300}

# define MAIN_MENU_LENGTH 4
typedef enum  MainMenus
{
	FILES,
	EDIT,
	VIEW,
	HELP
}   MainMenus;

#define SUB_MENU_FILES_LENGTH 16
typedef enum  SubMenus
{
	FILES_NEW,
	FILES_OPEN,
	FILES_SAVE,
	FILES_SAVE_AS,
	FILES_EXPORT,

	EDIT_UNDO,
	EDIT_REDO,
	EDIT_CUT,
	EDIT_COPY,
	EDIT_PASTE,

	SETTINGS_LANGUAGE,
	SETTINGS_THEME,
	SETTINGS_OPTIONS,

	HELP_ABOUT,
	HELP_SUPPORT,
	HELP_DOCUMENTATION,
}   SubMenus;

typedef struct DE_Font
{
	Font    defaultFont;
}   DE_Font;

typedef struct Cube3D
{
	Vector3	pos;
	Vector3	size;
	Texture	texture;
	char*	name;
} Cube3D;

typedef struct ButtonsMenu
{
	Button  play;
	Button  stop;
}   ButtonsMenu;

typedef struct Ray3D
{
	Ray 			ray; // Picking line ray
	RayCollision	collision;
}	Ray3D;

typedef struct Language
{
	char* language;
	// char*** dropdown_menus_03;
}	Language;

typedef struct ErrorToPopUp
{
    logLevel    level;
    Rectangle   rect;
    Rectangle   cam07;

    Color   bgColor;
	bl8		popUpInUse;
} ErrorToPopUp;

typedef struct ErrorManager
{
	ErrorToPopUp errorToPopUp;
} ErrorManager;


//******************************************************************************//
//***                                 States                                 ***//
//******************************************************************************//

typedef enum ViewState
{
	STATE_VIEW_ENGINE,
	STATE_VIEW_FILES_NEW_PROJECT,
	STATE_VIEW_FILES_OPEN_PROJECT,
	STATE_VIEW_FILES_SAVE,
	STATE_VIEW_FILES_SAVE_AS,
	STATE_VIEW_FILES_EXPORT,

	STATE_VIEW_EDIT_UNDO,
	STATE_VIEW_EDIT_REDO,
	STATE_VIEW_EDIT_CUT,
	STATE_VIEW_EDIT_COPY,
	STATE_VIEW_EDIT_PASTE,

	STATE_VIEW_SETTINGS_ENGINE,
	STATE_VIEW_SETTINGS_PROJECT,
	STATE_VIEW_SETTINGS_OPTIONS,

	STATE_VIEW_HELP_ABOUT,
	STATE_VIEW_HELP_SUPPORT,
	STATE_VIEW_HELP_DOCUMENTATION,

	STATE_VIEW_SUB_WINDOW,
}   ViewState;

typedef enum MouseState
{
	MOUSE_STATE_ON_WORKSPACE,			// 0
	MOUSE_STATE_ON_MENU_01,				// 1
	MOUSE_STATE_ON_MENU_02,				// 2
	MOUSE_STATE_ON_MENU_03,				// 3
	MOUSE_STATE_ON_MENU_04,				// 4
	MOUSE_STATE_ON_MENU_05,				// 5
	MOUSE_STATE_ON_RESIZE_LINES_UP, 	// 6
	MOUSE_STATE_ON_RESIZE_LINES_DOWN,	// 7
	MOUSE_STATE_ON_RESIZE_LINES_RIGHT,	// 8
	MOUSE_STATE_ON_RESIZE_LINES_LEFT,	// 9
	MOUSE_STATE_ON_OTHER_WINDOW,		// 10
	MOUSE_STATE_ON_POP_UP,				// 11
}   MouseState;

// TODO: Gerer le mouse state quand dropdown menu is open
typedef struct AllStates
{
	// Window states
	ViewState	currentStateView;
	ViewState   lastStateView;

	// Mouse states
	MouseState  currentStateMouse;
	MouseState  lastStateMouse;
	bl8			blockMouseStates;
}   AllStates;

//******************************************************************************//
//***                                 Tests                                  ***//
//******************************************************************************//

typedef struct TestWorkspace
{
	Model model;
	Model modelCube;
	struct RGizmo gizmo;

}   TestWorkspace;

//******************************************************************************//
//***                               User Struct                              ***//
//******************************************************************************//

typedef struct UserSettings
{
	char	*engineVersion;

	// Default 60 FPS
	sint16	currentFPS;
} UserSettings;

typedef struct ProjectSettings
{
	char	*projectName;
	char	*projectVersion;
	char	*projectPath;

	char	*engineVersion;
	
	// Default 60 FPS
	sint16	currentFPS;
} ProjectSettings;

//******************************************************************************//
//***                               MAIN STRUCT                              ***//
//******************************************************************************//

typedef struct CoreInfos
{
	char	*coreVersion;
} CoreInfos;


typedef struct  Engine
{
	Vector2			screenSize; // in engine mode
	Vector2			lastScreenSize; // in engine mode
	Vector2			screenSizeWindow; // in window mode
	// WindowsSizeType     savedScreenSizeWindow;

	MultipleCam3D   *allCameras;

	// Buttons Menu Up Bar
	ButtonsMenu     buttonsMenuUp;

	// Window state
	AllStates       allStates;

	bl8             introCt;
	bl8				inputEventCt;

	Cube3D	        cube_01;
	Ray3D			ray;
	Mouse			mouse;

	ErrorManager	errorManager;	

	// Tests
	Texture2D       testTexture;
	TestWorkspace   testWorkspace;

	// For Text
	DE_Font         fonts;
	Language        language;
	// Exit Engine
	volatile sig_atomic_t   exitCt;

	ProjectSettings	projectSettings;
	UserSettings	userSettings;
}   Engine;

//##############################################################################//
//###                     ### Functions Definitions ###                      ###//
//##############################################################################//
//******************************************************************************//
//***                               engine                                   ***//
//******************************************************************************//

void    dr_init(Engine *engine, CoreInfos *coreInfos);
void    dr_update(Engine *engine, CoreInfos const *coreInfos);
void    dr_exit(Engine *engine, CoreInfos *coreInfos);

//******************************************************************************//
//***                              utility.C                                 ***//
//******************************************************************************//

void		open_window(Vector2 screenSize, Vector2 minSize, char *title, bool resizable);
void		print_memory_usage(const char* phase);
Rectangle	rectangle_addition(Rectangle rect01, Rectangle rect02);
Rectangle	get_camera07_rect(void);

//******************************************************************************//
//***                              up_panel.h                                ***//
//******************************************************************************//

void	up_menu(Engine *engine, Camera2D *camera);
void    draw_drop_down_menu(Engine *engine);

//******************************************************************************//
//***                             windows_events.c                           ***//
//******************************************************************************//

void    window_events(Engine *engine);

//******************************************************************************//
//***                                 update.c                               ***//
//******************************************************************************//

void    draw_rectangle_borders(Rectangle rectangle, Color color, int thickness);

//******************************************************************************//
//***                                Workspace.c                             ***//
//******************************************************************************//

void    control_main_panel(Engine *engine, Camera *camera);

//******************************************************************************//
//***                           menu_functions.c                             ***//
//******************************************************************************//

void    quit_menu_window(Engine *engine);
void    change_language(Engine *engine, const char *language);
void    change_view(Engine *engine, ViewState state, bl8 resize_window, int *selectedTab, bl8 *isDropdownOpen);

#ifdef __cplusplus
}
#endif

#endif
