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

# include "../../library/extern/raylib/src/raylib.h"
# include "../../library/extern/raylib/src/raymath.h"
# include "../../library/libft/libft.h"
# include "struct_globale.h"
# include "../../library/drackengine_lib/drackengine_lib.h"
# include "../srcs/utility/buttons.h"
// # include "Config/menus.h"

# include <signal.h>


// Windows define
#define BORDER_COLOR DARKPURPLE2
#define BORDER_THICK 2
#define WINDOW_OTHERS (Vector2){800, 500}
#define CAMERA_UP_BAR 30

#define MAIN_MENU_LENGTH 4
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

// Camera global state context data [56 bytes]
typedef struct CameraData
{
    unsigned int mode;              // Current camera mode
    float targetDistance;           // Camera distance from position to target
    float playerEyesPosition;       // Player eyes position from ground (in meters)
    Vector2 angle;                  // Camera angle in plane XZ
    Vector2 previousMousePosition;  // Previous mouse position

    // Camera movement control keys
    int moveControl[6];             // Move controls (CAMERA_FIRST_PERSON)
    int smoothZoomControl;          // Smooth zoom control key
    int altControl;                 // Alternative control key
    int panControl;                 // Pan view control key
}	CameraData;

static CameraData CAMERA = {        // Global CAMERA state context
    .mode = 0,
    .targetDistance = 0,
    .playerEyesPosition = 1.85f,
    .angle = { 0 },
    .previousMousePosition = { 0 },
    .moveControl = { 'W', 'S', 'D', 'A', 'E', 'Q' },
    .smoothZoomControl = 341,       // raylib: KEY_LEFT_CONTROL
    .altControl = 342,              // raylib: KEY_LEFT_ALT
    .panControl = 2                 // raylib: MOUSE_BUTTON_MIDDLE
};

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

    STATE_VIEW_SETTINGS_LANGUAGE,
    STATE_VIEW_SETTINGS_THEME,
    STATE_VIEW_SETTINGS_OPTIONS,

    STATE_VIEW_HELP_ABOUT,
    STATE_VIEW_HELP_SUPPORT,
    STATE_VIEW_HELP_DOCUMENTATION,
}   ViewState;

typedef struct Ray3D
{
	Ray 			ray; // Picking line ray
	RayCollision	collision;
}	Ray3D;

typedef struct ButtonsMenu
{
    Button*  play;
    Button*  stop;
}   ButtonsMenu;

typedef struct TestWorkspace
{
    Vector3 cubePosition;
    Vector3 cubeSize;

    Ray ray;                    // Picking line ray
    RayCollision collision;     // Ray collision hit info
}   TestWorkspace;

typedef struct  Engine
{
    Vector2             screenSize; // in engine mode
    Vector2             lastScreenSize; // in engine mode
    Vector2             screenSizeWindow; // in window mode
    // WindowsSizeType     savedScreenSizeWindow;

    MultipleCam3D	        *allCameras;

    // Buttons Menu Up Bar
    ButtonsMenu             buttonsMenuUp;

    // Window state
    ViewState               currentStateView;
    ViewState               lastStateView;

    volatile sig_atomic_t   exitCt;
    bl8                     introCt;

    Cube3D	                cube_01;
    Ray3D			        ray;
    Mouse			        mouse;

    // Tests
    Texture2D               testTexture;
    TestWorkspace           testWorkspace;

    // For Text
    DE_Font                 fonts;
}   Engine;

//******************************************************************************//
//***                               engine.h                                 ***//
//******************************************************************************//

void    dr_init(Engine *engine);
void    dr_update(Engine *engine);
void    dr_exit(Engine *engine);

//******************************************************************************//
//***                              utility.h                                 ***//
//******************************************************************************//

void	open_window(Vector2 screenSize, Vector2 minSize, char *title, bool resizable);
void    print_memory_usage(const char* phase);

//******************************************************************************//
//***                              sideUpPanel.h                             ***//
//******************************************************************************//

void	ftUpMenu2D(Engine *engine, Camera2D *camera);
void    ftDrawDropdownMenu(Engine *engine);

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

void    ftControlMainPanel(Engine *engine);

//******************************************************************************//
//***                           menu_functions.c                             ***//
//******************************************************************************//

void    quit_menu_window(Engine *engine);

#endif
