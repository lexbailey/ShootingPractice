#include "bitmapTest.h"

//CLab assignment - graphics option.
//Copyright Daniel Bailey 2013

void drawGLWindow(){
	//draw stuff here

	glTranslatef(0.0f, +0.4f, 0.0f);
	bitmapFontGLRenderTextCentre(myTextureID1, "This is a bitmap font from a BMP image!", 0.25f);
	glTranslatef(0.0f, -0.4f, 0.0f);
	bitmapFontGLRenderTextCentre(myTextureID2, "This is a bitmap font from a BMP image!", 0.25f);
	glTranslatef(0.0f, -0.4f, 0.0f);
	bitmapFontGLRenderTextCentre(myTextureID3, "This is a bitmap font from a BMP image!", 0.25f);

}


int main (int argc, char **argv) {
	glwindow_init(argc, argv); //create the 3D view window (freeglut)
	glwindow_setDrawFunc(drawGLWindow); //set the callback for the draw funcion

	//myBitmap = loadBitmap("res/MonoFont.bmp");
	myBitmap1 = bitmapLoad("res/OrangeJuiceFont1024.bmp");
	myBitmap2 = bitmapLoad("res/OrangeJuiceFont4096.bmp");
	myBitmap3 = bitmapLoad("res/MonoFont.bmp");
	if (myBitmap1 && myBitmap2 && myBitmap3){
		myTextureID1 = bitmapToGLTexture(myBitmap1);
		myTextureID2 = bitmapToGLTexture(myBitmap2);
		myTextureID3 = bitmapToGLTexture(myBitmap3);

		glWindowData.translateEnabled = true;
		glWindowData.rotateEnabled = true;
		glWindowData.zoomEnabled = true;

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		glwindow_show();//go!
	}
	return 0;
}

