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
	, texture((Texture2D){0})
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

Button::Button(Vector2 pos, Vector2 size, Color bgColor, Color textColor,
		const std::string& texturePath, const std::string& text, float scale)
	: rect((Rectangle){pos.x, pos.y, size.x, size.y})
	, bgColor(bgColor)
	, textColor(textColor)
	, text(text)
	, font(GetFontDefault())
	, isClicked(false)
	, scale(scale)
	, userData(nullptr)
{
	if (!texturePath.empty())
	{
		texture = LoadTexture(texturePath.c_str());
	}
}

Button::Button(const Button& other)
{
	copyFrom(other);
}

Button& Button::operator=(const Button& other)
{
	if (this != &other)
	{
		cleanup();
		copyFrom(other);
	}
	return *this;
}

Button::~Button()
{
	cleanup();
}

void Button::cleanup()
{
	if (texture.id > 0)
		UnloadTexture(texture);
	if (textureHover.id > 0)
		UnloadTexture(textureHover);
	if (textureClick.id > 0)
		UnloadTexture(textureClick);
}

void Button::copyFrom(const Button& other)
{
	rect = other.rect;
	if (other.texture.id > 0)
	{
		// Charger une nouvelle copie de la texture
		Image img = LoadImageFromTexture(other.texture);
		texture = LoadTextureFromImage(img);
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
		if (texture.id > 0)
		{
			DrawTextureEx(texture, (Vector2){rect.x, rect.y}, 0, scale, W);
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

void Button::setCallback(Callback callback, void* data)
{
	onClickCallback = callback;
	userData = data;
}
