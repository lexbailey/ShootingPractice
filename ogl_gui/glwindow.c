/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See glwindow.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "glwindow.h"

//Private function for initialising the OpenGL lighting and some other things
void glwindow_initLights() 
{

	glDepthFunc(GL_LEQUAL);           // the type of depth test to do
	glEnable(GL_DEPTH_TEST);          // enables depth testing

	glShadeModel(GL_SMOOTH);          // enables smooth color shading

	//Turn on all anti-aliasing possible
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable (GL_POLYGON_SMOOTH);
	glEnable (GL_LINE_SMOOTH);

	//Set the blending method (source decides alpha)
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Allow objects under light to have colour
	glEnable(GL_COLOR_MATERIAL);

	//Automatically scale normals to length 1
	glEnable(GL_NORMALIZE);

	//Set up the lighting
	glEnable(GL_LIGHTING);

	//first light
	glEnable(GL_LIGHT0);
	GLfloat light_position[] = { -3.0f, 2.0f, -1.0f, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);

	//Second light
	glEnable(GL_LIGHT1);
	GLfloat light_position1[] = { 3.0f, 2.0f, -1.0f, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	GLfloat light_amb1[] = { 0.6, 0.6, 0.6, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);

	//Set the material with which to draw.
	GLfloat diffuseMaterial[] = { 0.5f,0.5f, 0.5f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);

}

//Private function, called by FreeGLUT
void glwindow_Render()
{

	//set background colour (sky blue ish)
	glClearColor(1.0f/255.0f*186.0f, 1.0f/255.0f*200.0f, 1.0f/255.0f*220.0f, 0.0f);
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Reset the translation matrix to the default before drawing anything
	glLoadIdentity();

	glPushMatrix();
		if (glWindowData.rawDrawCallBack!=NULL){
			//let the application know we are about to draw.
			glWindowData.rawDrawCallBack();
		}
		glTranslatef(0,0,-40.0f); //move back a little
		#ifdef DEBUG_AXES
		glBegin(GL_LINES);
			glColor3f(0.0,0.0,1);
			glVertex3f(0,0,0);
			glVertex3f(0,0,100);
			glColor3f(1,0,0);
			glVertex3f(0,0,0);
			glVertex3f(100,0,0);
			glColor3f(0,1,0);
			glVertex3f(0,0,0);
			glVertex3f(0,100,0);
		glEnd();
		#endif

		//Apply the transformations from the mouse commands
		glScalef(glWindowData.scale, glWindowData.scale, glWindowData.scale);
		glTranslatef(glWindowData.xshift2,glWindowData.yshift2,0.0f);
		glRotatef(glWindowData.zrot2, 0.0f, 0.0f, 1.0f);
		glRotatef(glWindowData.xrot2, 1.0f, 0.0f, 0.0f);
		glRotatef(glWindowData.yrot2, 0.0f, 1.0f, 0.0f);
			//#################################################
			//## Start draw                                  ##
			//#################################################
			//if debugging local axes...
			#ifdef DEBUG_LOCAL_AXES
				glBegin(GL_LINES);
					glColor3f(0.0,0.0,1);
					glVertex3f(0,0,0);
					glVertex3f(0,0,100);
					glColor3f(1,0,0);
					glVertex3f(0,0,0);
					glVertex3f(100,0,0);
					glColor3f(0,1,0);
					glVertex3f(0,0,0);
					glVertex3f(0,100,0);
				glEnd();
			#endif //DEBUG_LOCAL_AXES

			//if debugging mouse position...
			#ifdef DEBUG_MOUSE_POS
				vector3 mouse = getOGLPos(mousex, mousey);
				drawCircle(mouse, 1.0f, 30);
			#endif //DEBUG_MOUSE_POS

			//Call draw function
			if (glWindowData.drawCallBack!=NULL){
				glWindowData.drawCallBack();
			}
			//#################################################
			//##  End draw                                   ##
			//#################################################
	glPopMatrix();
	glutSwapBuffers();	//Swap the front and back buffers (put the next frame on the screen)
	
	if (glWindowData.drawDoneCallBack!=NULL){
		//Notify the application that drawing is done
		glWindowData.drawDoneCallBack();
	}	
}

//Private function, called by FreeGLUT when the window is re-sized
void glwindow_reshape (int width, int height) {

	//This simple resize method will not maintain aspect ration :-( this can be fixed, perhaps later...
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); 			//Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); 						//Reset the projection matrix
	glOrtho(-5, 5, -3, 3, 0.1f, 1000.0f);	//Tell OpenGL how we want the coordinates set up (Orthographic mode, not projection)
	glMatrixMode(GL_MODELVIEW); 			//Switch back to the model view matrix, so that we can start drawing shapes correctly
}

