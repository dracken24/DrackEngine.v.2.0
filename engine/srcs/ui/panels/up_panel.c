/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--* PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* DATE:		     06-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* FILE: 	     up_panel.c           *--*            | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../includes/engine.h"
#include "../../../../library/drackengine_lib/logger.h"
#include "../../../includes/Config/menus.h"
#include "../../memory/dmemory.h"

void    draw_play_stop(Engine *engine)
{
    Vector2 mousePos = GetMousePosition();
    
    // Bouton Play
    Rectangle playRect = (Rectangle)
    {
        button_get_position(engine->buttonsMenuUp.play).x,
        button_get_position(engine->buttonsMenuUp.play).y,
        engine->buttonsMenuUp.play->texture.width * engine->buttonsMenuUp.play->scale,
        engine->buttonsMenuUp.play->texture.height * engine->buttonsMenuUp.play->scale
    };
    
    // Bouton Stop
    Rectangle stopRect = (Rectangle)
    {
        button_get_position(engine->buttonsMenuUp.stop).x,
        button_get_position(engine->buttonsMenuUp.stop).y,
        engine->buttonsMenuUp.stop->texture.width * engine->buttonsMenuUp.stop->scale,
        engine->buttonsMenuUp.stop->texture.height * engine->buttonsMenuUp.stop->scale
    };

    // Vérifier si la souris est sur le bouton Play
    if (CheckCollisionPointRec(mousePos, playRect))
    {
        DrawTextureEx(engine->buttonsMenuUp.play->texture_hover,
            button_get_position(engine->buttonsMenuUp.play), 0, engine->buttonsMenuUp.play->scale, WHITE);
    }
    else
    {
        DrawTextureEx(engine->buttonsMenuUp.play->texture,
            button_get_position(engine->buttonsMenuUp.play), 0, engine->buttonsMenuUp.play->scale, WHITE);
    }

    // Vérifier si la souris est sur le bouton Stop
    if (CheckCollisionPointRec(mousePos, stopRect))
    {
        DrawTextureEx(engine->buttonsMenuUp.stop->texture_hover,
            button_get_position(engine->buttonsMenuUp.stop), 0, engine->buttonsMenuUp.stop->scale, WHITE);
    }
    else
    {
        DrawTextureEx(engine->buttonsMenuUp.stop->texture,
            button_get_position(engine->buttonsMenuUp.stop), 0, engine->buttonsMenuUp.stop->scale, WHITE);
    }
}

void	ftDrawMenuUp(Engine *engine)
{
	    draw_play_stop(engine);
}

void    change_view(Engine *engine, ViewState state, bl8 resize_window)
{
    engine->lastStateView = engine->currentStateView;
    engine->currentStateView = state;
    if (resize_window)
    {
        engine->screenSizeWindow = WINDOW_OTHERS;
        SetWindowSize(engine->screenSizeWindow.x, engine->screenSizeWindow.y);
    }
}

