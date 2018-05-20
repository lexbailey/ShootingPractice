/*! \file lineCircleIntersectTest.h
    \brief A quick test of line to circle collisions. (It's a catchy name, I know)
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This test program draws a circle on the screen and a line from the last clicked point on the screen to the mouse
	cursor position. If the line enters the circle or starts inside the circle then the circle will turn red.

    (University of York C Programming Labs assessment)
*/

#ifndef LINECIRCLE_TEST_PROGRAM_INCLUDE
#define LINECIRCLE_TEST_PROGRAM_INCLUDE

#include "../ogl_gui/glwindow.h"
#include "../ogl_gui/glDrawFuncs.h"
#include "../utils/boolean.h"

float red, green, blue;

int mousex, mousey;
bool click;

vector3 mousePos, lineStart;

vector3 circlePos;
float circleRad;

/**
 * Keyboard event handler, called by the glWindow
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Mouse event handler, called by the glWindow
 */
void motion(int x, int y);

/**
 * Draw the scene, called by the glWindow
 */
void drawGLWindow();

int main (int argc, char **argv);

#endif //LINECIRCLE_TEST_PROGRAM_INCLUDE
