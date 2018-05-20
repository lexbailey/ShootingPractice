/*! \file myColours.h
    \brief definitions of basic colours for use in the game
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    Defines particular colours used in the game, ready to be used with the colourEnable() function

    (University of York C Programming Labs assessment)
*/

#ifndef MY_COLOURS_INCLUDE
#define MY_COLOURS_INCLUDE

#define COLOUR_RED colourRGBByte(255, 0, 0)						//!< Bright red
#define COLOUR_GREEN colourRGBByte(0, 255, 0)					//!< Bright green
#define COLOUR_BLUE colourRGBByte(0, 0, 255)					//!< Bright blue
#define COLOUR_WHITE colourRGBByte(255, 255, 255)				//!< Bright white

#define COLOUR_GRASS colourRGBByte(138,255,122)					//!< Grass colour
#define COLOUR_STICKMAN1 colourRGB(1.0f, 0.2f, 0.2f)			//!< The colour of the first stick man (mostly red)
#define COLOUR_STICKMAN2 colourRGB(0.2f, 0.2f, 1.0f)			//!< The colour of the second stick man (mostly blue)
#define COLOUR_TARGET colourRGB(1.0f, 1.0f, 0.5f)				//!< The colour of the targets, yellow

#define COLOUR_ONEPLAYER_BUTTON colourRGBByte(255, 118, 102)	//!< Red colour for buttons, despite the name this does most buttons
#define COLOUR_TWOPLAYER_BUTTON colourRGBByte(102, 118, 255)	//!< Blue colour for the two player button

#define COLOUR_EXIT_BUTTON colourRGBByte(255, 255, 0)			//!< Yellow colour for the exit button

#define COLOUR_OBS_BOUNCE colourRGBByte(50,255,50)				//!< Colour of the bouncy obstacles (greenish)
#define COLOUR_OBS_DIE colourRGBByte(170,90,90)					//!< Colour of the death obstacles (redish - not radish, radish won't cause death in most cases)

#endif //MY_COLOURS_INCLUDE
