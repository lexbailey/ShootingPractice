
#include "glWindowANDglDrawFuncsTest.h"


void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 'r': case 'R': 
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
		break;
		case 'g': case 'G': 
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
		break;
		case 'b': case 'B': 
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
		break;
	}
}

void motion(int x, int y){
	mousex = x;
	mousey = y;
}

void drawGLWindow(){

	mousePos = glWindowGetOGLPos(mousex,mousey);
	mousePos.z = 0;

	float distance = vector3DistanceBetween(vector3GetNull(), mousePos);

	glColor3f(red, green, blue);
	drawFuncLine(vector3GetNull(), mousePos);
	drawFuncCircle(vector3GetNull(), distance/10.0f, 30);
	drawFuncDisc(mousePos, distance/10.0f, 30);
}

int main (int argc, char **argv) {

	glwindow_init(argc, argv); //create the 3D view window (freeglut)
	glwindow_setDrawFunc(drawGLWindow); //set the callback for the draw funcion

	glwindow_setKeyboardFunc(keyboard);
	glwindow_setMotionFunc(motion);

	//initial colour
	red = 1.0f;
	green = 0.0f;
	blue = 0.0f;
     
	glwindow_show();//go!

	return 0;	    	
}

