/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*            | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-10-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  error_to_popUp.c        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "error_to_popUp.h"
Rectangle	get_camera07_rect(void);

extern Engine *g_engine;

void	init_ErrorToPopUp(ErrorToPopUp *errToPopUp, Rectangle rect ,logLevel level, Color bgColor)
{
	errToPopUp->bgColor = bgColor;
	errToPopUp->level = level;
	errToPopUp->rect = rect;
	errToPopUp->cam07 = get_camera07_rect();
	errToPopUp->popUpInUse = false;
}

void    draw_popUp_now(ErrorToPopUp errToPop, const char *message)
{
    Rectangle rect = errToPop.rect;
    DrawRectangleRec(rect, errToPop.bgColor);

    const Color *colors[] = {&RED, &MAROON, &ORANGE, &YELLOW, &BLUE, &GREEN};
    DrawRectangleLinesEx(rect, 4, *colors[errToPop.level]);
	
	Font font = g_engine->fonts.defaultFont;
	Vector2 mesureText = MeasureTextEx(font, message, font.baseSize , 1);
	Vector2 rectPos = (Vector2){rect.x + rect.width / 2 - mesureText.x / 2,
		rect.y + rect.height / 2 - mesureText.y / 4};
	DrawTextEx(font, message, rectPos, font.baseSize, 1, *colors[errToPop.level]);
}

void    draw_popUp(ErrorToPopUp errToPop, bl8 skipWord00, const char *message, ...)
{
    const char	*levelStr[6] = {"[*FATAL*]   : ", "[*ERROR*]   : ", "[*WARNING*] : ",
		"[*INFO*]    : ", "[*DEBUG*]   : ", "[*TRACE*]   : "};
	bl8 shouldLog = errToPop.level < DE_LOG_LEVEL_WARNING;

    char outMessage[32000];
	memset(outMessage, 0, sizeof(outMessage));

	va_list args;
	va_start(args, message);
	vsnprintf(outMessage, 32000, message, args);
	va_end(args);

	char outBuffer[32000];
	memset(outBuffer, 0, sizeof(outBuffer));
	if (!skipWord00)
	{
		strcat(outBuffer, levelStr[errToPop.level]);
	}
	strcat(outBuffer, outMessage);
	strcat(outBuffer, "\n");

    draw_popUp_now(errToPop, outBuffer);
}
