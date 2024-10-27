/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackEngine   PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:        text_entry.c             *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "text_entry.h"
#include "../memory/dmemory.h"
#include "../../library/drackengine_lib/logger.h"
#include "utility.h"
#include "struct_globale.h"

#include <string.h>

#define KEY_REPEAT_DELAY 0.5f
#define KEY_REPEAT_RATE 0.05f

TextBox create_textBox(Rectangle rect, int maxLength)
{
    TextBox textBox;
    textBox.rect = rect;
    textBox.text = (char*)de_allocate(maxLength + 1, MEMORY_TAG_ENGINE);
    textBox.text[0] = '\0';
    textBox.textSize = 0;
    textBox.maxLength = maxLength;
    textBox.isActive = false;
    textBox.cursorPosition = 0;
    textBox.textOffset = 0;
    return textBox;
}

void    update_textBox(TextBox *textBox, Rectangle adjust, Font font, sint32 spacing, intptr_t fontSize)
{
    static float backspaceTimer = 0.0f;
    static float deleteTimer = 0.0f;
    static float leftArrowTimer = 0.0f;
    static float rightArrowTimer = 0.0f;
    static bool isBackspaceHeld = false;
    static bool isDeleteHeld = false;
    static bool isLeftArrowHeld = false;
    static bool isRightArrowHeld = false;

    Vector2 mousePoint = GetMousePosition();
    Rectangle adjustedRect = {
        textBox->rect.x + adjust.x,
        textBox->rect.y + adjust.y,
        textBox->rect.width,
        textBox->rect.height
    };

    if (CheckCollisionPointRec(mousePoint, adjustedRect))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            textBox->isActive = true;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        textBox->isActive = false;
    }

    if (textBox->isActive)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (textBox->textSize < textBox->maxLength))
            {
                // Insert the character at the cursor position
                memmove(&textBox->text[textBox->cursorPosition + 1], &textBox->text[textBox->cursorPosition], textBox->textSize - textBox->cursorPosition);
                textBox->text[textBox->cursorPosition] = (char)key;
                textBox->textSize++;
                textBox->cursorPosition++;
                textBox->text[textBox->textSize] = '\0';
            }
            key = GetCharPressed();
        }

        // Backspace key handling
        if (IsKeyDown(KEY_BACKSPACE))
        {
            if (!isBackspaceHeld)
            {
                if (textBox->cursorPosition > 0)
                {
                    // delete the character before the cursor
                    memmove(&textBox->text[textBox->cursorPosition - 1], &textBox->text[textBox->cursorPosition], textBox->textSize - textBox->cursorPosition + 1);
                    textBox->textSize--;
                    textBox->cursorPosition--;
                    textBox->text[textBox->textSize] = '\0';
                }
                isBackspaceHeld = true;
                backspaceTimer = 0.0f;
            }
            else
            {
                backspaceTimer += GetFrameTime();
                if (backspaceTimer > KEY_REPEAT_DELAY)
                {
                    if (textBox->cursorPosition > 0 && backspaceTimer - KEY_REPEAT_DELAY > KEY_REPEAT_RATE)
                    {
                        // delete the character before the cursor
                        memmove(&textBox->text[textBox->cursorPosition - 1], &textBox->text[textBox->cursorPosition], textBox->textSize - textBox->cursorPosition + 1);
                        textBox->textSize--;
                        textBox->cursorPosition--;
                        textBox->text[textBox->textSize] = '\0';
                        backspaceTimer = KEY_REPEAT_DELAY;
                    }
                }
            }
        }
        else
        {
            isBackspaceHeld = false;
        }

        // Delete key handling
        if (IsKeyDown(KEY_DELETE))
        {
            if (!isDeleteHeld)
            {
                if (textBox->cursorPosition < textBox->textSize)
                {
                    // delete the character after the cursor
                    memmove(&textBox->text[textBox->cursorPosition], &textBox->text[textBox->cursorPosition + 1], textBox->textSize - textBox->cursorPosition);
                    textBox->textSize--;
                    textBox->text[textBox->textSize] = '\0';
                }
                isDeleteHeld = true;
                deleteTimer = 0.0f;
            }
            else
            {
                deleteTimer += GetFrameTime();
                if (deleteTimer > KEY_REPEAT_DELAY)
                {
                    if (textBox->cursorPosition < textBox->textSize && deleteTimer - KEY_REPEAT_DELAY > KEY_REPEAT_RATE)
                    {
                        // delete the character after the cursor
                        memmove(&textBox->text[textBox->cursorPosition], &textBox->text[textBox->cursorPosition + 1], textBox->textSize - textBox->cursorPosition);
                        textBox->textSize--;
                        textBox->text[textBox->textSize] = '\0';
                        deleteTimer = KEY_REPEAT_DELAY;
                    }
                }
            }
        }
        else
        {
            isDeleteHeld = false;
        }

        // Left arrow key handling
        if (IsKeyDown(KEY_LEFT))
        {
            if (!isLeftArrowHeld)
            {
                if (textBox->cursorPosition > 0)
                {
                    textBox->cursorPosition--;
                }
                isLeftArrowHeld = true;
                leftArrowTimer = 0.0f;
            }
            else
            {
                leftArrowTimer += GetFrameTime();
                if (leftArrowTimer > KEY_REPEAT_DELAY)
                {
                    if (textBox->cursorPosition > 0 && leftArrowTimer - KEY_REPEAT_DELAY > KEY_REPEAT_RATE)
                    {
                        textBox->cursorPosition--;
                        leftArrowTimer = KEY_REPEAT_DELAY;
                    }
                }
            }
        }
        else
        {
            isLeftArrowHeld = false;
        }

        // Right arrow key handling
        if (IsKeyDown(KEY_RIGHT))
        {
            if (!isRightArrowHeld)
            {
                if (textBox->cursorPosition < textBox->textSize)
                {
                    textBox->cursorPosition++;
                }
                isRightArrowHeld = true;
                rightArrowTimer = 0.0f;
            }
            else
            {
                rightArrowTimer += GetFrameTime();
                if (rightArrowTimer > KEY_REPEAT_DELAY)
                {
                    if (textBox->cursorPosition < textBox->textSize && rightArrowTimer - KEY_REPEAT_DELAY > KEY_REPEAT_RATE)
                    {
                        textBox->cursorPosition++;
                        rightArrowTimer = KEY_REPEAT_DELAY;
                    }
                }
            }
        }
        else
        {
            isRightArrowHeld = false;
        }

        // Adjust the text offset
        float actualFontSize = fontSize ? (float)fontSize : (float)font.baseSize;
        float visibleWidth = textBox->rect.width - 10;  // 10 pixels of margin
        float textWidth = MeasureTextEx(font, textBox->text, actualFontSize, spacing).x;
        float cursorX = MeasureTextEx(font, TextSubtext(textBox->text, 0, textBox->cursorPosition), actualFontSize, spacing).x;

        // Adjust the text offset so the cursor is always visible
        if (cursorX - textBox->textOffset > visibleWidth)
        {
            textBox->textOffset = cursorX - visibleWidth + actualFontSize;
        }
        else if (cursorX - textBox->textOffset < 0)
        {
            textBox->textOffset = cursorX;
        }

        // Ensure the text doesn't go too far to the left
        if (textWidth - textBox->textOffset < visibleWidth && textWidth > visibleWidth)
        {
            textBox->textOffset = textWidth - visibleWidth;
        }

        // Ensure the offset is never negative
        textBox->textOffset = fmaxf(0, textBox->textOffset);
    }
}

