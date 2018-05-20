/*! \file errors.h
    \brief Reports full error messages from OpenGL
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This file provides a simple OpenGL error reporting function

    (University of York C Programming Labs assessment)
*/

#ifndef GL_ERRORS_INCLUDE
#define GL_ERRORS_INCLUDE

#include <stdio.h>
#include <GL/gl.h>

/**
 * Prints a message describing the error from the last OpenGL call (if it did error)
 */
void reportErrors();

#endif //GL_ERRORS_INCLUDE
