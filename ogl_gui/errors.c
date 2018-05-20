/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See errors.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "errors.h"

void reportErrors() {
	//Get an error number from OpenGL
	GLenum error = glGetError();

	//Check to see if there was an error
	if (error != GL_NO_ERROR) {

		//Print the raw error code
		printf("OpenGL error code: %d\n", error);

		//Print a more meaningful error message
		switch (error) {
		case GL_INVALID_ENUM:
			printf("Invalid Enum\n");
			break;
		case GL_INVALID_VALUE:
			printf("Invalid Value\n");
			break;
		case GL_INVALID_OPERATION:
			printf("Invalid Operation\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("Invalid Framebuffer Operation\n");
			break;
		case GL_OUT_OF_MEMORY:
			printf("Out Of Memory\n");
			break;
		case GL_STACK_UNDERFLOW:
			printf("Stack Underflow\n");
			break;
		case GL_STACK_OVERFLOW:
			printf("Stack Overflow\n");
			break;
		}
	}
}
