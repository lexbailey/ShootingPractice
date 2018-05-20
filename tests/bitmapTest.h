/*! \file bitmapTest.h
    \brief A quick test of the bitmap loader and the font rendering libraries
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This test program loads three different fontmap image from BMP files and renders the same text with each one
    The first is the "Sketchy" font in high resolution (4096 pixels wide), the second is the same in a lower
    resolution (1024 pixels wide) the last is the monospace font (1024 pixels wide).
    On some systems, OpenGL will limit the size of the bitmaps that can be loaded as textures. It is not common
    to find one that is not capable of loading 1024 pixel wide images and so this is the maximum requirement.
    On systems that can handle it however, the larger resolution images will can be used.

    (University of York C Programming Labs assessment)
*/

#ifndef BITMAP_TEST_PROGRAM_INCLUDE
#define BITMAP_TEST_PROGRAM_INCLUDE
#include "../ogl_gui/glwindow.h"
#include "../ogl_gui/glDrawFuncs.h"
#include "../ogl_gui/colours.h"
#include "../ogl_gui/bitmaps.h"
#include "../ogl_gui/bitmapFonts.h"

bitmap_t *myBitmap1, *myBitmap2, *myBitmap3;
unsigned int myTextureID1, myTextureID2, myTextureID3;

/**
 * Draw the scene, called by the glWindow
 */
void drawGLWindow();
int main (int argc, char **argv);

#endif //BITMAP_TEST_PROGRAM_INCLUDE
