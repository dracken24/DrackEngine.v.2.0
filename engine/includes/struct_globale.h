#ifndef STRUCT_GLOBLE_H
# define STRUCT_GLOBLE_H

# include "../srcs/utility/buttons.h"

# include "raylib.h"

# include <math.h>

# define G 800
# define PLAYER_JUMP_SPD 600.0f
# define PLAYER_HOR_SPD 200.0f
# define MAX_INPUT_CHARS 8

# define CENTER_SCREEN {(float)game->screenWidth / 2 - 150, (float)game->screenHeight / 2 - 20}

# define DARKGRAY1		CLITERAL(Color){ 60, 60, 60, 255 }
# define DARKGRAY2		CLITERAL(Color){ 120, 120, 120, 255 }
# define DARKGRAY3		CLITERAL(Color){ 140, 140, 140, 255 }
# define DARKPURPLE2	CLITERAL(Color){ 46, 23, 126, 255 } 
# define MYDARKGREEN	CLITERAL(Color){ 0, 148, 54, 255 }
# define GRAYPURPLE		CLITERAL(Color){ 110, 113, 127, 255 }
# define LIGHTDARKGREEN CLITERAL(Color){ 0, 166, 69, 255 }

typedef struct Mouse
{
	Vector2	pos;
	Vector2	lastPos;
	float	camZoom;
	int		clickName;
}	Mouse;

//******************************************************************************//
//***                                Cameras                                 ***//
//******************************************************************************//

typedef struct NeedBy3DCam
{
	RenderTexture 	textForCam2;
	RenderTexture 	textForCam;
	Rectangle		rectForCam;
	Camera2D 		camera2D;
	Camera3D 		camera3D;
	Image			image;
	// Vector2			offset;
}	NeedBy3DCam;

typedef struct MultipleCam3D
{
	NeedBy3DCam	camera00;
	NeedBy3DCam camera01;
	NeedBy3DCam camera02;
	NeedBy3DCam camera03;
	NeedBy3DCam camera04;
	NeedBy3DCam camera05;
	NeedBy3DCam camera06;
	NeedBy3DCam camera07;
	NeedBy3DCam camera08;
	NeedBy3DCam camera09;
}	MultipleCam3D;

//******************************************************************************//
//***                                Buttons                                 ***//
//******************************************************************************//

typedef struct BUTTONS
{
    Rectangle		_rect;
    Texture2D		_texture;
    Color			_color;

    int				_nbr;
}   BUTTONS;


//******************************************************************************//
//***                              Text Gestion                              ***//
//******************************************************************************//

// Struct for text_entry.c
typedef struct	TextBox
{
	Rectangle rect;
	char *text;
	int textSize;
	int maxLength;
	int cursorPosition;
	int textOffset;
	bool isActive;
} TextBox;

// struct for New Projec Window camera07
typedef struct FilesNew
{
	TextBox	projectNameEntry;

	Button	confirmButton;
}	FilesNew;

typedef struct FilesOpen
{
	TextBox	projectNameEntry;
}	FilesOpen;

typedef struct FilesSave
{
	TextBox	testEntry;
}	FilesSave;

typedef struct FilesSaveAs
{
	TextBox	testEntry;
}	FilesSaveAs;

typedef struct FilesExport
{
	TextBox	testEntry;
}	FilesExport;

typedef struct SettingsEngine
{
	TextBox	testEntry;
}	SettingsEngine;

typedef struct SettingsProject
{
	TextBox	testEntry;
}	SettingsProject;

typedef struct SettingsOptions
{
	TextBox	testEntry;
}	SettingsOptions;

typedef struct HelpSupport
{
	TextBox	testEntry;
}	HelpSupport;

typedef struct HelpDoc
{
	TextBox	testEntry;
}	HelpDoc;

#endif
