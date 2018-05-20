/*! \file buttons.h
    \brief Allows drawing of buttons on an OpenGL context.
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file contains a structure for holding information about a
    button and functions for drawing it and checking if the mouse is in it.

    (University of York C Programming Labs assessment)
*/

#ifndef BUTTONS_INCLUDE
#define BUTTONS_INCLUDE

#include "glDrawFuncs.h"
#include "bitmaps.h"
#include "bitmapFonts.h"
#include "vector3.h"
#include "colours.h"
#include "../utils/boolean.h"

///Structure to hold information about a button
typedef struct {
	float width, height;
	colour_t colour;
	float x, y;
	char* text;
	unsigned int fontMap;
} button_t;

/**
 * Draw a button on an OpenGL context
 * @param button	Pointer to the button to be drawn
 */
void buttonDraw(button_t *button);

/**
 * Check if a button is currently being hovered by the mouse
 * @param button	Pointer to the button to check
 * @param mousePos	The current position of the mouse (from glWindowGetOGLPos)
 * @return true is mousePos is hovering over the button, false otherwise
 */
bool buttonIsHovered(button_t *button, vector3 mousePos);

#endif //BUTTONS_INCLUDE