//Private function, called by FreeGLUT when a mouse button event is detected
void glwindow_mouse(int button, int state, int x, int y){


	if (glWindowData.mouseCallBack!=NULL){
		//Let the application know about the mouse click
		glWindowData.mouseCallBack(button, state, x, y);
	}

	//log which buttons are pressed
	glWindowData.mousebuttons[button] = (state == 0);

	//if any of the first three buttons was pressed, remember the start position
	if (glWindowData.mousebuttons[0]||glWindowData.mousebuttons[1]||glWindowData.mousebuttons[2]){
		glWindowData.startx = x;
		glWindowData.starty = y;
	}	

	//if the middle button is released, store the new rotation value
	if (!glWindowData.mousebuttons[1]){
		glWindowData.zrot = glWindowData.zrot2;
		glWindowData.xrot = glWindowData.xrot2;
		glWindowData.yrot = glWindowData.yrot2;
	}

	//left button released, store new translation
	if (!glWindowData.mousebuttons[0]){
		glWindowData.xshift = glWindowData.xshift2;
		glWindowData.yshift = glWindowData.yshift2;
	}

	//right click released, store new zoom
	if (!glWindowData.mousebuttons[2]){
		glWindowData.scale2 = glWindowData.scale;
	}

	//if zoom is allowed then act on the scroll wheel events
	if (glWindowData.zoomEnabled){
		if (button == 4){
			glWindowData.scale /= 1.1;
			glWindowData.scale2 = glWindowData.scale;
			glutPostRedisplay();
		}
		if (button == 3){
			glWindowData.scale *= 1.1;
			glWindowData.scale2 = glWindowData.scale;
			glutPostRedisplay();
		}
	}

}

//These private keyboard functions (called by FreeGLUT) are nothing special, they simply pass messages on to the application
void glwindow_keyboard(unsigned char key, int x, int y){
	if (glWindowData.keyboardCallBack!=NULL){
		glWindowData.keyboardCallBack(key, x, y);
	}
}

void glwindow_keyboardSpecial(int key, int x, int y){
	if (glWindowData.keyboardSpecialCallBack!=NULL){
		glWindowData.keyboardSpecialCallBack(key, x,y);
	}
}

void glwindow_keyboardSpecialUp(int key, int x, int y){
	if (glWindowData.keyboardSpecialUpCallBack!=NULL){
		glWindowData.keyboardSpecialUpCallBack(key, x,y);
	}
}

//Private function called by FreeGLUT when the mouse moves
void glwindow_motion(int x, int y){

	//Store mouse position
	glWindowData.mousex = x;
	glWindowData.mousey = y;

	//Rotation
	if ((glWindowData.mousebuttons[1]) && (glWindowData.rotateEnabled)){


		//The movement in the X axis determines Y axis rotation.
		int differencex = glWindowData.startx - x;
		glWindowData.yrot2 = (glWindowData.yrot - differencex/5)%360;
		
		//The movement in the Y axis causes a change in both X and Z rotation
		int differencey = (glWindowData.starty - y);
		//The change for each axis depends on the rotation in Y
		float xfactor = -cos(glWindowData.yrot2 IN_RADIANS);
		float zfactor = sin(glWindowData.yrot2 IN_RADIANS);
		glWindowData.xrot2 = (glWindowData.xrot + ((differencey/5)*xfactor));
		glWindowData.zrot2 = (glWindowData.zrot + ((differencey/5)*zfactor));
		glutPostRedisplay();

	}
	else{
		//Translation is simple
		if((glWindowData.mousebuttons[0]) && (glWindowData.translateEnabled)){
			glWindowData.xshift2 = glWindowData.xshift - ((glWindowData.startx - x)/5);
			glWindowData.yshift2 = glWindowData.yshift + ((glWindowData.starty - y)/5);
			glutPostRedisplay();
		}
		//Zoom is also simple
		if((glWindowData.mousebuttons[2]) && (glWindowData.zoomEnabled)){
			glWindowData.scale = glWindowData.scale2* pow(1.1, ((glWindowData.starty - y)/50.0f));
		}
	}

	if (glWindowData.motionCallBack!=NULL){
		//Let the application know about the mouse motion
		glWindowData.motionCallBack(x,y);
	}
}

