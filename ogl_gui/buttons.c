/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See buttons.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "buttons.h"

//This function draws a button
void buttonDraw(button_t *button) {

	//Two vectors are constructed to hold coordinates for two corners of the button.
	vector3 Button1, Button2;

	//bottom left
	Button1.x = button->x;
	Button1.y = button->y;
	Button1.z = 0.0f;

	//top right
	Button2.x = button->x + button->width;
	Button2.y = button->y + button->height;
	Button2.z = 0.0f;

	//quick string length (needed to centre the text)
	int numChars = -1;
	while (button->text[++numChars] != '\0') {}

	//change to the colour for this button...
	colourEnable(button->colour);
	//draw the main button rectangle...
	drawFuncRectangle(Button1, Button2, 0.0f);

	float textSize = 0.2f;	//text size is constant

	//figure out where the centre of the button is relative to the bottom left corner...
	float textHeight = textSize;
	float textWidth = textSize * numChars;
	float dispY = (button->height / 2.0f) - (textHeight / 2.0f);
	float dispX = (button->width / 2.0f) - ((textWidth / 2.0f));

	glPushMatrix();

		//move to the bottom left corner of the button...
		drawFuncApplyTranslation(Button1);

		//from there, move to the middle...
		glTranslatef(dispX, dispY, 0.0f);

		//then put the text on the button...
		bitmapFontGLRenderText(button->fontMap, button->text, textSize);

	glPopMatrix();
}

//this functions simply checks to see if a point is inside the bounds of a button
//this is used to see if the mouse cursor is hovering over it
bool buttonIsHovered(button_t *button, vector3 mousePos) {
	return 	(
				(
					(mousePos.x >= button->x) &&
					(mousePos.y >= button->y)
				) &&
				(
					 (mousePos.x <= button->x + button->width)&&
					 (mousePos.y <= button->y + button->height)
				)
			);
}
