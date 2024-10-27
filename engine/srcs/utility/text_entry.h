#ifndef TEXT_ENTRY_H
# define TEXT_ENTRY_H

# include "engine_defines.h"
# include "struct_globale.h"

# include "raylib.h"

#include <stdint.h>

TextBox	create_textBox(Rectangle rect, int maxLength);
void    destroy_textBox(TextBox *textBox);

void    update_textBox(TextBox *textBox, Rectangle adjust, Font font, sint32 spacing, intptr_t fontSize);
void    draw_textBox(TextBox textBox, Font font, Color fontColor, sint32 spacing, intptr_t fontSize);
void    resize_textBox_len(TextBox *textBox, sint32 newMaxLen);
void    resize_texBox_rectangle(TextBox *textBox, Rectangle newSizeRec);

#endif