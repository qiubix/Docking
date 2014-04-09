//ImageLoader.cpp
//Contains definition of function declared in ImageLoader.h

#include <stdlib.h>
#include <iostream>
#include "SOIL.h"
#include "GLUT.H"
//#include <GL\glut.h>
#include "ImageLoader.h"


//Loads an image from path and loads it as a new texture. 
GLuint loadTexture(const char *path) {
	int width, height;
	GLuint texture;
	/* load an image file directly as a new OpenGL texture */
	//texture =  SOIL_load_OGL_texture (
	//	path,
	//	SOIL_LOAD_AUTO,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_INVERT_Y );
	
	unsigned char* img = SOIL_load_image(path, &width, &height, NULL, 0);

	if(img == 0)
		return 0;
	
	// Typical Texture Generation Using Data From The Bitmap
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE ); //set texture environment parameters
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	glBindTexture(GL_TEXTURE_2D, 0);
	//std::cout << "\nTexture " << path << " loaded..\nWidth = " << width << "\nHeight = " << height <<std::endl;

	return texture;
}