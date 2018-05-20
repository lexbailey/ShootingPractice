/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See bitmaps.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "bitmaps.h"

#define BITMAPS_COMPRESSION_NONE 0

#define BITMAPS_COLOURS_UNLIMITED 0

//This functions checks a loaded bitmap to see if it is a compatible type
//It is not in the header file as it is a private function
bool bitmapValidateCompatible(bitmap_t *bitmap) {

	//First check is that the bitmap header is not horrifically corrupt
	if (!((bitmap->bitmapHeader.ID[0] == 'B')
			&& (bitmap->bitmapHeader.ID[1] == 'M'))) {
		printf("Image file must be a bitmap.\n");
		return false;
	}

	//Make sure that the image data isn't compressed.
	if (bitmap->bitmapInfoHeader.compressionMethod != BITMAPS_COMPRESSION_NONE) {
		printf("Image file must be an uncompressed bitmap.\n");
		return false;
	}

	//We currently only support 24 bits per pixel
	if ((bitmap->bitmapInfoHeader.bitsPerPixel != 24)) {
		printf("Image file must have 24 bits per pixel. (\"R8 G8 B8\" / \"24Bit RGB\")\n");
		return false;
	}

	//The colour pallet must not be limited at all
	if (bitmap->bitmapInfoHeader.coloursInPalette != BITMAPS_COLOURS_UNLIMITED) {
		printf("Image file must have unlimited pallet.\n");
		return false;
	}

	//If that's all fine, we are valid, return true
	return true;
}

//This is the big meaty bitmap loading function.
bitmap_t *bitmapLoad(const char *fileName) {

	bitmap_t *output;					//pointer to our bitmap
	output = malloc(sizeof(bitmap_t));	//make space for a new bitmap

	if (output) {						//if space was available

		//For convenience, lets have some handy pointers to the bitmap's headers
		bitmapHeader_t *bitmapHeader = &(output->bitmapHeader);
		bitmapInfoHeader_t *bitmapInfoHeader = &(output->bitmapInfoHeader);

		//now try and open the file for reading
		FILE *input;
		input = fopen(fileName, "r");

		//If we can read the file then do so...
		if (input != NULL) {
			//First thing to do is read the two headers in.
			fread(bitmapHeader, sizeof(bitmapHeader_t), 1, input);
			fread(bitmapInfoHeader, sizeof(bitmapInfoHeader_t), 1, input);
			//Before loading anything else, make sure that this bitmap is compatible
			if (bitmapValidateCompatible(output)) {

				//get the dimensions of the bitmap
				int width, height;
				width = output->bitmapInfoHeader.pxWidth;
				height = output->bitmapInfoHeader.pxHeight;

				//make space for the pixel data
				output->data = malloc(output->bitmapInfoHeader.rawDataSize);
				if (output->data) {
					//move to the point in the file where the data starts
					fseek(input, output->bitmapHeader.dataStart, SEEK_SET);
					//read the pixel data into our new array
					fread(output->data, 1, output->bitmapInfoHeader.rawDataSize,
							input);
				} else {
					free(output);
					fclose(input);
					printf("Error loading bitmap file. Not enough Ram");
					return NULL;
				}
			} else {
				free(output);
				fclose(input);
				printf(
						"This bitmap file type is not supported. Load failed.\n");
				return NULL;
			}
		} else {
			free(output);
			printf("Oh no! Error loading bitmap file!\n");
			return NULL;
		}
		//when done, close the file
		fclose(input);
	}
	//return a pointer our bitmap structure
	return output;
}

//function for disposing of the data in a bitmap
void bitmapFree(bitmap_t *bitmap) {
	//we allocated space for the bitmap data and must free it.
	free(bitmap->data);
	//then we can free the actual bitmap (yes, this is our job, we malloced it)
	free(bitmap);
}

unsigned int bitmapToGLTexture(bitmap_t *bitmap) {
	unsigned int texture;

	//tell OpenGL to prepare for a texture to be added
	glGenTextures(1, &texture);

	//Errors are likely to appear after glGenTextures so report them if they did
	//(If the system is low on memory then this will show here)
	reportErrors();

	//Tell OpenGL we are working with the new texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set up the filters so that the image scales well
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//make sure the image is not set to repeat (we only see it once)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Our bitmap files store image data in BGR format and so OpenGL must be informed
	GLint internalFormat = GL_RGB;
	GLint format = GL_BGR;

	//Load the image into OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
			bitmap->bitmapInfoHeader.pxWidth, bitmap->bitmapInfoHeader.pxHeight,
			0, GL_BGR, GL_UNSIGNED_BYTE, bitmap->data);

	//Make sure the user knows if anything went wrong
	reportErrors();

	//Flush pending OpenGL commands
	glFlush();

	return texture;
}
