/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-09-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     buttons.h            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef BUTTONS_H
# define BUTTONS_H

# include "../../../library/extern/raylib/src/raylib.h"
# include "../../includes/engine_defines.h"
typedef struct Button
{
	Rectangle		rect;
	Texture2D		texture;
	Texture2D		texture_hover;
	Texture2D		texture_click;
	Color			bg_color;
	Color			bg_hover_color;
	Color			bg_click_color;

	char*			text;
	Font			font;
	Vector2			text_position;
	Color			text_color;
	Color			text_hover_color;
	Color			text_click_color;

	bl8				isClicked;
	bl8				isAllocate;
	fl32			scale;
	int				nbr;

	// Function On Click
    void (*onClickCallback)(void *userData);
    void *userData;  // Parametre pass to callback
}	Button;

Button		button_init(Vector2 pos, Vector2 size, Color bg_color,
				Color text_color, char* texturePath, char* text, fl32 scale, int nbr);
void		button_unload(Button* button);
void		draw_button(Button* button, intptr_t fontSize, sint32 spacing, sint32 borderThick,
				Color borderColor, Vector2 cameraOrigin, bl8 skipUpdate);

Vector2		button_get_position(Button* const button);
Vector2		button_get_size(Button* const button);
Color		button_get_color(Button* const button);
Color		button_get_bg_hover_color(Button* const button);
Color		button_get_bg_click_color(Button* const button);
Texture2D	button_get_texture(Button* const button);
Rectangle	button_get_rectangle(Button* const button);
int			button_get_nbr(Button* const button);
Font		button_get_font(Button* const button);
Vector2		button_get_text_position(Button* const button);
Color		button_get_text_color(Button* const button);
Color		button_get_text_hover_color(Button* const button);
Color		button_get_text_click_color(Button* const button);

void        button_set_position(Button* button, Vector2 pos);
void		button_set_size(Button* button, Vector2 size);
void		button_set_bg_color(Button* button, Color bg_color);
void		button_set_bg_hover_color(Button* button, Color bg_hover_color);
void		button_set_bg_click_color(Button* button, Color bg_click_color);
void		button_set_texture(Button* button, Texture2D texture);
void		button_set_nbr(Button* button, int nbr);
void		button_set_font(Button* button, Font font);
void		button_set_text_position(Button* button, Vector2 text_position);
void		button_set_text_color(Button* button, Color text_color);
void		button_set_text_hover_color(Button* button, Color text_hover_color);
void		button_set_text_click_color(Button* button, Color text_click_color);
void		button_set_function(Button* button, void (*callback)(void *), void *userData);

void		button_unload_texture(Button* button);

#endif