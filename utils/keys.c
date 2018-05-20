#include "keys.h"
#include <GL/freeglut.h>

void setSpecialKeyState(int key, bool state){

	//Arrow keys
	if ((key >= GLUT_KEY_LEFT) && (key <= GLUT_KEY_DOWN)){
		int myKey = (key-GLUT_KEY_LEFT) + KEY_A_LEFT;
		//if the key is an arrow key then set the state in the arrow key array
		keyData.arrowKeysPressed[myKey] = state;
	}

	//Function keys
	if ((key >= GLUT_KEY_F1) && (key <= GLUT_KEY_F12)){
		int myKey = (key-GLUT_KEY_F1) + KEY_F_1;
		//if the key is an F key then set the state in the FKeys array
		keyData.FKeysPressed[myKey] = state;
	}
}

//set the correct state
void onGLUTSpecialDown(int key){
	setSpecialKeyState(key, true);
}

void onGLUTSpecialUp(int key){
	setSpecialKeyState(key, false);
}

//these ones are easy
void onGLUTKeyDown(unsigned char key){
	keyData.keyPressed[key] = true;
}

void onGLUTKeyUp(unsigned char key){
	keyData.keyPressed[key] = false;
}

void initKeyPressed(){
	int i;
	for (i = 0; i<= 3; i++){
		//initialise the first four keys for each array
		keyData.keyPressed[i] = false;
		keyData.FKeysPressed[i] = false;
		keyData.arrowKeysPressed[i] = false;
	}
	for (i = 4; i<= 11; i++){
		//initialise the next 8 keys for the larger arrays
		keyData.keyPressed[i] = false;
		keyData.FKeysPressed[i] = false;
	}
	for (i = 12; i<= 255; i++){
		//init the rest for the really big one
		keyData.keyPressed[i] = false;

	}
}
