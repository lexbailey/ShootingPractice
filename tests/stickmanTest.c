

#include "stickmanTest.h"

void drawFloor(){
	glColor3ub(138,255,122);
	vector3 P1, P2;
	P1.x = -5.0f; P1.y = -1.5f; P1.z = 0.0f;
	P2.x = 5.0f; P2.y = -3.0f; P2.z = 0.0f;
	drawFuncRectangle(P1, P2, 0);
}

void drawGLWindow(){
	//draw stuff here
	drawFloor();

	glPushMatrix();
		glTranslatef(0.0f,-1.50f,0.0f);
		stickManDraw(&myStickMan);
	glPopMatrix();
}


int main (int argc, char **argv) {

	glwindow_init(argc, argv); //create the 3D view window (freeglut)
	glwindow_setDrawFunc(drawGLWindow); //set the callback for the draw funcion

	glWindowData.translateEnabled = true;
	glWindowData.rotateEnabled = true;
	glWindowData.zoomEnabled = true;

	myStickMan.pos.x = 0;
	myStickMan.pos.y = 0;
	myStickMan.pos.z = 0;
	myStickMan.pose = pose;
	myStickMan.colour = colourRGB(1.0f, 0.0f, 0.0f);
	myStickMan.aimAngle = 45;
	myStickMan.pullBack = 10;
	stickManSetPose(&myStickMan, myStickMan.pose);

	glwindow_show();//go!

	return 0;	    	
}

