/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*            | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-09-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     buttons.c            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "buttons.h"
#include "../memory/dmemory.h"
#include "../../../library/drackengine_lib/logger.h"

//******************************** Init ********************************//

Button*		button_init(Vector2 pos, Vector2 size,
				Color bg_color, Color text_color, char *texturePath, fl32 scale, int nbr)
{
    Button* button;
    button = (Button*)de_allocate(sizeof(Button), MEMORY_TAG_UI);

    button->rect.x = pos.x;
    button->rect.y = pos.y;
    button->rect.width = size.x;
    button->rect.height = size.y;
    button->bg_color = bg_color;
    button->text_color = text_color;
    button->texture = LoadTexture(texturePath);
    button->nbr = nbr;
    button->scale = scale;
    
    DE_DEBUG("Play texture : %f, %f", button->texture.width, button->texture.height);

    return (button);
}

void    button_unload(Button* button)
{
    UnloadTexture(button->texture);
    UnloadTexture(button->texture_hover);
    UnloadTexture(button->texture_click);
    de_free(button, sizeof(Button), MEMORY_TAG_UI);
}

//******************************************************************************//
//***                               getters                                  ***//
//******************************************************************************//

Vector2     button_get_position(Button* button)
{
    return ((Vector2){button->rect.x, button->rect.y});
}

Vector2     button_get_size(Button* button)
{
    return ((Vector2){button->rect.width, button->rect.height});
}

Color       button_get_bg_color(Button* button)
{
    return (button->bg_color);
}

Color       button_get_bg_hover_color(Button* button)
{
    return (button->bg_hover_color);
}

Color       button_get_bg_click_color(Button* button)
{
    return (button->bg_click_color);
}

Texture2D   button_get_texture(Button* button)
{
    return (button->texture);
}

int         button_get_nbr(Button* button)
{
    return (button->nbr);
}

Rectangle   button_get_rectangle(Button* button)
{
    return (button->rect);
}

Font        button_get_font(Button* button)
{
    return (button->font);
}

Vector2     button_get_text_position(Button* button)
{
    return (button->text_position);
}

Color       button_get_text_color(Button* button)
{
    return (button->text_color);
}

Color       button_get_text_hover_color(Button* button)
{
    return (button->text_hover_color);
}

Color       button_get_text_click_color(Button* button)
{
    return (button->text_click_color);
}

//******************************************************************************//
//***                               setters                                  ***//
//******************************************************************************//

void        button_set_position(Button* button, Vector2 pos)
{
    button->rect.x = pos.x;
    button->rect.y = pos.y;
}

void        button_set_size(Button* button, Vector2 size)
{
    button->rect.width = size.x;
    button->rect.height = size.y;
}

void        button_set_bg_color(Button* button, Color bg_color)
{
    button->bg_color = bg_color;
}

void        button_set_bg_hover_color(Button* button, Color bg_hover_color)
{
    button->bg_hover_color = bg_hover_color;
}

void        button_set_bg_click_color(Button* button, Color bg_click_color)
{
    button->bg_click_color = bg_click_color;
}

void        button_set_texture(Button* button, Texture2D texture)
{
    button->texture = texture;
}

void        button_set_nbr(Button* button, int nbr)
{
    button->nbr = nbr;
}

void        button_set_font(Button* button, Font font)
{
    button->font = font;
}

void        button_set_text_position(Button* button, Vector2 text_position)
{
    button->text_position = text_position;
}

void        button_set_text_color(Button* button, Color text_color)
{
    button->text_color = text_color;
}

void        button_set_text_hover_color(Button* button, Color text_hover_color)
{
    button->text_hover_color = text_hover_color;
}

void        button_set_text_click_color(Button* button, Color text_click_color)
{
    button->text_click_color = text_click_color;
}

//******************************* Unload *******************************//

void        button_unload_texture(Button* button)
{
    UnloadTexture(button->texture);
}