//These functions simply set the callback pointers
void glwindow_setRawDrawFunc (void (*mf)()){
	glWindowData.rawDrawCallBack = mf;
}

void glwindow_setDrawFunc (void (*mf)()){
	glWindowData.drawCallBack = mf;
}

void glwindow_setDoneDrawFunc (void (*mf)()){
	glWindowData.drawDoneCallBack = mf;
}

void glwindow_setKeyboardFunc (void (*mf)(unsigned char, int, int)){
	glWindowData.keyboardCallBack = mf;
}

void glwindow_setKeyboardSpecialFunc (void (*mf)(int, int, int)){
	glWindowData.keyboardSpecialCallBack = mf;
}

void glwindow_setKeyboardSpecialUpFunc (void (*mf)(int, int, int)){
	glWindowData.keyboardSpecialUpCallBack = mf;
}

void glwindow_setMotionFunc (void (*mf)(int, int)){
	glWindowData.motionCallBack = mf;
}

void glwindow_setMouseFunc (void (*mf)(int, int, int, int)){
	glWindowData.mouseCallBack = mf;
}

//Init a GL window
void glwindow_init(int argc, char **argv){
	//By default transformations are disabled
	glWindowData.zoomEnabled = false;
	glWindowData.rotateEnabled= false;
	glWindowData.translateEnabled = false;

	//By default no rotation is applied
	glWindowData.zrot = 0;
	glWindowData.zrot2 = 0;
	glWindowData.xrot = 0;
	glWindowData.xrot2 = 0;
	glWindowData.yrot = 0;
	glWindowData.yrot2 = 0;
		
	//The scale starts at 1
	glWindowData.scale = 1;
	glWindowData.scale2 = 1;

	//The centre stays in the centre
	glWindowData.xshift = 0;
	glWindowData.yshift = 0;
	glWindowData.xshift2 = 0;
	glWindowData.yshift2 = 0;
		
	//Not buttons are clicked
	glWindowData.mousebuttons[0] = false;
	glWindowData.mousebuttons[1] = false;
	glWindowData.mousebuttons[2] = false;

	//These values don't really matter but it's best if everything is inititalised
	glWindowData.startx = 0;
	glWindowData.starty = 0;

	glutInit(&argc, argv); 				// Initialize GLUT
	glutInitDisplayMode (GLUT_DOUBLE);	// Set up a double display buffer
	glutInitWindowSize (1000, 600);		// Set the width and height of the window
	glutInitWindowPosition (50, 50);	// Set the position of the window
	glutCreateWindow ("CLab Assignment - Graphical Game"); // Set the title for the window

	//Set up our callback functions
	glutDisplayFunc(glwindow_Render);
	glutIdleFunc(glwindow_Render);
	glutReshapeFunc(glwindow_reshape);
	glutMouseFunc(glwindow_mouse);
	glutMotionFunc(glwindow_motion);
	glutPassiveMotionFunc(glwindow_motion);
	glutKeyboardFunc(glwindow_keyboard);
	glutSpecialFunc(glwindow_keyboardSpecial);
	glutSpecialUpFunc(glwindow_keyboardSpecialUp);

	glutIgnoreKeyRepeat(true); //we need to ignore key press auto repeats
	glwindow_initLights();		//Initialise the rest of our stuff
	glLineWidth(2.0f);			//And last but not least, make the line width 2
}


//this function adapted from: http://nehe.gamedev.net/article/using_gluunproject/16013/
vector3 glWindowGetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
 
	//Get a copy of the modelview and projection matricies and the viewport info
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
 
	winX = (float)x;
	winY = (float)(viewport[3] - y); //subtract Y from viewport height (flip y coordinate)

	//read the depth of the pixel under the mouse cursor to get a z value
	glReadPixels( x, (int)(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	//Un-project the x, y and z coordinates from the screen to the model to get the OpenGL mouse position
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//All done, return the position as a vector
	vector3 output;
	output.x = (float)posX;
	output.y = (float)posY;
	output.z = (float)posZ;

	return output;
}

void glwindow_show(){
	glutMainLoop(); // Enter GLUT's main loop
}

