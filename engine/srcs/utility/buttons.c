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
#include "../../../library/libft/libft.h"

Rectangle rectangle_addition(Rectangle rect01, Rectangle rect02);
void    draw_rectangle_borders(Rectangle rect, Color color, int thickness);

//******************************** Init ********************************//

Button		button_init(Vector2 pos, Vector2 size, Color bg_color,
				Color text_color, char* texturePath, char* text, fl32 scale, int nbr)
{
    Button button;

    button.rect.x = pos.x;
    button.rect.y = pos.y;
    button.rect.width = size.x;
    button.rect.height = size.y;
    button.bg_color = bg_color;
    button.text_color = text_color;
    button.texture = LoadTexture(texturePath);
    button.nbr = nbr;
    button.scale = scale;
    button.isClicked = false;
    button.isAllocate = false;
    button.texture = (Texture2D){0};
    button.texture_hover = (Texture2D){0};
    button.texture_click = (Texture2D){0};
    
    if (text != NULL)
    {
        button.text = (char*)de_allocate(sizeof(char) * (ft_strlen(text) + 1), MEMORY_TAG_BUTTONS);
        ft_strlcpy(button.text, text, ft_strlen(text) + 1);
        button.isAllocate = true;
    }

    // DE_DEBUG("Play text : %s", button.text);

    return (button);
}

void    button_unload(Button* button)
{
    // DE_DEBUG("Free In Button");
    UnloadTexture(button->texture);
    UnloadTexture(button->texture_hover);
    UnloadTexture(button->texture_click);

    if (button->isAllocate == true)
    {
        // DE_WARNING("Free In Button");
        // DE_WARNING("Button text: %s", button->text);
        de_free(button->text, sizeof(char) * (ft_strlen(button->text) + 1), MEMORY_TAG_BUTTONS);
    }
}

void    draw_button(Button const button, intptr_t fontSize, sint32 spacing,
            sint32 borderThick, Color borderColor, Vector2 cameraOrigin)
{
    Vector2 mousePos = GetMousePosition();
    Vector2 textPos = {button.rect.x + button.rect.width / 2 , button.rect.y + button.rect.height / 2};

    if (button.isAllocate)
    {
        Vector2 textVec = MeasureTextEx(button.font, button.text, fontSize ? fontSize : button.font.baseSize, spacing);
        textPos.x -= textVec.x / 2;
        textPos.y -= textVec.y / 2;
    }

    Rectangle hitBox = button.rect;
    hitBox.x += cameraOrigin.x;
    hitBox.y += cameraOrigin.y;

    if (CheckCollisionPointRec(mousePos, hitBox))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (button.texture_click.id > 0)
            {
                DE_WARNING("Not Good");
                DrawTextureEx(button.texture_click, (Vector2){button.rect.x, button.rect.y},
                    0, button.scale, WHITE);
            }
            else
            {
                DrawRectangleRec(button.rect, button.bg_click_color);
                if (button.isAllocate)
                {
                    DrawTextEx(button.font, button.text, textPos,
                        fontSize ? fontSize : button.font.baseSize, spacing, button.text_color);
                }
            }

            draw_rectangle_borders(button.rect, borderColor, borderThick);
            return;
        }

        if (button.texture_hover.id > 0)
        {
            //  DE_WARNING("Not Good");
            DrawTextureEx(button.texture_hover, (Vector2){button.rect.x, button.rect.y},
                0, button.scale, WHITE);
        }
        else
        {
            DrawRectangleRec(button.rect, button.bg_hover_color);
            if (button.isAllocate)
            {
                DrawTextEx(button.font, button.text, textPos,
                    fontSize ? fontSize : button.font.baseSize, spacing, button.text_color);
            }
        }
    }
    else
    {
        if (button.texture.id > 0)
        {
            //  DE_WARNING("Not Good");
            DrawTextureEx(button.texture, (Vector2){button.rect.x, button.rect.y},
                    0, button.scale, WHITE);
        }
        else
        {
            DrawRectangleRec(button.rect, button.bg_color);
            if (button.isAllocate)
            {
                DrawTextEx(button.font, button.text, textPos,
                        fontSize ? fontSize : button.font.baseSize, spacing, button.text_color);
            }
        }
    }
    draw_rectangle_borders(button.rect, borderColor, borderThick);
}

//******************************************************************************//
//***                               getters                                  ***//
//******************************************************************************//

Vector2     button_get_position(Button* const button)
{
    return ((Vector2){button->rect.x, button->rect.y});
}

Vector2     button_get_size(Button* button)
{
    return ((Vector2){button->rect.width, button->rect.height});
}

Color       button_get_bg_color(Button* const button)
{
    return (button->bg_color);
}

Color       button_get_bg_hover_color(Button* const button)
{
    return (button->bg_hover_color);
}

Color       button_get_bg_click_color(Button* const button)
{
    return (button->bg_click_color);
}

Texture2D   button_get_texture(Button* const button)
{
    return (button->texture);
}

int         button_get_nbr(Button* const button)
{
    return (button->nbr);
}

Rectangle   button_get_rectangle(Button* const button)
{
    return (button->rect);
}

Font        button_get_font(Button* const button)
{
    return (button->font);
}

Vector2     button_get_text_position(Button* const button)
{
    return (button->text_position);
}

Color       button_get_text_color(Button* const button)
{
    return (button->text_color);
}

Color       button_get_text_hover_color(Button* const button)
{
    return (button->text_hover_color);
}

Color       button_get_text_click_color(Button* const button)
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


