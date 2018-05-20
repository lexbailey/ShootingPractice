
#include "lineCircleIntersectTest.h"
#include "../physics/collisions.h"


void keyboard(unsigned char key, int x, int y){

}

void mouse(int button, int state, int x, int y){
	if ((button == 0)&& (state==0)){
		click = true;
	}
}

void motion(int x, int y){
	mousex = x;
	mousey = y;
}


void drawGLWindow(){

	mousePos = glWindowGetOGLPos(mousex,mousey);
	mousePos.z = 0;

	glColor3f(1.0f, 0.0f, 0.0f);
	drawFuncLine(lineStart, mousePos);

	if (collisionLineEntersCircle(lineStart, mousePos, circlePos, circleRad)){
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else{
		glColor3f(0.0f, 1.0f, 0.0f);
	}

	drawFuncCircle(circlePos, circleRad, 30);

	if (click){
		lineStart = mousePos;
	}
	click = false;
}

int main (int argc, char **argv) {

	glwindow_init(argc, argv); //create the 3D view window (freeglut)
	glwindow_setDrawFunc(drawGLWindow); //set the callback for the draw funcion

	glwindow_setKeyboardFunc(keyboard);
	glwindow_setMouseFunc(mouse);
	glwindow_setMotionFunc(motion);

	lineStart.x = 0.0f;
	lineStart.y = 0.0f;
	lineStart.z = 0.0f;

	circlePos = lineStart;
	circleRad = 1.0f;
     
	glwindow_show();//go!

	return 0;	    	
}

