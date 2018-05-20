/*! \file clab_assignment_graphics.h
    \brief Header file for the main program file
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file provides mostly just documentation.
    It defines function prototypes for the main program functions.
    It also defines the game variables

    (University of York C Programming Labs assessment)
*/

#ifndef MAIN_PROGRAM_INCLUDE
#define MAIN_PROGRAM_INCLUDE
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include "ogl_gui/glwindow.h"
#include "ogl_gui/glDrawFuncs.h"
#include "ogl_gui/bitmaps.h"
#include "ogl_gui/bitmapFonts.h"
#include "ogl_gui/vector3.h"
#include "ogl_gui/colours.h"
#include "ogl_gui/buttons.h"
#include "stickman/stickman.h"

#include "myColours.h"
#include "myCoords.h"
#include "physics/physics.h"
#include "physics/collisions.h"
#include "utils/keys.h"
#include "simLevels.h"

#define WALK_SPEED 3.0f			//!< The speed of the walk of the stickman
#define BOW_POWER 15.0f			//!< the relative power of the bow
#define PROJECTILE_RADIUS 0.01f //!< the radius of the head of the arrow
#define NUM_MAN_PAGES 6			//!< total number of pages in the "How to play" manual

//font map file names
#define MAIN_PROGRAM_MONOSPACE_FONT_FILE "res/MonoFont.bmp"					//!< resource file for the standard monospace font
#define MAIN_PROGRAM_SKETCHY_FONT_FILE_SMALL "res/OrangeJuiceFont1024.bmp"	//!< resource file for the small version of the sketchy font
#define MAIN_PROGRAM_SKETCHY_FONT_FILE_LARGE "res/OrangeJuiceFont4096.bmp"	//!< resource file for the large version of the sketchy font

//Texture file names
#define MAIN_PROGRAM_GRASS_TEXTURE "res/grass.bmp"	//!< resource file for the grass texture

/**
 * Enumerated type representing the current state of the game
 */
typedef enum {gs_Menu, gs_OnePlay, gs_TwoPlay, gs_Credits, gs_Instructions} gameState_t;

typedef struct{
	//Basic game engine stuff
	gameState_t gameState;	//!< the current game state (menu, one player mode, credits page, etc.)
	float simSpeed;			//!< speed of the simulation (number of simulation seconds for each real seccond)
	long int lastDraw;		//!< the unix time in milliseconds for the start of the last draw call
	float totTime;			//!< the total time since the start of the game (reset when the state changes)

	//maximum dimension for texture images
	int maxDim;				//!< maximum width or height for any OpenGL texture (for deciding which font to load)

	//menu buttons
	button_t SinglePlayerButton, 				//!< button for starting a single player game
			TwoPlayerButton;					//!< button for starting a two player game

	button_t CreditsButton,						//!< button for showing credits
			FullscreenButton,					//!< button for toggling fullscreen
			InstructionsButton;					//!< button for showing instructions

	//otherButtons
	button_t ExitButton;						//!< button for exiting the game
	button_t NextButton;						//!< button for advancing to the next page in the manual
	button_t PrevButton;						//!< button for moving to the previous page in the manual

	//mouse stuff
	vector3 mousePos;							//!< the position of the mouse cursor (OpenGL coordinates)
	int mousex,									//!< the x coordinate of the mouse cursor on the window (pixels)
		mousey;									//!< the y coordinate of the mouse cursor on the window (pixels)
	bool leftClick;								//!< true if a left click even has occured since it was last checked

	//level stuff
	sim_level_t levelData;						//!< data for this level (locations of objects and wind speed/direction)
	float windAngle;							//!< the angle for the arraow that represents the wind (radians)
	float windPower;							//!< the relative power of the wind, for determining the speed at which the arrow waves
	int level;									//!< the ID for this level
	int level2;									//!< the level that player 2 is on
	int loadLevel;								//!< the next level to load (this is only different to 'level' in 2 player mode)
	float endTime;								//!< the time at which the game finished (for the purposes of playing the exit animation)

	//stick men
	stickman_t myStickMan;						//!< a stickman object for the character
	stickman_t miniStickMan,					//!< a small stickman for the life indicator
				miniStickMan2;

	//physics simulation stuff
	physics_world_t physWorld;					//!< the physics simulation world
	physics_object_t projectile;				//!< our initial projectile object
	physics_object_t *projectileP;				//!< a pointer to the world copy of the projectile object
	constraint_t floorConstraint;				//!< a constraint to stop the projectile falling under the ground

	//game variables
	bool hasFired;
	bool hasWon, hasDied, isGameOver;
	int lives,									//!< number of lives for player 1
		lives2;									//!< number of lives for player 2
	int player;									//!< ID of the current player (1 or 2)
	int numPlayers;								//!< number of players in the game (1 or 2)
	int loser; 									//!< the ID of the player that lost
	float timeLeft;								//!< the remaining time to complete a level in two player mode

	//textures
	bitmap_t *grassBitmap;						//!< a bitmap object for loading the grass texture
	unsigned int grassTexture;					//!< the texture ID for grass as assigned by OpenGL

	//Fonts
	bitmap_t	*MonospaceBitmap,				//!< bitmap object for monospace font
				*SketchyBitmap;					//!< bitmap object for the 'sketchy' font
	unsigned int	MonospaceFont,				//!< the texture ID for monospace fontmap as assigned by OpenGL
					SketchyFont;				//!< the texture ID for 'sketchy' fontmap as assigned by OpenGL

	//manual
	int manPage;								//!< the ID of the manual page being viewed
} clab_assignment_data_t;

