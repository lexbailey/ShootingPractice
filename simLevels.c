/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See simLevels.h for function documentation
 *  (University of York C Programming Labs assessment)
 */


#include "simLevels.h"

void levelFree(sim_level_t *level){
	if (level){
		if (level->numObstructions){	//obstruction pointer might not be null if the level didn't need any space
			if (level->obstructions){
				free(level->obstructions);
				level->obstructions = NULL;
			}
		}
	}
}

sim_level_t levelGet(unsigned int level){
	sim_level_t output;
	switch(level){
		case 1:
			output.target.x = 2.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.1f;
			output.wind.x = 0.0f;
			output.wind.y = 0.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 0;
		break;
		case 2:
			output.target.x = 2.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.1f;
			output.wind.x = 0.0f;
			output.wind.y = 2.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 1;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);
			output.obstructions[0].obsType = ot_Bounce;
			output.obstructions[0].radius = 0.2f;
			output.obstructions[0].pos.x = 1.0f;
			output.obstructions[0].pos.y = 2.0f;
			output.obstructions[0].pos.z = 0.0f;
		break;
		case 3:
			output.target.x = 4.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.2f;
			output.wind.x = 0.0f;
			output.wind.y = -3.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 2;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);

			output.obstructions[0].obsType = ot_Die;
			output.obstructions[0].radius = 0.4f;
			output.obstructions[0].pos.x = 3.0f;
			output.obstructions[0].pos.y = 3.0f;
			output.obstructions[0].pos.z = 0.0f;

			output.obstructions[1].obsType = ot_Die;
			output.obstructions[1].radius = 0.4f;
			output.obstructions[1].pos.x = 3.0f;
			output.obstructions[1].pos.y = 1.0f;
			output.obstructions[1].pos.z = 0.0f;
		break;
		case 4:
			output.target.x = 4.3f;
			output.target.y = 1.4f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 5.0f;
			output.wind.y = 2.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 3;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);

			output.obstructions[0].obsType = ot_Bounce;
			output.obstructions[0].radius = 0.5f;
			output.obstructions[0].pos.x = 2.5f;
			output.obstructions[0].pos.y = 2.0f;
			output.obstructions[0].pos.z = 0.0f;

			output.obstructions[1].obsType = ot_Bounce;
			output.obstructions[1].radius = 0.5f;
			output.obstructions[1].pos.x = 4.0f;
			output.obstructions[1].pos.y = 1.0f;
			output.obstructions[1].pos.z = 0.0f;

			output.obstructions[2].obsType = ot_Die;
			output.obstructions[2].radius = 0.6f;
			output.obstructions[2].pos.x = 4.0f;
			output.obstructions[2].pos.y = 3.0f;
			output.obstructions[2].pos.z = 0.0f;
		break;

		case 5:
			output.target.x = 2.5f;
			output.target.y = 0.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 1.0f;
			output.wind.y = 1.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 3;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);

			output.obstructions[0].obsType = ot_Die;
			output.obstructions[0].radius = 0.7f;
			output.obstructions[0].pos.x = 1.0f;
			output.obstructions[0].pos.y = 0.0f;
			output.obstructions[0].pos.z = 0.0f;

			output.obstructions[1].obsType = ot_Bounce;
			output.obstructions[1].radius = 0.5f;
			output.obstructions[1].pos.x = 2.5f;
			output.obstructions[1].pos.y = 3.0f;
			output.obstructions[1].pos.z = 0.0f;

			output.obstructions[2].obsType = ot_Die;
			output.obstructions[2].radius = 0.7f;
			output.obstructions[2].pos.x = 4.0f;
			output.obstructions[2].pos.y = 0.0f;
			output.obstructions[2].pos.z = 0.0f;
		break;
		case 6:
			output.target.x = 4.0f;
			output.target.y = 3.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 3.0f;
			output.wind.y = -5.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 2;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);
			output.obstructions[0].obsType = ot_Die;
			output.obstructions[0].radius = 0.4f;
			output.obstructions[0].pos.x = 3.0f;
			output.obstructions[0].pos.y = 3.0f;
			output.obstructions[0].pos.z = 0.0f;

			output.obstructions[1].obsType = ot_Bounce;
			output.obstructions[1].radius = 0.4f;
			output.obstructions[1].pos.x = 3.5f;
			output.obstructions[1].pos.y = 1.0f;
			output.obstructions[1].pos.z = 0.0f;
		break;


		case 7:
			output.target.x = 1.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 6.0f;
			output.wind.y = 0.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 4;
			output.obstructions = malloc(sizeof(sim_obstruction_t)*output.numObstructions);
			output.obstructions[0].obsType = ot_Die;
			output.obstructions[0].radius = 0.4f;
			output.obstructions[0].pos.x = 1.0f;
			output.obstructions[0].pos.y = 2.5f;
			output.obstructions[0].pos.z = 0.0f;

			output.obstructions[1].obsType = ot_Die;
			output.obstructions[1].radius = 0.4f;
			output.obstructions[1].pos.x = 0.5f;
			output.obstructions[1].pos.y = 2.0f;
			output.obstructions[1].pos.z = 0.0f;

			output.obstructions[2].obsType = ot_Die;
			output.obstructions[2].radius = 0.4f;
			output.obstructions[2].pos.x = 1.0f;
			output.obstructions[2].pos.y = 1.5f;
			output.obstructions[2].pos.z = 0.0f;

			output.obstructions[3].obsType = ot_Bounce;
			output.obstructions[3].radius = 1.0f;
			output.obstructions[3].pos.x = 4.5f;
			output.obstructions[3].pos.y = 2.0f;
			output.obstructions[3].pos.z = 0.0f;
		break;
		//Levels 8, 9 and 10 are a work in progress
		case 8:
			output.target.x = 2.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 0.0f;
			output.wind.y = 0.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 0;
		break;
		case 9:
			output.target.x = 2.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 0.0f;
			output.wind.y = 0.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 0;
		break;
		case 10:
			output.target.x = 2.0f;
			output.target.y = 2.0f;
			output.target.z = 0.0f;
			output.targetSize = 0.4f;
			output.wind.x = 0.0f;
			output.wind.y = 0.0f;
			output.wind.z = 0.0f;
			output.numObstructions = 0;
		break;
	}
	//just some protection
	if (!output.numObstructions){
		//If there are no obstruction then ensure the pointer is initialised to NULL
		output.obstructions = NULL;
	}
	return output;
}
