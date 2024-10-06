/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  sideUpPanel.hpp         *--*             | */
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
    int tabHeight = 30;
    int startX = 5;
    int startY = 0;
    int fontSize = 20;
    int padding = 10;

    bool clickedOutside = true;

    for (int i = 0; i < numTabs; i++)
    {
        int tabWidth = MeasureText(tabs[i], fontSize) + 2 * padding;
        Rectangle tabRect = {startX, startY, tabWidth, tabHeight};
        
        Vector2 mousePos = GetMousePosition();
        bool isMouseOver = CheckCollisionPointRec(mousePos, tabRect);
        
        Color tabColor = (i == selectedTab && isDropdownOpen) ? GRAY : (isMouseOver ? LIGHTGRAY : WHITE);
        
        DrawRectangleRec(tabRect, tabColor);
        DrawRectangleLinesEx(tabRect, 1, BLACK);
        DrawText(tabs[i], tabRect.x + padding, tabRect.y + 5, fontSize, BLACK);

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
                const char *options[] = {"Documentation", "Option 2", "Option 3"};
                int numOptions = sizeof(options) / sizeof(options[0]);
                int maxWidth = tabWidth;
                for (int j = 0; j < numOptions; j++)
                {
                    int optionWidth = MeasureText(options[j], fontSize) + 4 * padding;
                    if (optionWidth > maxWidth)
                        maxWidth = optionWidth;
                }
                
                dropdownRect = (Rectangle){tabRect.x, tabRect.y + tabRect.height, maxWidth, numOptions * 30};
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
        const char *files[] = {"New", "Open", "Save", "Save as", "Export"};
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
            Rectangle optionRect = {dropdownRect.x, dropdownRect.y + i * 30, dropdownRect.width, 30};
            Vector2 mousePos = GetMousePosition();
            bool isMouseOverOption = CheckCollisionPointRec(mousePos, optionRect);
            
            DrawRectangleRec(optionRect, isMouseOverOption ? LIGHTGRAY : RAYWHITE);
            switch (selectedTab)
            {
                case 0:
                    DrawText(files[i], optionRect.x + padding, optionRect.y + 5, fontSize, BLACK);
                    break;
                case 1:
                    DrawText(edit[i], optionRect.x + padding, optionRect.y + 5, fontSize, BLACK);
                    break;
                case 2:
                    DrawText(settings[i], optionRect.x + padding, optionRect.y + 3, fontSize, BLACK);
                    break;
                case 3:
                    DrawText(help[i], optionRect.x + padding, optionRect.y + 3, fontSize, BLACK);
                    break;
                default:
                    break;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOverOption)
            {
                switch (selectedTab)
                {
                    case 0:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (files[i] && files[i] == "New")
                        {
                            menu_files_new();
                            break;
                        }
                        else if (files[i] && files[i] == "Open")
                        {
                            menu_files_open();
                            break;
                        }
                        else if (files[i] && files[i] == "Save")
                        {
                            menu_files_save();
                            break;
                        }
                        else if (files[i] && files[i] == "Save as")
                        {
                            menu_files_save_as();
                            break;
                        }
                        else if (files[i] && files[i] == "Export")
                        {
                            menu_files_export();
                            break;
                        }
                        break;
                    case 1:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (edit[i] && edit[i] == "Undo")
                        {
                            menu_edit_undo();
                            break;
                        }
                        else if (edit[i] && edit[i] == "Redo")
                        {
                            menu_edit_redo();
                            break;
                        }
                        else if (edit[i] && edit[i] == "Cut")
                        {
                            menu_edit_cut();
                            break;
                        }
                        else if (edit[i] && edit[i] == "Copy")
                        {
                            menu_edit_copy();
                            break;
                        }
                        else if (edit[i] && edit[i] == "Paste")
                        {
                            menu_edit_paste();
                            break;
                        }
                        break;
                    case 2:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (settings[i] && settings[i] == "Language")
                        {
                            menu_settings_language();
                            break;
                        }
                        else if (settings[i] && settings[i] == "Theme")
                        {
                            menu_settings_theme();
                            break;
                        }
                        else if (settings[i] && settings[i] == "Options")
                        {
                            menu_settings_options();
                            break;
                        }
                        break;
                    case 3:
                        // DE_DEBUG("Option selected: %d", selectedTab);
                        if (help[i] && help[i] == "About")
                        {
                            menu_help_about();
                            break;
                        }
                        else if (help[i] && help[i] == "Documentation")
                        {
                            menu_help_documentation();
                            break;
                        }
                        else if (help[i] && help[i] == "Support")
                        {
                            menu_help_support();
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
