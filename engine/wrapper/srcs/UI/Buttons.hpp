/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:         04-11-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    Buttons.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#pragma once

#include <iostream>
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
	    Button(); 
	    // Button(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
		// const std::string& texturePath = "", const std::string& text = "", float scale = 1.0f);
	    Button(const Button& other);
	    Button& operator=(const Button& other);
	    ~Button();

    //******************************************************************************//
    //***                           Members Functions                            ***//
    //******************************************************************************//

	    // Méthodes principales
		void	initButton(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
					const std::string& texturePath = "", const std::string& text = "", float scale = 1.0f);
	    void draw(int fontSize = 0, int spacing = 0, int borderThick = 0,
		    Color borderColor = TEXT_COLOR, Vector2 cameraOrigin = (Vector2){0, 0}, bool skipUpdate = false);
	    void unload();

    //******************************************************************************//
    //***                                 Setters                                ***//
    //******************************************************************************//

	    void setPosition(Vector2 &pos);
	    void setSize(Vector2 &size);
	    void setBgColor(Color &color);
	    void setBgHoverColor(Color &color);
	    void setBgClickColor(Color &color);
	    void setTexture(Texture2D texture);
		void setTextureHover(Texture2D texture);
		void setTextureClick(Texture2D texture);
	    void setFont(Font &newFont);
	    void setTextPosition(Vector2 &pos);
	    void setTextColor(Color &color);
	    void setTextHoverColor(Color &color);
	    void setTextClickColor(Color &color);
	    void setText(const std::string& newText);

	    void setCallback(Callback callback, void* userData);

    //******************************************************************************//
    //***                                Getters                                 ***//
    //******************************************************************************//

	    Vector2	getPosition()		const { return {rect.x, rect.y}; }
	    Vector2	getSize()		const { return {rect.width, rect.height}; }
	    Color	getBgColor()		const { return bgColor; }
	    Color	getBgHoverColor()	const { return bgHoverColor; }
	    Color	getBgClickColor()	const { return bgClickColor; }
	    Rectangle	getRectangle()		const { return rect; }
	    Font	getFont()		const { return font; }
	    Vector2	getTextPosition()	const { return textPosition; }
	    Color	endregiongetTextColor()	const { return textColor; }
	    Color	getTextHoverColor()     const { return textHoverColor; }
	    Color	getTextClickColor()     const { return textClickColor; }
	    const Texture2D& getTexture()   	const { return textureBase; }

    //******************************************************************************//
    //***                                Variables                               ***//
    //******************************************************************************//

	private:
	    Rectangle	rect;
	    Texture2D	textureBase;
	    Texture2D	textureHover;
	    Texture2D	textureClick;
	    Color	bgColor;
	    Color	bgHoverColor;
	    Color	bgClickColor;

	    std::string text;
	    Font	font;
	    Vector2	textPosition;
	    Color	textColor;
	    Color	textHoverColor;
	    Color	textClickColor;

	    bool	isClicked;
		// bl8		isAllocate;
	    float	scale;

	    // Fn pointer
	    Callback	onClickCallback;
	    void*	userData;

	    void cleanup();
	    void copyFrom(const Button& other);
    };
};
