/*! \file stickmanTest.h
    \brief A quick test of the stickman library
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This test program simply draws a stickman standing on some grass.
    This was written to ensure the the stickman draws properly

    (University of York C Programming Labs assessment)
*/

#ifndef STICKMAN_TEST_PROGRAM_INCLUDE
#define STICKMAN_TEST_PROGRAM_INCLUDE
#include "../ogl_gui/glwindow.h"
#include "../ogl_gui/glDrawFuncs.h"
#include "../ogl_gui/colours.h"
#include "../stickman/stickman.h"

pose_t pose = ptStand;
stickman_t myStickMan;

/**
 * Draws the grass
 */
void drawFloor();

/**
 * Draw the scene, called by the glWindow
 */
void drawGLWindow();

int main (int argc, char **argv);

#endif //STICKMAN_TEST_PROGRAM_INCLUDE