void    draw_textBox(TextBox textBox, Font font, Color fontColor, sint32 spacing, intptr_t fontSize)
{
    DrawRectangleRec(textBox.rect, LIGHTGRAY);
    DrawRectangleLinesEx(textBox.rect, 2, textBox.isActive ? LIGHTDARKGREEN : DARKGRAY);

    float actualFontSize = fontSize ? (float)fontSize : (float)font.baseSize;
    Vector2 pos = {textBox.rect.x + 5 - textBox.textOffset, textBox.rect.y + (textBox.rect.height - actualFontSize) / 2};
    
    // Draw the text with a clipping rectangle
    BeginScissorMode(textBox.rect.x, textBox.rect.y, textBox.rect.width, textBox.rect.height);
    if (textBox.textSize > 0)
    {
        DrawTextEx(font, textBox.text, pos, actualFontSize, spacing, fontColor);
    }
    EndScissorMode();
    
    // Draw the cursor
    if (textBox.isActive)
    {
        float cursorX = pos.x + MeasureTextEx(font, TextSubtext(textBox.text, 0, textBox.cursorPosition), actualFontSize, spacing).x;
        if (cursorX >= textBox.rect.x && cursorX <= textBox.rect.x + textBox.rect.width)
        {
            DrawLineEx((Vector2){cursorX, textBox.rect.y + 2}, 
                       (Vector2){cursorX, textBox.rect.y + textBox.rect.height - 2}, 
                       2, MAROON);
        }
    }

    // Debugging text size
    // char debugText[50];
    // snprintf(debugText, sizeof(debugText), "Text size: %d", textBox.textSize);
    // DrawText(debugText, 10, 10, 20, RED);
}

void    resize_textBox_len(TextBox *textBox, sint32 newMaxLen)
{
    de_free(textBox->text, textBox->maxLength + 1, MEMORY_TAG_ENGINE);
    textBox->text = (char*)de_allocate(newMaxLen + 1, MEMORY_TAG_ENGINE);
}

void    resize_texBox_rectangle(TextBox *textBox, Rectangle newSizeRec)
{
    textBox->rect = newSizeRec;
}

void    destroy_textBox(TextBox *textBox)
{
    de_free(textBox->text, textBox->maxLength + 1, MEMORY_TAG_ENGINE);
}