/**
 * This is one of only two global variables needed for the entire game. It handles all game variables.
 * This must be defined globally as it is required by functions that are called by FreeGLUT.
 * Functions called by FreeGLUT cannot be given custom parameters.
 * This Global variable is therefore unavoidable when using FreeGLUT callbacks.
 */
clab_assignment_data_t gameData;

/**
 *Draw the grass with the grass tecture
 */
void drawFloor();

/**
 * Handles keyboard events (Called by FreeGLUT)
 * @param key	a character representing the key that was pressed.
 * @param x		The x position of the mouse (in pixels, not used)
 * @param y		The y position of the mouse (in pixels, not used)
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Handles special keyboard press events such as arrow keys and  (Called by FreeGLUT)
 * @param key	a key ID representing the key that was pressed.
 * @param x		The x position of the mouse (in pixels, not used)
 * @param y		The y position of the mouse (in pixels, not used)
 */
void keyboardSpecial(int key, int x, int y);

/**
 * Handles special keyboard release events such as arrow keys and  (Called by FreeGLUT)
 * @param key	a key ID representing the key that was released.
 * @param x		The x position of the mouse (in pixels, not used)
 * @param y		The y position of the mouse (in pixels, not used)
 */
void keyboardSpecialUp(int key, int x, int y);

/**
 * Handles mouse button events (press and release, called by FreeGLUT)
 * @param button	The number of the button pressed or released
 * @param state		The state of the button (0 = pressed, 1 = released)
 * @param x			The x position of the mouse (in pixels, not used)
 * @param y			The y position of the mouse (in pixels, not used)
 */
void mouse(int button, int state, int x, int y);

/**
 * Handles mouse movement events (Called by FreeGLUT)
 * @param x	The x position of the mouse (in pixels, not used)
 * @param y	The y position of the mouse (in pixels, not used)
 */
void motion(int x, int y);

/**
 * draws a wavy arrow using OpenGL.
 * @param pos	Decides the start position for the wave.
 */
void drawArrow (float pos);

/**
 * Draws an arrow of the correct rotation and wave speed to represent the wind for the current level
 */
void drawWind();

/**
 * Initialises the menu page
 */
void initMenu();

/**
 * starts the menu page again, from the begining
 */
void restartMenu();

/**
 * Animates a floating point value between a given value (animationDistance) over a given time (animationTime)
 * This is used when items roll in from the sides on the main menu
 * @param animationTime			The total time for the animation to elapse
 * @param animationDistance		The total distance the value should move
 * @param curTime				The current time for the animation (can be in any unit that matches the units for animationTime)
 * @return	the current animation value.
 */
float motionAnimation(float animationTime, float animationDistance, float curTime);

/**
 * Draws the main menu on the screen
 * @param time_delta	The time since the last draw call (for simulating physics properly)
 */
void drawGameMenu(float time_delta);

/**
 * Initialises the game scene (common to two and one player games)
 */
void initGame();

/**
 * Initialises the single player game
 */
