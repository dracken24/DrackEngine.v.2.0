/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*            | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-10-2024  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  error_to_popUp.h        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/
#ifndef ERROR_TO_POPUP_H
# define ERROR_TO_POPUP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../library/drackengine_lib/drackengine_lib.h"

#include "engine.h"

// typedef struct ErrorToPopUp
// {
//     logLevel    level;
//     Rectangle   rect;
//     Rectangle   cam07;

//     Color   bgColor;
// } ErrorToPopUp;

void	init_ErrorToPopUp(ErrorToPopUp *errToPopUp, Rectangle rect ,logLevel level, Color bgColor);
void    draw_popUp(ErrorToPopUp errToPop, bl8 skipWord00, const char *message, ...);

#ifdef __cplusplus
}
#endif

#endif