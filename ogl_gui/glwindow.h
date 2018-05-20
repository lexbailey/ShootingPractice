/*! \file glwindow.h
    \brief A small wrapper around FreeGLUT
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This is a wrapper around the FreeGLUT library that will automatically create a window and allow you to pan, rotate and zoom using the mouse

    (University of York C Programming Labs assessment)
*/

#ifndef GLWINDOW_INCLUDE
#define GLWINDOW_INCLUDE

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "glDrawFuncs.h"
#include "vector3.h"
#include "colours.h"
#include "../utils/boolean.h"
#include "../myColours.h"

//These definitions are to be enabled for the purpose of debugging this library (glwindow.h and .c)
//#define DEBUG_AXES		//Draws the global axes (used to ensure they stay constant)
//#define DEBUG_LOCAL_AXES	//Draws the local axes (used to ensure they move correctly)
//#define DEBUG_MOUSE_POS	//Draws a line to the current mouse position (to ensure that mouse position is known correctly)

/// Structure to keep all of the window's variable away from the rest of the program... Most values in here should be though of as 'read-only' The only values the user can change are zoomEnabled, rotateEnabled and translateEnabled
typedef struct{
	//Defines what actions are enabled
	bool zoomEnabled, rotateEnabled, translateEnabled;

	//For handling rotation
	int zrot;
	int zrot2;
	int xrot;
	int xrot2;
	int yrot;
	int yrot2;

	//For handling zooming
	float scale;
	float scale2;

	//For handling translation
	float xshift, yshift;
	float xshift2, yshift2;
		
	//Variables for handling mouse actions
	bool mousebuttons[5];
	int startx, starty;
	int mousex, mousey;

	//The variable below are pointers to callback functions (for the user to set with the appropriate functions)
	void (* rawDrawCallBack)();
	void (* drawCallBack)();
	void (* drawDoneCallBack)();
	void (* keyboardCallBack)(unsigned char, int, int);
	void (* keyboardSpecialCallBack)(int, int, int);
	void (* keyboardSpecialUpCallBack)(int, int, int);
	void (* motionCallBack)(int, int);
	void (* mouseCallBack)(int, int, int, int);

} glWindowData_t;

/**
 * The instance of the glWindowData_t structure. Available to the user.
 * This must be defined globally as it is required by functions that are called by FreeGLUT.
 * Functions called by FreeGLUT cannot be given custom parameters.
 * This Global variable is therefore unavoidable when using FreeGLUT callbacks.
 */
glWindowData_t glWindowData;

/**
 * Sets the function that is called when FreeGLUT requests that the scene is rendered
 * The preliminary setup and translation, rotation and zoom is handled internally.
 * @param f	The function to be called
 */
void glwindow_setDrawFunc (void (*f)());

/**
 * Sets the function that is called when FreeGLUT requests that the scene is rendered
 * This event fires before the preliminary setup and translation, unlike glwindow_setDrawFunc.
 * @param f	The function to be called
 */
void glwindow_setRawDrawFunc (void (*f)());

/**
 * Sets the function that is called when the drawing is finished and glutSwapBuffers has been called (the next frame has reached the screen)
 * @param f	The function to be called
 */
void glwindow_setDoneDrawFunc (void (*f)());

/**
 * Sets the function that is called when FreeGLUT detects keyboard input
 * @param mf	The function to be called
 */
void glwindow_setKeyboardFunc (void (*mf)(unsigned char, int, int));

/**
 * Sets the function that is called when FreeGLUT detects 'special' keyboard input
 * This includes the arrow keys and F1 to F12 keys
 * @param mf	The function to be called
 */
void glwindow_setKeyboardSpecialFunc (void (*mf)(int, int, int));

/**
 * Sets the function that is called when FreeGLUT detects that a 'special' key has been released
 * @param mf	The function to be called
 */
void glwindow_setKeyboardSpecialUpFunc (void (*mf)(int, int, int));

/**
 * Sets the function that is called when FreeGLUT detects mouse movement
 * @param mf	The function to be called
 */
void glwindow_setMotionFunc (void (*mf)(int, int));

/**
 * Sets the function that is called when FreeGLUT detects mouse clicks
 * @param mf	The function to be called
 */
void glwindow_setMouseFunc (void (*mf)(int, int, int, int));

/**
 * Gets the current mouse position (in relative OpenGL coordinates)
 * @param x	The x position of the mouse on the screen (in pixels)
 * @param y The y position of the mouse on the screen (in pixels)
 * @return	The OpenGL position of the mouse
 */
vector3 glWindowGetOGLPos(int x, int y);

/**
 * Initialises the OpenGL window
 * @param argc Program argument count from the standard arguments (aka argument count)
 * @param argv Program argument array from the standard arguments (aka argument vector)
 */
void glwindow_init(int argc, char **argv);

/**
 * Shows the OpenGL window by initialising the main FreeGLUT loop
 */
void glwindow_show();

#endif /*GLWINDOW_INCLUDE*/

