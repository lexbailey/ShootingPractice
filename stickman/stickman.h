/*! \file stickman.h
    \brief For drawing stickmen
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This is used to draw stickmen using OpenGL
    The stickmen can be standing still or firing a bow and arrow

    (University of York C Programming Labs assessment)
*/

#ifndef STICKMAN_INCLUDE
#define STICKMAN_INCLUDE

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../ogl_gui/glDrawFuncs.h"
#include "../ogl_gui/vector3.h"
#include "../ogl_gui/colours.h"
#include <stdio.h>

#define BODYHEIGHT 0.9f
#define LEGEIGHT 0.8f
#define ARMLENGTH 0.7f
#define HEADRADIUS 0.2f
#define STANCEWIDTH 0.35f
#define ARMDROP 0.1f
#define FIREDROP 0.1f
#define PULLBACKLIMIT 0.34f

//The bow colour is fixed to a sort of brown colour
#define BOW_COLOUR colourRGBByte(176, 111, 19)

///A pose type for defining how a stickman should stand (ptWalk is unimplemented yet)
typedef enum {ptStand, ptFire, ptWalk} pose_t;

///A stickman
typedef struct{

	vector3 pos;	//! position of the stickman
	pose_t pose;	//! the stickman's current pose
	int frame;		//! the frame of the walking animation (currently unimplemented)

	float aimAngle;	//! the angle at which the stickman is aiming his bow

	colour_t colour;//!the colour of the stickman

	float pullBack;	//! the distance by which the stickman is pulling the bow back (power)

	//for reading only, not writing
	vector3 bottom, top,
		leftKnee, leftFoot,
		rightKnee, rightFoot,
		leftElbow, leftHand,
		rightElbow, rightHand,
		head;

} stickman_t;

/**
 * Changes a stickman's pose and initialises the new pose
 * @param man	A pointer to the stickman to pose
 * @param pose	The new pose
 */
void stickManSetPose(stickman_t* man, pose_t pose);

/**
 * Draws a stickman
 * @param man	A pointer to the stickman to draw
 */
void stickManDraw(stickman_t* man);

#endif //STICKMAN_INCLUDE
