/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*            | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-09-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     Buttons.c            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "Buttons.hpp"

using namespace DrackEngine::UI;

Button::Button()
	: rect((Rectangle){0.0f, 0.0f, 0.0f, 0.0f})
	, textureBase((Texture2D){0})
	, textureHover((Texture2D){0})
	, textureClick((Texture2D){0})
	, bgColor(DEFAULT_BG)
	, bgHoverColor(HOVER_BG)
	, bgClickColor(CLICK_BG)
	, font(GetFontDefault())
	, textPosition((Vector2){0.0f, 0.0f})
	, textColor(TEXT_COLOR)
	, textHoverColor(TEXT_COLOR)
	, textClickColor(TEXT_COLOR)
	, isClicked(false)
	, scale(1.0f)
	, userData(nullptr)
{
}

// Button::Button(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
// 		const std::string& texturePath, const std::string& text, float scale)
// 	: rect((Rectangle){pos.x, pos.y, size.x, size.y})
// 	, bgColor(bgColor)
// 	, textColor(textColor)
// 	, text(text)
// 	, font(GetFontDefault())
// 	, isClicked(false)
// 	, scale(scale)
// 	, userData(nullptr)
// {
// 	if (!texturePath.empty())
// 	{
// 		textureBase = LoadTexture(texturePath.c_str());
// 	}
// }

Button::Button(const Button& other)
{
	copyFrom(other);
}

Button& Button::operator=(const Button& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

Button::~Button()
{

}

void Button::copyFrom(const Button& other)
{
	rect = other.rect;
	if (other.textureBase.id > 0)
	{
		// Charger une nouvelle copie de la texture
		Image img = LoadImageFromTexture(other.textureBase);
		textureBase = LoadTextureFromImage(img);
		UnloadImage(img);
	}
	// Même chose pour textureHover et textureClick
	bgColor = other.bgColor;
	bgHoverColor = other.bgHoverColor;
	bgClickColor = other.bgClickColor;
	text = other.text;
	font = other.font;
	textPosition = other.textPosition;
	textColor = other.textColor;
	textHoverColor = other.textHoverColor;
	textClickColor = other.textClickColor;
	isClicked = other.isClicked;
	scale = other.scale;
	onClickCallback = other.onClickCallback;
	userData = other.userData;
}

void	DrackEngine::UI::Button::initButton(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
    		const std::string& texturePath, const std::string& text, float scale)
{
    // Initialisation des propriétés de base
    this->rect = (Rectangle){pos.x, pos.y, size.x, size.y};
    this->bgColor = bgColor;
    this->textColor = textColor;
    this->text = text;
    this->scale = scale;
    
    // Couleurs par défaut pour les états hover et click
    this->bgHoverColor = HOVER_BG;
    this->bgClickColor = CLICK_BG;
    this->textHoverColor = textColor;
    this->textClickColor = textColor;
    
    // Position du texte au centre du bouton par défaut
    this->textPosition = (Vector2)
	{
        pos.x + size.x/2,
        pos.y + size.y/2
    };
    
    // Initialisation des autres membres
    this->isClicked = false;
    this->onClickCallback = nullptr;
    this->userData = nullptr;

    // Chargement de la texture si un chemin est fourni
    if (!texturePath.empty())
	{
        this->textureBase = LoadTexture(texturePath.c_str());
    }
}

void Button::draw(int fontSize, int spacing, int borderThick,
	 Color borderColor, Vector2 cameraOrigin, bool skipUpdate)
{
	Vector2 mousePos = GetMousePosition();
	Vector2 textPos = {rect.x + rect.width / 2, rect.y + rect.height / 2};

	if (!text.empty()) 
	{
		Vector2 textSize = MeasureTextEx(font, text.c_str(),
			fontSize ? fontSize : font.baseSize, spacing);
		textPos.x -= textSize.x / 2;
		textPos.y -= textSize.y / 2;
	}

	Rectangle hitBox = rect;
	hitBox.x += cameraOrigin.x;
	hitBox.y += cameraOrigin.y;

	if (CheckCollisionPointRec(mousePos, hitBox) && !skipUpdate)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if (textureClick.id > 0)
			{
				DrawTextureEx(textureClick, (Vector2){rect.x, rect.y}, 0, scale, W);
			}
			else
			{
				DrawRectangleRec(rect, bgClickColor);
				if (!text.empty()) {
					DrawTextEx(font, text.c_str(), textPos,
						fontSize ? fontSize : font.baseSize, spacing, textColor);
				}
			}

			if (onClickCallback && !isClicked)
			{
				onClickCallback(userData);
				isClicked = true;
			}
		}
		else
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				isClicked = false;
			}

			if (textureHover.id > 0)
			{
				DrawTextureEx(textureHover, (Vector2){rect.x, rect.y}, 0, scale, W);
			}
			else
			{
				DrawRectangleRec(rect, bgHoverColor);
				if (!text.empty())
				{
					DrawTextEx(font, text.c_str(), textPos,
						fontSize ? fontSize : font.baseSize, spacing, textColor);
				}
			}
		}
	}
	else
	{
		if (textureBase.id > 0)
		{
			DrawTextureEx(textureBase, (Vector2){rect.x, rect.y}, 0, scale, W);
		}
		else
		{
			DrawRectangleRec(rect, bgColor);
			if (!text.empty())
			{
				DrawTextEx(font, text.c_str(), textPos,
					fontSize ? fontSize : font.baseSize, spacing, textColor);
			}
		}
	}

	// Draw borders
	if (borderThick > 0)
	{
		DrawRectangleLinesEx(rect, borderThick, borderColor);
	}
}

//******************************************************************************//
//***                                 Setters                                ***//
//******************************************************************************//

void    Button::setPosition(Vector2 &pos)
{
	rect.x = pos.x;
	rect.y = pos.y;
}

void    Button::setSize(Vector2 &size)
{
	rect.width = size.x;
	rect.height = size.y;
}

void    Button::setBgColor(Color &bg_color)
{
	bg_color = bg_color;
}

void    Button::setBgHoverColor(Color &bg_hover_color)
{
	bg_hover_color = bg_hover_color;
}

void    Button::setBgClickColor(Color &bg_click_color)
{
	bg_click_color = bg_click_color;
}

void    Button::setTexture(Texture2D texture)
{
	textureBase = texture;
}

void    Button::setTextureHover(Texture2D texture)
{
	textureHover = texture;
}

void    Button::setTextureClick(Texture2D texture)
{
	textureClick = texture;
}

void    Button::setFont(Font &font)
{
	font = font;
}

void    Button::setTextPosition(Vector2 &text_position)
{
	text_position = text_position;
}

void    Button::setTextColor(Color &text_color)
{
	text_color = text_color;
}

void    Button::setTextHoverColor(Color &text_hover_color)
{
	text_hover_color = text_hover_color;
}

void    Button::setTextClickColor(Color &text_click_color)
{
	text_click_color = text_click_color;
}

void	Button::setText(const std::string& newText)
{
	text = newText;
}

void    Button::setCallback(Callback callback, void* userData)
{
	onClickCallback = callback;
	userData = userData;
}
