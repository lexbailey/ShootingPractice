/*! \file keys.h
    \brief Simple FreeGLUT keyboard handler
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    Attaches to FreeGLUT callbacks to provide a slightly more sophisticated method of handling key presses.

    (University of York C Programming Labs assessment)
*/

#ifndef KEYS_INCLUDE
#define KEYS_INCLUDE

#include "../utils/boolean.h"

//Arrow keys
#define KEY_A_LEFT 0	//!< Arrow Key, Left
#define KEY_A_UP 1		//!< Arrow Key, Up
#define KEY_A_RIGHT 2	//!< Arrow Key, Right
#define KEY_A_DOWN 3	//!< Arrow Key, Down

//F Keys
#define KEY_F_1 0		//!< Function Key, 1
#define KEY_F_2 1		//!< Function Key, 2
#define KEY_F_3 2		//!< Function Key, 3
#define KEY_F_4 3		//!< Function Key, 4
#define KEY_F_5 4		//!< Function Key, 5
#define KEY_F_6 5		//!< Function Key, 6
#define KEY_F_7 6		//!< Function Key, 7
#define KEY_F_8 7		//!< Function Key, 8
#define KEY_F_9 8		//!< Function Key, 9
#define KEY_F_10 9		//!< Function Key, 10
#define KEY_F_11 10		//!< Function Key, 11
#define KEY_F_12 11		//!< Function Key, 12

/**
 * A structure holding information on what keyboard keys are pressed.
 */
typedef struct {
	/**
	 * An array of bool showing which arrow keys are pressed. Test with arrowKeysPressed[KEY_A_LEFT] etc.
	 * true is pressed, false is not
	 */
	bool arrowKeysPressed[4];

	/**
	 * An array of bool showing which function keys are pressed. Test with FKeysPressed[KEY_F_1] etc.
	 * true is pressed, false is not
	 */
	bool FKeysPressed[12];

	/**
	 * An array of bool showing which standard character keys are pressed. Test with keyPressed['a'] etc.
	 * true is pressed, false is not
	 */
	bool keyPressed[256];
} keyData_t;

/**
 * our instance of the keyData_t structure for the program to read the state of the keys.
 * This must be defined globally as it is required by functions that are called by FreeGLUT.
 * Functions called by FreeGLUT cannot be given custom parameters.
 * This Global variable is therefore unavoidable when using FreeGLUT callbacks.
 */
keyData_t keyData;

/**
 * Special key down handler. Call this function from your GLUT key handler to register the event.
 * @param key	The key that was pressed
 */
void onGLUTSpecialDown(int key);

/**
 * Special key up handler. Call this function from your GLUT key handler to register the event.
 * @param key	The key that was released
 */
void onGLUTSpecialUp(int key);

/**
 * Standard key down handler. Call this function from your GLUT key handler to register the event
 * @param key	The key that was pressed
 */
void onGLUTKeyDown(unsigned char key);

/**
 * Standard key down handler. Call this function from your GLUT key handler to register the event
 * @param key	The key that was released
 */
void onGLUTKeyUp(unsigned char key);

/**
 * Initialises the key handler system.
 */
void initKeyPressed();

#endif  //KEYS_INCLUDE
