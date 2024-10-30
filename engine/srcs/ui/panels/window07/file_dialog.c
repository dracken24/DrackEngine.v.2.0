/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    28-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:        file_dialog.c            *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "file_dialog.h"
#include "../../library/drackengine_lib/logger.h"
#include "../../../utility/buttons.h"
#include "../../../memory/dmemory.h"
#include "engine.h"
#include "struct_globale.h"

#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

extern Engine *g_engine;

void init_file_dialog(FileDialog* dialog, const char* initialPath, Rectangle camRect)
{
    dialog->isOpen = true;
    dialog->shouldClose = false;
    
    // Make sure the initial path is valid
    if (!initialPath || strlen(initialPath) == 0)
    {
        // Use the current directory if no path is provided
        if (getcwd(dialog->currentPath, sizeof(dialog->currentPath)) == NULL)
        {
            DE_ERROR("Failed to get current working directory");
            strcpy(dialog->currentPath, "/");
        }
    }
    else
    {
        strncpy(dialog->currentPath, initialPath, sizeof(dialog->currentPath) - 1);
        dialog->currentPath[sizeof(dialog->currentPath) - 1] = '\0';
    }
    
    DE_DEBUG("File dialog initialized with path: %s", dialog->currentPath);
    
    dialog->position = (Vector2){camRect.width / 2 - 250, camRect.height / 2 - 200};
    dialog->size = (Vector2){500, 400};
    dialog->selectedPath[0] = '\0';
    dialog->scrollOffset = 0;
}

static bool custom_button(Rectangle bounds, char* text, Vector2 camPos)
{
    // Create a temporary button without texture
    Button btn;
    memset(&btn, 0, sizeof(Button)); // Initialize all fields to 0

    btn.rect = bounds;
    btn.bg_color = DARKGRAY;
    btn.text_color = WHITE;
    btn.bg_hover_color = GRAY;
    btn.bg_click_color = LIGHTGRAY;
    btn.font = g_engine->fonts.defaultFont;
    btn.scale = 1.0f;

    // Draw the button
    draw_button(&btn, 20, 1, 2, DARKGRAY, camPos);
    DrawTextEx(btn.font, text, (Vector2){bounds.x + bounds.width / 2 - MeasureText(text, btn.font.baseSize / 2),
        bounds.y}, btn.font.baseSize, 1, btn.text_color);
    
    // Check if the button is clicked
    Vector2 mousePos = GetMousePosition();
    Rectangle hitBox = bounds;
    hitBox.x += camPos.x;
    hitBox.y += camPos.y;
    
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
                  CheckCollisionPointRec(mousePos, hitBox);

    if (clicked)
    {
        DE_DEBUG("Button clicked: %s", text);
    }

    button_unload(&btn);
    
    return clicked;
}