void ftDrawDropdownMenu(Engine *engine)
{
	(void)engine;
    static int selectedTab = -1;
    static bool isDropdownOpen = false;
    static Rectangle dropdownRect = {0};

    // Dessiner les onglets
    // const char *tabs[] = {"Files", "Edit", "Settings", "Help"};
    const char *tabs[] = {"Files", "Edit", "Settings", "Help"};
    int numTabs = sizeof(tabs) / sizeof(tabs[0]);
    int tabHeight = CAMERA_UP_BAR;
    int startX = 5;
    int startY = 0;
    int spacing = 1;
    int fontsize = 18;
    int padding = 10;

    Font    font = engine->fonts.defaultFont;

    bool clickedOutside = true;

    for (int i = 0; i < numTabs; i++)
    {
        int tabWidth = MeasureText(tabs[i], fontsize) + 2 * padding;
        Rectangle tabRect = {startX, startY, tabWidth, tabHeight};
        
        Vector2 mousePos = GetMousePosition();
        bool isMouseOver = CheckCollisionPointRec(mousePos, tabRect);
        
        Color tabColor = (i == selectedTab && isDropdownOpen) ? GRAY : (isMouseOver ? LIGHTGRAY : WHITE);
        
        DrawRectangleRec(tabRect, tabColor);
        DrawRectangleLinesEx(tabRect, 1, BLACK);
        DrawTextEx(font, tabs[i], (Vector2){tabRect.x + padding, tabRect.y + 5}, font.baseSize, spacing, BLACK);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOver)
        {
            clickedOutside = false;  // Le clic n'est pas en dehors
            if (selectedTab == i && isDropdownOpen)
            {
                isDropdownOpen = false;
                selectedTab = -1;
            }
            else
            {
                selectedTab = i;
                isDropdownOpen = true;
                
                // Ajuster la largeur du menu déroulant
                const char *options[] = {"Documentation"};
                int numOptions = sizeof(options) / sizeof(options[0]);
                int maxWidth = tabWidth;
                for (int j = 0; j < numOptions; j++)
                {
                    int optionWidth = MeasureText(options[j], font.baseSize) + 4 * padding;
                    if (optionWidth > maxWidth)
                        maxWidth = optionWidth;
                }
                
                dropdownRect = (Rectangle){tabRect.x, tabRect.y + tabRect.height, maxWidth, numOptions * 24};
            }
        }

        startX += tabWidth + 1;
    }

    // Dessiner le menu déroulant si ouvert
    if (isDropdownOpen && selectedTab != -1)
    {
        DrawRectangleRec(dropdownRect, RAYWHITE);
        DrawRectangleLinesEx(dropdownRect, 1, BLACK);

        // TODO: Add options from enum
        const char *files[] = {"New", "Open", "Save", "Save as", "Export", "Exit"};
        const char *edit[] = {"Undo", "Redo", "Cut", "Copy", "Paste"};
        const char *settings[] = {"Language", "Theme", "Options"};
        const char *help[] = {"About", "Documentation", "Support"};

        int numOptions;
        switch (selectedTab)
        {
            case 0:
                numOptions = sizeof(files) / sizeof(files[0]);
                break;
            case 1:
                numOptions = sizeof(edit) / sizeof(edit[0]);
                break;
            case 2:
                numOptions = sizeof(settings) / sizeof(settings[0]);
                break;
            case 3:
                numOptions = sizeof(help) / sizeof(help[0]);
                break;
            default:
                break;
        }
        
        for (int i = 0; i < numOptions; i++)
        {
            Rectangle optionRect = {dropdownRect.x, dropdownRect.y + i * 24, dropdownRect.width, 24};
            Vector2 mousePos = GetMousePosition();
            bool isMouseOverOption = CheckCollisionPointRec(mousePos, optionRect);
            
            DrawRectangleRec(optionRect, isMouseOverOption ? LIGHTGRAY : RAYWHITE);
            switch (selectedTab)
            {
                case 0:
                    DrawTextEx(font, files[i], (Vector2){optionRect.x + padding, optionRect.y + 2}, font.baseSize, spacing, BLACK);
                    break;
                case 1:
                    DrawTextEx(font, edit[i], (Vector2){optionRect.x + padding, optionRect.y + 2}, font.baseSize, spacing, BLACK);
                    break;
                case 2:
                    DrawTextEx(font, settings[i], (Vector2){optionRect.x + padding, optionRect.y + 2}, font.baseSize, spacing, BLACK);
                    break;
                case 3:
                    DrawTextEx(font, help[i], (Vector2){optionRect.x + padding, optionRect.y + 2}, font.baseSize, spacing, BLACK);
                    break;
                default:
                    break;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOverOption)
            {
                switch (selectedTab)
                {
                    case (enum MainMenus)FILES:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (files[i] && files[i] == "New")
                        {
                            change_view(engine, STATE_VIEW_FILES_NEW_PROJECT, true);
                            break;
                        }
                        else if (files[i] && files[i] == "Open")
                        {
                            change_view(engine, STATE_VIEW_FILES_OPEN_PROJECT, true);
                            break;
                        }
                        else if (files[i] && files[i] == "Save")
                        {
                            change_view(engine, STATE_VIEW_FILES_SAVE, true);
                            break;
                        }
                        else if (files[i] && files[i] == "Save as")
                        {
                            change_view(engine, STATE_VIEW_FILES_SAVE_AS, true);
                            break;
                        }
                        else if (files[i] && files[i] == "Export")
                        {
                            change_view(engine, STATE_VIEW_FILES_EXPORT, true);
                            break;
                        }
                        else if (files[i] && files[i] == "Exit")
                        {
                            engine->exitCt = true;
                            break;
                        }
                        break;
                    case (enum MainMenus)EDIT:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (edit[i] && edit[i] == "Undo")
                        {
                            change_view(engine, STATE_VIEW_EDIT_UNDO, false);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Redo")
                        {
                            change_view(engine, STATE_VIEW_EDIT_REDO, false);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Cut")
                        {
                            change_view(engine, STATE_VIEW_EDIT_CUT, false);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Copy")
                        {
                            change_view(engine, STATE_VIEW_EDIT_COPY, false);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Paste")
                        {
                            change_view(engine, STATE_VIEW_EDIT_PASTE, false);
                            break;
                        }
                        break;
                    case (enum MainMenus)VIEW:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (settings[i] && settings[i] == "Language")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_LANGUAGE, true);
                            break;
                        }
                        else if (settings[i] && settings[i] == "Theme")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_THEME, true);
                            break;
                        }
                        else if (settings[i] && settings[i] == "Options")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_OPTIONS, true);
                            break;
                        }
                        break;
                    case (enum MainMenus)HELP:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (help[i] && help[i] == "About")
                        {
                            change_view(engine, STATE_VIEW_HELP_ABOUT, true);
                            break;
                        }
                        else if (help[i] && help[i] == "Documentation")
                        {
                            change_view(engine, STATE_VIEW_HELP_DOCUMENTATION, true);
                            break;
                        }
                        else if (help[i] && help[i] == "Support")
                        {
                            change_view(engine, STATE_VIEW_HELP_SUPPORT, true);
                            break;
                        }
                        break;
                default:
                    break;
                }
            }
        }
    }

    // Fermer le menu si on clique en dehors
    if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && clickedOutside)
    {
        isDropdownOpen = false;
        selectedTab = -1;
    }
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Engine *engine, Camera2D *camera)
{
	(void)camera;
	ftDrawMenuUp(engine);
}
