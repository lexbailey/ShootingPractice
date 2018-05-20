/*! \file world.h
    \brief Utilities for handling lots of physics objects at once
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file provides a structure and various functions that handle a physics world.
    This allows lots of objects to be simulated at once.

    (University of York C Programming Labs assessment)
*/

#ifndef PHYSICS_WORLD_INCLUDE
#define PHYSICS_WORLD_INCLUDE

#include <stdlib.h>
#include "../ogl_gui/glDrawFuncs.h"
#include "../myColours.h"
#include "../ogl_gui/vector3.h"
#include "../utils/boolean.h"
#include "forces.h"
#include "constraints.h"
#include "objects.h"

///This structure holds many physics objects at once
typedef struct {

	vector3 windSpeed;
	vector3 gravity;

	int numObjects;
	int lastObject;
	physics_object_t *physObjects;

} physics_world_t;

/**
 * Initialises a physics world ready for a particular number of objects
 * @param world			A pointer to the world to initialise
 * @param gravity		A vector representing gravity, this is usually just a negative y value (-9.8 for earth)
 * @param numObjects	The number of objects that the world needs space for
 */
void physWorldInitialise(physics_world_t *world, vector3 gravity, int numObjects);

/**
 * Adds an object to the array of objects that the world manages.
 * A copy of the object is made and so the original can be discarded after adding.
 * @param world		A pointer to the world to which the object will be added
 * @param object	The object to be added
 * @return	A pointer to the new object in the world array.
 */
physics_object_t *physWorldAddObject(physics_world_t *world, physics_object_t object);

/**
 * Check to see if there will be a collision between two objects in a given time frame
 * If the objects are of different collision types then collisions will only be tested
 * one way unless examineReverse is true. (If in doubt set this to true)
 * @param obj1				A pointer to the first object to collide
 * @param obj2				A pointer to the second object to collide
 * @param timeFrame			The time frame in which the collision must happen
 * @param examineReverse	If true, the objects are swapped and tested again
 * @param normal			A pointer to a vector3 where a collision normal can be returned
 * @return true if objects collide
 */
bool physWorldObjectCollision(physics_object_t *obj1, physics_object_t *obj2, float timeFrame, bool examineReverse, vector3 *normal);

/**
 * Perform the next time step in the physics world
 * @param world	A pointer to the world to step
 * @param time	The time in seconds for the step
 */
void physWorldStep(physics_world_t *world, float time);

/**
 * Free all data for a physics world (including objects and the world structure itself)
 * @param world	A pointer to the world to be freed
 */
void physWorldFree(physics_world_t *world);

#endif //PHYSICS_WORLD_INCLUDE
