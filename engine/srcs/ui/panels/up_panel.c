/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--* PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* DATE:		     06-09-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--* FILE: 	     up_panel.c           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../includes/engine.h"
#include "../../../../library/drackengine_lib/logger.h"
#include "../../../includes/Config/menus.h"
#include "../../memory/dmemory.h"

void	change_state_mouse(MouseState mouse_state);
void    ftControlMainPanel(Engine *engine, Camera *camera);

extern bl8 refresh_frame;

void    draw_play_stop(Engine *engine)
{
    draw_button(&engine->buttonsMenuUp.play, (intptr_t)NULL, 1, 2, DARKPURPLE2, (Vector2){0, 0});
    draw_button(&engine->buttonsMenuUp.stop, (intptr_t)NULL, 1, 2, DARKPURPLE2, (Vector2){0, 0});
}

void	ftDrawMenuUp(Engine *engine)
{
	    draw_play_stop(engine);
}

void    unselect_tab(int *selectedTab, bl8 *isDropdownOpen)
{
    *isDropdownOpen = false;
    *selectedTab = -1;
}

void    change_view(Engine *engine, ViewState state, bl8 resize_window, int *selectedTab, bl8 *isDropdownOpen)
{
    engine->allStates.lastStateView = engine->allStates.currentStateView;
    engine->allStates.currentStateView = state;

    change_state_mouse(MOUSE_STATE_ON_OTHER_WINDOW);
    unselect_tab(selectedTab, isDropdownOpen);

    Rectangle *rec07 = &engine->allCameras->camera07.rectForCam;
    rec07->x = engine->screenSize.x / 2 - rec07->width / 2;
    rec07->y = engine->screenSize.y / 2 - rec07->height / 2;

    refresh_frame = true;
}

void ftDrawDropdownMenu(Engine *engine)
{
    static int selectedTab = -1;
    static bl8 isDropdownOpen = false;
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

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOver && engine->allStates.currentStateView == STATE_VIEW_ENGINE)
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

    if (engine->allStates.currentStateView != STATE_VIEW_ENGINE)
    {
        return;
    }

    // Dessiner le menu déroulant si ouvert
    if (isDropdownOpen && selectedTab != -1)
    {
        DrawRectangleRec(dropdownRect, RAYWHITE);
        DrawRectangleLinesEx(dropdownRect, 1, BLACK);

        // TODO: Add options from enum
        const char *files[] = {"New", "Open", "Save", "Save as", "Export", "Exit"};
        const char *edit[] = {"Undo", "Redo", "Cut", "Copy", "Paste"};
        const char *settings[] = {"Engine", "Project", "Options"};
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
                            change_view(engine, STATE_VIEW_FILES_NEW_PROJECT, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (files[i] && files[i] == "Open")
                        {
                            change_view(engine, STATE_VIEW_FILES_OPEN_PROJECT, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (files[i] && files[i] == "Save")
                        {
                            change_view(engine, STATE_VIEW_FILES_SAVE, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (files[i] && files[i] == "Save as")
                        {
                            change_view(engine, STATE_VIEW_FILES_SAVE_AS, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (files[i] && files[i] == "Export")
                        {
                            change_view(engine, STATE_VIEW_FILES_EXPORT, true, &selectedTab, &isDropdownOpen);
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
                            change_view(engine, STATE_VIEW_EDIT_UNDO, false, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Redo")
                        {
                            change_view(engine, STATE_VIEW_EDIT_REDO, false, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Cut")
                        {
                            change_view(engine, STATE_VIEW_EDIT_CUT, false, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Copy")
                        {
                            change_view(engine, STATE_VIEW_EDIT_COPY, false, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (edit[i] && edit[i] == "Paste")
                        {
                            change_view(engine, STATE_VIEW_EDIT_PASTE, false, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        break;
                    case (enum MainMenus)VIEW:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (settings[i] && settings[i] == "Engine")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_ENGINE, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (settings[i] && settings[i] == "Project")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_PROJECT, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (settings[i] && settings[i] == "Options")
                        {
                            change_view(engine, STATE_VIEW_SETTINGS_OPTIONS, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        break;
                    case (enum MainMenus)HELP:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (help[i] && help[i] == "About")
                        {
                            change_view(engine, STATE_VIEW_HELP_ABOUT, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (help[i] && help[i] == "Documentation")
                        {
                            change_view(engine, STATE_VIEW_HELP_DOCUMENTATION, true, &selectedTab, &isDropdownOpen);
                            break;
                        }
                        else if (help[i] && help[i] == "Support")
                        {
                            change_view(engine, STATE_VIEW_HELP_SUPPORT, true, &selectedTab, &isDropdownOpen);
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
        unselect_tab(&selectedTab, &isDropdownOpen);
    }
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Engine *engine, Camera2D *camera)
{
	(void)camera;
	ftDrawMenuUp(engine);
}
