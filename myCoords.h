/*! \file myCoords.h
    \brief Header file containing fixed coordinates and vectors.
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This is a list of all fixed coordinates and vectors that are needed in the game.
    These definitions can be used with any function that wants three floating point parameters.
    This is useful for quickly getting a vector such as gravity.

    Example usage for getting gravity:

    vector3 Gravity = vector3XYZ(GRAVITY);

    Example usage for moving to a particular position:

    glTranslatef(HEADER_TEXT_POS);

    (University of York C Programming Labs assessment)
*/

#ifndef MYCOORDS_INCLUDE
#define MYCOORDS_INCLUDE

#define GRAVITY					0.0f,	-9.8f,	0.0f
#define GROUND_LEVEL			0.0f,	-1.5f,	0.0f
#define WIND_INDICATOR_POS		-3.5f,	1.25f,	0.0f
#define WIND_TEXT_OFFSET		0.8f,	0.1f,	0.0f
#define MINI_STICKMAN_1_POS		0.0f,	0.0f,	0.0f
#define MINI_STICKMAN_2_POS		0.7f,	0.0f,	0.0f
#define PLAYER_START_POS		-4.5f,	0.0f,	0.0f
#define ONE_PLAYER_BUTTON_POS	-2.0f,	0.0f,	0.0f
#define TWO_PLAYER_BUTTON_POS	-2.0f,	-1.0f,	0.0f
#define TITLE_POS				-4.5f,	+2.0f,	0.0f
#define TITLE_LINE2_OFFSET		+1.0f,	-1.0f,	0.0f

#define PLAYER_ID_LOCATION		-0.7f,	2.7f,	0.0f
#define PLAYER_TIMER_LOCATION	2.5f,	2.2f,	0.0f
#define LEVEL_ID_LOCATION		-3.5f,	2.7f,	0.0f
#define LIFE_INDICATOR_LOCATION	2.5f,	2.7f,	0.0f
#define LIFE_STICKS_OFFSET		1.2f,	-0.2f,	0.0f
#define LIFE_STICKS_SEPERATION	0.7f,	0.0f,	0.0f

#define HEADER_TEXT_POS			0.0f,	2.0f,	0.0f
#define ARROW_END_POS			-0.3f,	0.0f,	0.0f
#define FLOOR_COLLISION_NORMAL	0.0f,	1.0f,	0.0f

#define TEXT_LINES_START		-1.0f,	-0.7f,	0.0f
#define TEXT_SINGLE_LINE_SPACE	0.0f,	-0.3f,	0.0f
#define TEXT_DOUBLE_LINE_SPACE	0.0f,	-0.6f,	0.0f

#define TEXT_MID_LINE_SPACE		0.0f,	-0.4f,	0.0f

#endif //MYCOORDS_INCLUDE
