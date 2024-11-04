/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 04-11-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    Buttons.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#pragma once

// #include <iostream>
#include <string>
#include <functional>

#include <raylib.h>

#include "../../../core/includes/engine_defines.h"


namespace DrackEngine::UI
{
    typedef void (*Callback)(void*);

    const Color DEFAULT_BG = (Color){245, 245, 245, 255};    // RAYWHITE
    const Color HOVER_BG = (Color){200, 200, 200, 255};      // LIGHTGRAY
    const Color CLICK_BG = (Color){130, 130, 130, 255};      // GRAY
    const Color TEXT_COLOR = (Color){0, 0, 0, 255};          // BLACK
    const Color W = (Color){255, 255, 255, 255};             // White

    class Button
    {
    //******************************************************************************//
    //***                       Constructors / Destructors                       ***//
    //******************************************************************************//

        public:
            Button();  // Constructeur par défaut
            Button(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
                const std::string& texturePath = "", const std::string& text = "", float scale = 1.0f);
            Button(const Button& other);  // Constructeur de copie
            Button& operator=(const Button& other);  // Opérateur d'affectation
            ~Button();  // Destructeur

    //******************************************************************************//
    //***                           Members Functions                            ***//
    //******************************************************************************//

            // Méthodes principales
            void draw(int fontSize = 0, int spacing = 0, int borderThick = 0,
                    Color borderColor = TEXT_COLOR, Vector2 cameraOrigin = (Vector2){0, 0}, bool skipUpdate = false);
            void unload();

    //******************************************************************************//
    //***                                 Setters                                ***//
    //******************************************************************************//

            void setPosition(Vector2 pos);
            void setSize(Vector2 size);
            void setBgColor(Color color);
            void setBgHoverColor(Color color);
            void setBgClickColor(Color color);
            void setTexture(const std::string& path);
            void setFont(Font newFont);
            void setTextPosition(Vector2 pos);
            void setTextColor(Color color);
            void setTextHoverColor(Color color);
            void setTextClickColor(Color color);
            void setText(const std::string& newText);

            void setCallback(Callback callback, void* userData = nullptr);

    //******************************************************************************//
    //***                                Getters                                 ***//
    //******************************************************************************//

            Vector2 getPosition()           const { return {rect.x, rect.y}; }
            Vector2 getSize()               const { return {rect.width, rect.height}; }
            Color getBgColor()              const { return bgColor; }
            Color getBgHoverColor()         const { return bgHoverColor; }
            Color getBgClickColor()         const { return bgClickColor; }
            const Texture2D& getTexture()   const { return texture; }
            Rectangle getRectangle()        const { return rect; }
            Font getFont()                  const { return font; }
            Vector2 getTextPosition()       const { return textPosition; }
            Color getTextColor()            const { return textColor; }
            Color getTextHoverColor()       const { return textHoverColor; }
            Color getTextClickColor()       const { return textClickColor; }

    //******************************************************************************//
    //***                                Variables                               ***//
    //******************************************************************************//

        private:
            Rectangle rect;
            Texture2D texture;
            Texture2D textureHover;
            Texture2D textureClick;
            Color bgColor;
            Color bgHoverColor;
            Color bgClickColor;

            std::string text;
            Font font;
            Vector2 textPosition;
            Color textColor;
            Color textHoverColor;
            Color textClickColor;

            bool isClicked;
            float scale;

            Callback onClickCallback;
            void* userData;

            void cleanup();
            void copyFrom(const Button& other);
    };
};