static Rectangle list_directory(FileDialog* dialog, Vector2 camPos)
{
    Rectangle viewArea = {
        dialog->position.x + 10,
        dialog->position.y + 60,
        dialog->size.x - 30,
        dialog->size.y - 130
    };

    // DE_DEBUG("Trying to open directory: %s", dialog->currentPath);
    DIR* dir = opendir(dialog->currentPath);
    if (!dir)
    {
        dir = opendir(getcwd(NULL, 0));
        if (!dir)
        {
            DE_ERROR("Cannot open directory: %s (errno: %d)", dialog->currentPath, errno);
            return viewArea;
        }
        ft_strlcpy(dialog->currentPath, getcwd(NULL, 0), sizeof(dialog->currentPath) - 1);
        dialog->currentPath[sizeof(dialog->currentPath) - 1] = '\0';
    }
    
    // Button to go up one level
    if (custom_button((Rectangle){dialog->position.x + 10, dialog->position.y + 30, 50, 20}, "..", camPos))
    {
        DE_DEBUG("Trying to go up from: %s", dialog->currentPath);
        char* lastSlash = strrchr(dialog->currentPath, '/');
        if (lastSlash && lastSlash != dialog->currentPath)
        {
            *lastSlash = '\0';
            DE_DEBUG("New path after going up: %s", dialog->currentPath);
        }
    }

    float contentHeight = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        contentHeight += 25;
    }
    closedir(dir);

    dir = opendir(dialog->currentPath);
    if (!dir)
    {
        return viewArea;
    }

    Rectangle collRec = viewArea;
    collRec.x += camPos.x;
    collRec.y += camPos.y;
    if (CheckCollisionPointRec(GetMousePosition(), collRec))
    {
        dialog->scrollOffset -= GetMouseWheelMove() * 30;
        
        float maxScroll = contentHeight - viewArea.height + 5;
        dialog->scrollOffset = Clamp(dialog->scrollOffset, 0, maxScroll > 0 ? maxScroll : 0);
    }

    Rectangle slideBox = (Rectangle){viewArea.x + viewArea.width + 3, viewArea.y, 10, viewArea.height};
    if (contentHeight > viewArea.height)
    {
        float scrollBarHeight = (viewArea.height / contentHeight) * viewArea.height;
        float scrollBarY = viewArea.y + (dialog->scrollOffset / contentHeight) * viewArea.height;
        
        DrawRectangleRec(slideBox, PURPLE);
        DrawRectangle(viewArea.x + viewArea.width + 3, scrollBarY,
            10, scrollBarHeight, DARKPURPLE);
    }
    else
    {
        DrawRectangleRec(slideBox, DARKPURPLE);
    }
    DrawRectangleLinesEx(slideBox, 2, DARKPURPLE);

    BeginScissorMode(viewArea.x, viewArea.y, viewArea.width, viewArea.height);
    
    float yPos = viewArea.y - dialog->scrollOffset;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char fullPath[1024];
        int result = snprintf(fullPath, sizeof(fullPath), "%s/%s", dialog->currentPath, entry->d_name);
        if (result < 0 || result >= sizeof(fullPath))
        {
            DE_WARNING("Path too long: %s/%s", dialog->currentPath, entry->d_name);
            continue;
        }
        
        struct stat statbuf;
        if (stat(fullPath, &statbuf) != 0)
        {
            DE_WARNING("Cannot stat file: %s (errno: %d)", fullPath, errno);
            continue;
        }

        bool isDir = S_ISDIR(statbuf.st_mode);
        char displayName[240];
        size_t nameLen = strlen(entry->d_name);
        
        if (nameLen > sizeof(displayName) - 6)
        {
            strncpy(displayName, entry->d_name, sizeof(displayName) - 7);
            strcat(displayName, "...");
        }
        else
        {
            strncpy(displayName, entry->d_name, sizeof(displayName) - 1);
            displayName[sizeof(displayName) - 1] = '\0';
        }
        
        char label[256];
        snprintf(label, sizeof(label), "%s%s", isDir ? "[D] " : "[F] ", displayName);
        
        if (custom_button((Rectangle){viewArea.x + 10, yPos + 5, viewArea.width - 20, 20}, label, camPos))
        {
            if (isDir)
            {
                DE_DEBUG("Trying to enter directory: %s", fullPath);
                strncpy(dialog->currentPath, fullPath, sizeof(dialog->currentPath) - 1);
                dialog->currentPath[sizeof(dialog->currentPath) - 1] = '\0';
                DE_DEBUG("New current path: %s", dialog->currentPath);
            }
        }
        yPos += 25;
    }
    EndScissorMode();
    closedir(dir);

    return viewArea;
}

void draw_file_dialog(FileDialog* dialog, Vector2 camPos)
{
    if (!dialog->isOpen)
    {
        return;
    }

    Font font = g_engine->fonts.defaultFont;

    // Draw the main window
    DrawRectangle(dialog->position.x, dialog->position.y, 
        dialog->size.x, dialog->size.y, Fade(RAYWHITE, 0.9f));
    DrawRectangleLinesEx((Rectangle){dialog->position.x, dialog->position.y, 
        dialog->size.x, dialog->size.y}, 4, DARKGRAY);

    // Title
    DrawTextEx(font, "Select Folder",  (Vector2){dialog->position.x + dialog->size.x / 2 -
        MeasureText("Select Folder", g_engine->fonts.defaultFont.baseSize - 2) / 2,
            dialog->position.y + 10}, 20, 1, BLACK);
    
    // Current Path
    DrawTextEx(font, "Path: ", (Vector2){dialog->position.x + 10,
        dialog->position.y + dialog->size.y - 60}, 14, 1, ORANGE);
    DrawTextEx(font, dialog->currentPath, (Vector2){dialog->position.x + 10 +
        MeasureTextEx(font, "Path: ", 14, 1).x, dialog->position.y +
            dialog->size.y - 60}, 14, 1, DARKGRAY);
    
    // List of files and directories
    BeginScissorMode(dialog->position.x, dialog->position.y + 50, 
        dialog->size.x, dialog->size.y - 100);
    EndScissorMode();
    Rectangle scrollRec = list_directory(dialog, camPos);
    DrawRectangleLinesEx((Rectangle){scrollRec.x, scrollRec.y,
        scrollRec.width, scrollRec.height}, 2, DARKPURPLE2);

    // Control buttons
    if (custom_button((Rectangle){dialog->position.x + dialog->size.x - 80, 
        dialog->position.y + dialog->size.y - 30, 70, 20}, "Select", camPos))
    {
        strncpy(dialog->selectedPath, dialog->currentPath, sizeof(dialog->selectedPath) - 1);
        dialog->shouldClose = true;
    }
    
    if (custom_button((Rectangle){dialog->position.x + dialog->size.x - 160, 
        dialog->position.y + dialog->size.y - 30, 70, 20}, "Close", camPos))
    {
        dialog->shouldClose = true;
    }
}

bl8 file_dialog_should_close(FileDialog* dialog)
{
    return dialog->shouldClose;
}