void initOnePlay();

/**
 * Restart the game (one player or two player)
 */
void restartGame();

/**
 * Restarts the one player game.
 * This starts at the current level and not the first level. This is called between levels
 */
void restartOnePlay();

/**
 * Draws the Level number and number of lives along with a visual representation of the lives in the form of stickmen
 * @param levelText		A pointer to a null-terminated string that contains the level text (eg. "Level 3")
 */
void drawStats(const char *levelText);

/**
 * Draws text using the large sketchy font near the top of the screen
 * @param text	The text to display
 */
void drawHeaderText(const char* text);

/**
 * Handles all of the firing of the bow and arrow
 * This includes handling button clicks, calculating the aim angle and providing the physics simulation with an impulse
 */
void handleFiring();

/**
 * Draws the projectile in its current position
 */
void drawProjectile();

/**
 * Draws the level currently loaded (the obstacles and the target)
 */
void drawLevel();

/**
 * Aims the stickman's bow at the current cursor position
 */
void aimBowAtCursor();

/**
 * Check if the arrow hit the floor and bounce if it did
 */
void handleFloorBounce();

/**
 * Check to see if the arrow has hit or will hit the target in the next time frame and advance to the next level if so.
 * @param time_delta	The time in which the collision must occur
 */
void handleTargetHit(float time_delta);

/**
 * deducts one life from the current player
 */
void loseLife();

/**
 * Check to see if the arrow has hit or will hit a death obstacle in the next time frame and deduct lives if so.
 * @param time_delta	The time in which the collision must occur
 */
void handleObstaclesHit(float time_delta);

/**
 * respond to left and right arrow key presses.
 * @param time_delta	The time the stickman will be walking if a button is pressed
 */
void handleWalk(float time_delta);

/**
 * manages buttons within the main game scene
 * @param goTime	the simulation time after which buttons are active (to allow for the intro animation to play)
 */
void manageGameButtons(float goTime);

/**
 * Draws the game scene for either the one or two player game.
 * @param time_delta	The time since the last drawing
 */
void drawGame(float time_delta);

/**
 * Draws the scene for the one player game
 * @param time_delta	The time since the last drawing
 */
void drawOnePlay(float time_delta);

/**
 * Initialises the two player game
 */
void initTwoPlay();

/**
 * Restarts the two player game
 */
void restartTwoPlay();

/**
 * Draws the two player game scene
 * @param time_delta	The time since the last draw of the game scene
 */
void drawTwoPlay(float time_delta);

/**
 * Initialise the instruction view
 */
void initInstructions();

/**
 * Restart the instruction view (does nothing, left in for completeness)
 */
void restartInstructions();

/**
 * Draws the instructions view
 * @param time_delta	The time since the last draw.
 */
void drawInstructions(float time_delta);

/**
 * Initialises the credits page
 */
void initCredits();

/**
 * Restarts the credits page (currently not needed but kept here for completeness as each mode has a function like this)
 */
void restartCredits();

/**
 * Draws the credits screen
 * @param time_delta	The time since the last draw (not used)
 */
void drawCredits(float time_delta);

/**
 * Calls the appropriate initialisation function for the current game state
 * @param state	The state to initialise
 */
void initialiseGameState(gameState_t state);

/**
 * Calls the appropriate restart function for the current game state
 * @param state		The state to restart
 */
void restartGameState(gameState_t state);

/**
 * Sets the current game state and initialises it.
 * @param newState	The state to which the game will change
 */
void setGameState(gameState_t newState);

/**
 * Same as setGameState except the state is restarted without being initialised.
 * @param newState	The state to restart
 */
void reSetGameState(gameState_t newState);

/**
 * Get the current system time in milliseconds
 * @return	The current system time in milliseconds
 */
long int getTimeMilliSeconds();

/**
 * Draws the OpenGL window
 */
void drawGLWindow();

/**
 * The function that is called before the application is exited.
 * This is where any remaining allocated memory is freed
 */
void exitFunc();

/**
 * The main function, (called by the OS when the application starts)
 * @param argc	Nuimber of arguments passed to the application
 * @param argv	a pointer to an array of arguments
 * @return	(This is only relevant to the OS) 0 for success, anything else otherwise
 */
int main (int argc, char **argv);

#endif //MAIN_PROGRAM_INCLUDE

