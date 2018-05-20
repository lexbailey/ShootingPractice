/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See bitmapFonts.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "bitmapFonts.h"

//used stuff from stackoverflow...
//http://stackoverflow.com/questions/1861222/opengl-es-get-current-blendfunc
void bitmapFontGLRenderRawChar(unsigned int font, int x, int y, float length) {

	//We need to remember the OpenGL states for state changed while drawing text so that it can be restored later
	bool IsTexture = glIsEnabled(GL_TEXTURE_2D);
	bool IsBlend = glIsEnabled(GL_BLEND);
	bool IsDepth = glIsEnabled(GL_DEPTH_TEST);
	GLint blendSrc;
	GLint blendDst;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
	glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);

	//Now we can set up all the states we require
	glEnable(GL_TEXTURE_2D);			//Enable texturing
	glEnable(GL_BLEND);					//Enable blending
	glDisable(GL_DEPTH_TEST);			//Enable depth testing
	//Set blending such that the white background of the font image is removed
	glBlendFunc(GL_DST_COLOR, GL_ZERO);

	//Ensure that the correct texture is bound and ready to use
	glBindTexture(GL_TEXTURE_2D, font);
	//set the colour to white
	glColor3f(1.0f, 1.0f, 1.0f);

	//Generate texture coordinates from our grid coordinates
	float texX1 = ((1.0f / BITMAP_FONTS_MAP_WIDTH) * x);
	float texY1 = ((1.0f / BITMAP_FONTS_MAP_HEIGHT) * y);

	float texX2 = ((1.0f / BITMAP_FONTS_MAP_WIDTH) * (x + 1));
	float texY2 = ((1.0f / BITMAP_FONTS_MAP_HEIGHT) * (y + 1));

	//Now get ready to draw a character
	glPushMatrix();

		//Draw the character!
		//We are actually drawing a square with a small portion of the font map on it, blended into the background so that only the text is visible
		glBegin(GL_QUADS);
			glTexCoord2f(texX1, texY1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(texX2, texY1);
			glVertex3f(length, 0.0f, 0.0f);
			glTexCoord2f(texX2, texY2);
			glVertex3f(length, length, 0.0f);
			glTexCoord2f(texX1, texY2);
			glVertex3f(0.0f, (length), 0.0f);
		glEnd();

	glPopMatrix();

	//Restore the states we had before if they changed
	if (!IsTexture) {
		glDisable(GL_TEXTURE_2D);
	}

	if (!IsBlend) {
		glDisable(GL_BLEND);
	}

	if (IsDepth) {
		glEnable(GL_DEPTH_TEST);
	}
	glBlendFunc(blendSrc, blendDst);
}

void bitmapFontGLRenderChar(unsigned int font, char character, float length) {
	//Calculate x and y coords from the character's ASCII value.
	int id = character - 32;
	int x = id % BITMAP_FONTS_MAP_WIDTH;
	int y = (BITMAP_FONTS_MAP_HEIGHT - 1) - (id / BITMAP_FONTS_MAP_WIDTH);

	//Render the character
	bitmapFontGLRenderRawChar(font, x, y, length);
}

void bitmapFontGLRenderText(unsigned int font, const char *text, float length) {
	int i = -1;
	glPushMatrix();
		//loop through all characters, render each one in turn
		while (text[++i] != '\0') {
			bitmapFontGLRenderChar(font, text[i], length);
			glTranslatef(length, 0, 0);
		}
	glPopMatrix();
}

void bitmapFontGLRenderTextCentre(unsigned int font, const char *text,
		float length) {

	//Get the length of the string
	int i = -1;
	while (text[++i] != '\0') {}

	glPushMatrix();
		//Move back half way so the string is rendered centred
		glTranslatef(-(length * i) / 2.0f, -length / 2.0f, 0.0f);

		//Render the string
		bitmapFontGLRenderText(font, text, length);
	glPopMatrix();
}

