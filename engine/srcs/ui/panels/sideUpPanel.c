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

// void	ftSelectItemsTop(Engine *engine, Camera2D *camera)
// {

// 	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
// 	{
// 		Vector2 mousePos = GetMousePosition();
// 		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);
// 		Rectangle item = game->buttonsMenuUp.play.ftReturnRectangle();

// 		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != -1)
// 		{
// 			game->ctMode = -1;
// 		}
// 		item = game->buttonsMenuUp.stop.ftReturnRectangle();
// 		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != 1)
// 		{
// 			game->ctMode = 1;
// 		}
// 	}
// }

void    draw_play_stop(Engine *engine)
{
    Vector2 mousePos = GetMousePosition();
    
    // Bouton Play
    Rectangle playRect = (Rectangle){
        button_get_position(engine->buttonsMenuUp.play).x,
        button_get_position(engine->buttonsMenuUp.play).y,
        engine->buttonsMenuUp.play->texture.width * engine->buttonsMenuUp.play->scale,
        engine->buttonsMenuUp.play->texture.height * engine->buttonsMenuUp.play->scale
    };
    
    // Bouton Stop
    Rectangle stopRect = (Rectangle){
        button_get_position(engine->buttonsMenuUp.stop).x,
        button_get_position(engine->buttonsMenuUp.stop).y,
        engine->buttonsMenuUp.stop->texture.width * engine->buttonsMenuUp.stop->scale,
        engine->buttonsMenuUp.stop->texture.height * engine->buttonsMenuUp.stop->scale
    };

    // Vérifier si la souris est sur le bouton Play
    if (CheckCollisionPointRec(mousePos, playRect)) {
        DrawTextureEx(engine->buttonsMenuUp.play->texture_hover,
            button_get_position(engine->buttonsMenuUp.play), 0, engine->buttonsMenuUp.play->scale, WHITE);
    } else {
        DrawTextureEx(engine->buttonsMenuUp.play->texture,
            button_get_position(engine->buttonsMenuUp.play), 0, engine->buttonsMenuUp.play->scale, WHITE);
    }

    // Vérifier si la souris est sur le bouton Stop
    if (CheckCollisionPointRec(mousePos, stopRect)) {
        DrawTextureEx(engine->buttonsMenuUp.stop->texture_hover,
            button_get_position(engine->buttonsMenuUp.stop), 0, engine->buttonsMenuUp.stop->scale, WHITE);
    } else {
        DrawTextureEx(engine->buttonsMenuUp.stop->texture,
            button_get_position(engine->buttonsMenuUp.stop), 0, engine->buttonsMenuUp.stop->scale, WHITE);
    }
    // DrawTextureEx(engine->buttonsMenuUp.play->texture,
	// 	button_get_position(engine->buttonsMenuUp.play), 0, engine->buttonsMenuUp.play->scale, WHITE);
	// DrawTextureEx(engine->buttonsMenuUp.stop->texture,
	// 	button_get_position(engine->buttonsMenuUp.stop), 0, engine->buttonsMenuUp.stop->scale, WHITE);
}

void	ftDrawMenuUp(Engine *engine)
{
	// (void)engine;
    // Vector2 pos = {0, 0};
    // DE_DEBUG("Play texture : %f, %f", engine->buttonsMenuUp.play->texture.width, engine->buttonsMenuUp.play->texture.height);
	    draw_play_stop(engine);
	// if (game->ctMenuUpButtons == 1) // Button Top Right
	// {
	// 	DrawTextureEx(game->buttonsMenuUp.buttonColorOpen.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonColorOpen.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonControlClose.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonListClose.ftReturnPosition(), 0, 1, WHITE);
	// }
	// else if (game->ctMenuUpButtons == 2) // Left Button Top Right
	// {
	// 	DrawTextureEx(game->buttonsMenuUp.buttonListOpen.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonListOpen.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonControlClose.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonColorClose.ftReturnPosition(), 0, 1, WHITE);
	// }
	// else if (game->ctMenuUpButtons == 0) // Middle Button Top Right
	// {
	// 	DrawTextureEx(game->buttonsMenuUp.buttonControlOpen.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonControlOpen.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonColorClose.ftReturnPosition(), 0, 1, WHITE);
	// 	DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnTexture(),
	// 		game->buttonsMenuUp.buttonListClose.ftReturnPosition(), 0, 1, WHITE);
	// }
}

void ftDrawDropdownMenu(Engine *engine)
{
	(void)engine;
    static int selectedTab = -1;
    static bool isDropdownOpen = false;
    static Rectangle dropdownRect = {0};

    // Dessiner les onglets
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
                const char *options[] = {"Banane", "Option 2", "Option 3"};
                int numOptions = sizeof(options) / sizeof(options[0]);
                int maxWidth = tabWidth;
                for (int j = 0; j < numOptions; j++)
                {
                    int optionWidth = MeasureText(options[j], fontSize) + 2 * padding;
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

        const char *options[] = {"Banane", "Option 2", "Option 3"};
        int numOptions = sizeof(options) / sizeof(options[0]);
        
        for (int i = 0; i < numOptions; i++)
        {
            Rectangle optionRect = {dropdownRect.x, dropdownRect.y + i * 30, dropdownRect.width, 30};
            Vector2 mousePos = GetMousePosition();
            bool isMouseOverOption = CheckCollisionPointRec(mousePos, optionRect);
            
            DrawRectangleRec(optionRect, isMouseOverOption ? LIGHTGRAY : RAYWHITE);
            DrawText(options[i], optionRect.x + padding, optionRect.y + 5, fontSize, BLACK);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOverOption)
            {
                clickedOutside = false;  // Le clic n'est pas en dehors
                // Action pour l'option sélectionnée
                isDropdownOpen = false;
                selectedTab = -1;
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


	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	// {
	// 	Vector2 mousePos = game->mouse.pos;
	// 	Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

	// 	Rectangle item = game->buttonsMenuUp.buttonColorOpen.ftReturnRectangle();
	// 	if (CheckCollisionPointRec(rayPos, item))	// Color panel
	// 	{
	// 		game->ctMenuUpButtons = 1;
	// 	}
	// 	item = game->buttonsMenuUp.buttonControlOpen.ftReturnRectangle();
	// 	if (CheckCollisionPointRec(rayPos, item)) // Control panel
	// 	{
	// 		game->ctMenuUpButtons = 0;
	// 	}
	// 	item = game->buttonsMenuUp.buttonListOpen.ftReturnRectangle();
	// 	if (CheckCollisionPointRec(rayPos, item)) // List panel
	// 	{
	// 		game->ctMenuUpButtons = 2;
	// 	}
	// }
}
