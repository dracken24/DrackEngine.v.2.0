#ifndef UTILITY_H
# define UTILITY_H

# include "raylib.h"

void		open_window(Vector2 screenSize, Vector2 minSize, char *title, bool resizable);
void		print_memory_usage(const char* phase);
Rectangle	rectangle_addition(Rectangle rect01, Rectangle rect02);

#endif