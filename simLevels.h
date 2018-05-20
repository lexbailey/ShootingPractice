/*! \file simLevels.h
    \brief Simple fixed level data source
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This generates levels from built in data. The plan was to have the level data loaded from files but that might have taken too much time.

    (University of York C Programming Labs assessment)
*/

#ifndef SIM_LEVELS_INCLUDE
#define SIM_LEVELS_INCLUDE

#include <stdlib.h>
#include "ogl_gui/vector3.h"

#define NUM_LEVELS 7

///The obstruction type enumeration. Two types are available, objects that kill when they are hit (ot_Die) and objects that rebound arrows. (ot_Bounce)
typedef enum {ot_Die, ot_Bounce} obstruction_type;

///A structure that defines a simple circular obstruction
typedef struct{
	vector3 pos;				//!< position of the obstruction
	float radius;				//!< Radius of the obstruction
	obstruction_type obsType;	//!< The type of obstruction (ot_Die or ot_Bounce)
} sim_obstruction_t;

/// A structure that defines a game level
typedef struct{
	vector3 target;						//!< Position of the target
	float targetSize;					//!< Radius of the target
	vector3 wind;						//!< The wind speed and direction
	unsigned int numObstructions;		//!< The number of obstructions
	sim_obstruction_t *obstructions;	//!< A pointer to the array of obstructions
} sim_level_t;

#define NUM_SIM_LEVELS 7	//!< The number of levels available

/**
 * Free the data for a level
 * @param level		A pointer to the level to free
 */
void levelFree(sim_level_t *level);

/**
 * A function to get the data for a specific level
 * @param level		The ID of the desired level
 * @return	A sim_level_t structure holding all of the level information
 */
sim_level_t levelGet(unsigned int level);

#endif //SIM_LEVELS_INCLUDE
