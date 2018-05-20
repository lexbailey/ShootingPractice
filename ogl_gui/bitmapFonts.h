/*! \file bitmapFonts.h
    \brief Functions for drawing fontmap texture in OpenGL
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file contains functions for rendering text in an OpenGL scene.
    The OpenGL context must be already set up and have the fontmap texture
    loaded.

    (University of York C Programming Labs assessment)
*/

#ifndef BITMAP_FONTS_INCLUDE
#define BITMAP_FONTS_INCLUDE

#include "bitmaps.h"

//These define the default sizes for the text
#define BITMAP_FONTS_DEFAULT_TEXT_HEIGHT 2.0f
#define BITMAP_FONTS_DEFAULT_TEXT_WIDTH 2.0f

//define the width and height of the font map (in characters)
//Our maps are all 10x10 squares (with 95 squares used if you count the space as used)
#define BITMAP_FONTS_MAP_WIDTH 10
#define BITMAP_FONTS_MAP_HEIGHT 10

/**
 * Renders a raw character from a fontmap texture given its coordinates.
 * X = 0 and Y = 0 is the top left corner of the fontmap texture. (space character)
 * @param font		The OpenGL texture ID for the font map
 * @param x			The X position of the desired character in the map
 * @param y			The X position of the desired character in the map
 * @param length	The width (in OpenGL units) that the character should be,
 * 					Consider using BITMAP_FONTS_DEFAULT_TEXT_WIDTH.
 */
void bitmapFontGLRenderRawChar(unsigned int font, int x, int y, float length);

/**
 * Renders a given character from a standard fontmap texture.
 * @param font		The OpenGL texture ID for the font map
 * @param character	The character to render
 * @param length	The width (in OpenGL units) that the character should be
 */
void bitmapFontGLRenderChar(unsigned int font, char character, float length);

/**
 * Renders a string using a given fontmap texture.
 * @param font		The OpenGL texture ID for the font map
 * @param text		A pointer to start of the string to render
 * @param length	The width (in OpenGL units) that each character should be
 */
void bitmapFontGLRenderText(unsigned int font, const char *text, float length);

/**
 * Renders a string using a given fontmap texture.
 * Unlike {@link #bitmapFontGLRenderText(unsigned int, const char *, float)}, it
 * draws the text centred in the current OpenGL transformation
 * @param font		The OpenGL texture ID for the font map
 * @param text		A pointer to start of the string to render
 * @param length	The width (in OpenGL units) that each character should be
 */
void bitmapFontGLRenderTextCentre(unsigned int font, const char *text,
		float length);

#endif //BITMAP_FONTS_INCLUDE
