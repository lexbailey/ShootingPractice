/*! \file glWindowANDglDrawFuncsTest.h
    \brief A quick test of the glWindow library
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This test program presents an OpenGL window and uses the drawing functions to perform a basic verification that
    the window and drawing functions work.
    it draws a line from the centre to the cursor. There is a circle at the centre and a disc at the cursor.
    The radii of the circles changes with the distance from the centre to the cursor.
    The colour used can be changed with the keyboard buttons R, G and B for red green and blue.

    (University of York C Programming Labs assessment)
*/

#ifndef WINDOW_TEST_PROGRAM_INCLUDE
#define WINDOW_TEST_PROGRAM_INCLUDE

#include "../ogl_gui/glwindow.h"
#include "../ogl_gui/glDrawFuncs.h"

float red, green, blue;

int mousex, mousey;

vector3 mousePos;

void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);

void drawGLWindow();
int main (int argc, char **argv);

#endif //WINDOW_TEST_PROGRAM_INCLUDE
