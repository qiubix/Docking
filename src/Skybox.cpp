//Skybox.cpp
//Implementation of Skybox class methods.

#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "GLUT.H"
#include <iostream>
#include "Skybox.h"
#include "ImageLoader.h"



//Skybox constructor, gathers images for textures and loads them to walls of the box
Skybox::Skybox(): width(500.0f)
{
	std::cout<<"Skybox::Skybox()\n";
	file_[0] = "skybox/front.bmp";
	file_[1] = "skybox/back.bmp";
	file_[2] = "skybox/left.bmp";
	file_[3] = "skybox/right.bmp";
	file_[4] = "skybox/top.bmp";
	file_[5] = "skybox/bottom.bmp";

	loadAllTextures();
}

//Skybox destructor
Skybox::~Skybox() {
	std::cout<<"Skybox::~Skybox()\n";
}


//Draws skybox around the camera
void Skybox::drawSkybox(Camera* cam) {
	//glPushMatrix();
	glDisable(GL_CULL_FACE);
	glPushMatrix();
 
    // Reset and transform the matrix.
    glLoadIdentity();
    gluLookAt(
        0,0,0,
        cam->m_position[0],cam->m_position[1],cam->m_position[2],
        0,1,0);
 
    // Enable/Disable features
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);
    //glDisable(GL_BLEND);
 
		//Front
		glBindTexture(GL_TEXTURE_2D, cube[0]);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 1); glVertex3f( -width, width, -width );
			glTexCoord2f(1, 1); glVertex3f( width, width, -width );
			glTexCoord2f(1, 0); glVertex3f( width, -width, -width );
			glTexCoord2f(0, 0); glVertex3f( -width, -width, -width );
		glEnd();
		//Back
		glBindTexture(GL_TEXTURE_2D, cube[1]);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 1); glVertex3f( width, width, width );
			glTexCoord2f(1, 1); glVertex3f( -width, width, width );
			glTexCoord2f(1, 0); glVertex3f( -width, -width, width );
			glTexCoord2f(0, 0); glVertex3f( width, -width, width );
		glEnd();
		//Left
		glBindTexture(GL_TEXTURE_2D, cube[2]);
		glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glTexCoord2f(0, 1); glVertex3f( -width, width, width );
			glTexCoord2f(1, 1); glVertex3f( -width, width, -width );
			glTexCoord2f(1, 0); glVertex3f( -width, -width, -width );
			glTexCoord2f(0, 0); glVertex3f( -width, -width, width );
		glEnd();
		//Right
		glBindTexture(GL_TEXTURE_2D, cube[3]);
		glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 1); glVertex3f( width, width, -width );
			glTexCoord2f(1, 1); glVertex3f( width, width, width );
			glTexCoord2f(1, 0); glVertex3f( width, -width, width );
			glTexCoord2f(0, 0); glVertex3f( width, -width, -width );
		glEnd();
		//Top
		glBindTexture(GL_TEXTURE_2D, cube[4]);
		glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glTexCoord2f(0, 1); glVertex3f( -width, width, width );
			glTexCoord2f(1, 1); glVertex3f( width, width, width );
			glTexCoord2f(1, 0); glVertex3f( width, width, -width );
			glTexCoord2f(0, 0); glVertex3f( -width, width, -width );
		glEnd();
		//Bottom
		glBindTexture(GL_TEXTURE_2D, cube[5]);
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 1); glVertex3f( -width, -width, -width );
			glTexCoord2f(1, 1); glVertex3f( width, -width, -width );
			glTexCoord2f(1, 0); glVertex3f( width, -width, width );
			glTexCoord2f(0, 0); glVertex3f( -width, -width, width );
		glEnd();
	
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_BLEND);
 	
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_CULL_FACE);
}


//loads all textures onto the cube
void Skybox::loadAllTextures() {
	for (int i = 0; i < 6; ++i)
		cube[i] = loadTexture(file_[i].c_str());
}