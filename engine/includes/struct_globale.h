#ifndef STRUCT_GLOBLE_H
# define STRUCT_GLOBLE_H

# include "../../library/extern/raylib/src/raylib.h"

# define G 800
# define PLAYER_JUMP_SPD 600.0f
# define PLAYER_HOR_SPD 200.0f
# define MAX_INPUT_CHARS 8

# define CENTER_SCREEN {(float)game->screenWidth / 2 - 150, (float)game->screenHeight / 2 - 20}

# define DARKGRAY1   CLITERAL(Color){ 60, 60, 60, 255 }
# define DARKGRAY2   CLITERAL(Color){ 120, 120, 120, 255 }
# define DARKGRAY3   CLITERAL(Color){ 140, 140, 140, 255 }
# define DARKPURPLE2 CLITERAL(Color){ 46, 23, 126, 255 } 
# define MYDARKGREEN  CLITERAL(Color){ 0, 148, 54, 255 }

typedef struct Mouse
{
	Vector2	pos;
	float	camZoom;
	int		clickName;
}	Mouse;

typedef struct NeedBy2DCam
{
	RenderTexture 	textForCam2;
	RenderTexture 	textForCam;
	Rectangle		rectForCam;
	Camera2D 		camera;
	Image			image;
}	NeedBy2DCam;

typedef struct MultipleCam2D
{
	NeedBy2DCam	camera00;
	NeedBy2DCam camera01;
	NeedBy2DCam camera02;
	NeedBy2DCam camera03;
	NeedBy2DCam camera04;
	NeedBy2DCam camera05;
	NeedBy2DCam camera06;
	NeedBy2DCam camera07;
	NeedBy2DCam camera08;
	NeedBy2DCam camera09;
}	MultipleCam2D;

typedef struct NeedBy3DCam
{
	RenderTexture 	textForCam2;
	RenderTexture 	textForCam;
	Rectangle		rectForCam;
	Camera2D 		camera2D;
	Camera 			camera3D;
	Image			image;
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

typedef struct BUTTONS
{

    // void		ftInitButton(Vector2 pos, Vector2 size,
    // 				Color color, Texture2D texture, int nbr);

    // Vector2		ftReturnPosition(void) const;
    // Vector2		ftReturnSize(void) const;
    // Color		ftReturnColor(void) const;
    // Texture2D	ftReturnTexture(void) const;
    // Rectangle	ftReturnRectangle(void) const;
    // int			ftReturnNbr(void) const;

    // void		ftUnloadTexture(void);

    Rectangle		_rect;
    Texture2D		_texture;
    Color			_color;

    int				_nbr;
}   BUTTONS;

typedef struct MenuUp
{
	BUTTONS		buttonControlClose;
	BUTTONS		buttonControlOpen;
	BUTTONS		buttonColorClose;
	BUTTONS		buttonColorOpen;
	BUTTONS		buttonListClose;
	BUTTONS		buttonListOpen;

	BUTTONS		play;
	BUTTONS		stop;
}	MenuUp;

typedef struct MenuSideDown
{
	BUTTONS		buttonMiddleClose;
	BUTTONS		buttonMiddleOpen;
	BUTTONS		buttonRightClose;
	BUTTONS		buttonRightOpen;
	BUTTONS		buttonLeftClose;
	BUTTONS		buttonLeftOpen;
}	MenuSideDown;

typedef struct TrioBox
{
	Vector2		posTextBox;

	Rectangle	writeBox;
	Rectangle	hitBox;
}	TrioBox;

typedef struct TextBoxSideUp
{
	TrioBox		RightBox0;
	TrioBox		LeftBox0;
	TrioBox		RightBox1;
	TrioBox		LeftBox1;

}	TextBoxSideUp;

// typedef struct Ray3D
// {
// 	Ray 			ray = {0}; // Picking line ray
// 	RayCollision	collision = {0};
// }	Ray3D;

// typedef struct RayForMove
// {
// 	Ray 			ray = {0}; // Picking line ray
// 	Ray				lastRay;
// 	RayCollision	collision = {0};
// }	RayForMove;

#endif
