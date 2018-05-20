/*! \file bitmaps.h
    \brief Functions for loading bitmaps and generating textures in OpenGL
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file contains functions for loading 24 bpp uncompressed bitmaps and generating OpenGL textures from them.
    Resources used:
    - http://en.wikipedia.org/wiki/BMP_file_format
    - OpenGL Game Programming book, loading bitmap textures

    (University of York C Programming Labs assessment)
*/

#ifndef BITMAP_INCLUDE
#define BITMAP_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../utils/boolean.h"
#include "errors.h"

//These structures must be packed!
//http://gcc.gnu.org/onlinedocs/gcc/Type-Attributes.html
//see the "packed" attribute

///Initial bitmap header structure
typedef struct __attribute__((__packed__)) {
	char ID[2];			//!< 2 bytes - First two bytes are ascii chars to identify bitmap
	int32_t fileSize;	//!< 4 bytes - next four bytes are the size of the file
	uint16_t reserved0;	//!< 2 bytes - two reserved bytes
	uint16_t reserved1;	//!< 2 bytes - two more reserved bytes
	uint32_t dataStart;	//!< 4 bytes - these four bytes represent the start of the image data
} bitmapHeader_t;

///Bitmap info header structure
typedef struct __attribute__((__packed__)) {
	uint32_t infoHeaderSize;	//!< 4 bytes - indicates size of this header (should always be 40 bytes)
	int32_t pxWidth;			//!< 4 bytes - width of the image in pixels
	int32_t pxHeight;			//!< 4 bytes - height of the image in pixels
	uint16_t colourPlanes;		//!< 2 bytes - number of colour planes (Must be 1)
	uint16_t bitsPerPixel;		//!< 2 bytes - bits per pixel (we want 24)
	uint32_t compressionMethod; //!< 4 bytes - (0 = RGB) MUST BE 0
	uint32_t rawDataSize;		//!< 4 bytes - number of bytes in raw image data
	int32_t horizPPM;			//!< 4 bytes - Pixels Per Meter along width
	int32_t vertPPM;			//!< 4 bytes - Pixels Per Meter along height
	uint32_t coloursInPalette;	//!< 4 bytes - number of colours in the palelt (0 = default to max)
	uint32_t importantColours;  //!< 4 bytes - number of important colours (0 = default to max, ignore)
} bitmapInfoHeader_t;

///Structure for holding all bitmap information (including the image data)
typedef struct{
	bitmapHeader_t bitmapHeader;		//!< the bitmap header section
	bitmapInfoHeader_t bitmapInfoHeader;//!< the bitmap info header section
	unsigned char *data;				//!< the raw image data
} bitmap_t;

/**
 * Load a bitmap from a file into a bitmap_t structure
 * @param fileName	The path to the file that contains the bitmap
 * @return	Pointer to a bitmap structure with loaded bitmap data
 */
bitmap_t *bitmapLoad(const char *fileName);

/**
 * Free a loaded bitmap from memory
 * @param bitmap	The bitmap to be freed
 */
void bitmapFree(bitmap_t *bitmap);

/**
 * Register a bitmap as an OpenGL texture
 * @param bitmap	Pointer to the bitmap to be registered
 * @return	The OpenGL texture ID (for use with glBindTexture)
 */
unsigned int bitmapToGLTexture(bitmap_t *bitmap);


#endif //BITMAP_INCLUDE
