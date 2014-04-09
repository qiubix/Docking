//DockingStation.cpp
//Implementation of class DockingStation's methods


#include <iostream>
#include "DockingStation.h"
#include "ImageLoader.h"

//constructor takes position of the docking station
DockingStation::DockingStation(float* position):width(10.0f),height(10.0f),length(160.0f){
	std::cout << "DockingStation::DockingStation();\n";
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	tex = loadTexture("textures/hull1.bmp");
}

//constructor takes dimentions of the docking station and its position
DockingStation::DockingStation(float width, float height, float length, float* position){
	std::cout << "DockingStation::DockingStation();\n";
	this->width = width;
	this->height = height;
	this->length = length;
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	tex = loadTexture("textures/hull1.bmp");
}

//destructor
DockingStation::~DockingStation(){
	std::cout << "DockingStation::DockingStation();\n";
}

float  DockingStation::getWidth(){ return width; }
float  DockingStation::getHeight(){ return height; }
float  DockingStation::getLength(){ return length; }
float* DockingStation::getPosition(){ return position; }


void DockingStation::drawDockingStation(){
	float stationWidth = width;
	float stationHeight = height;
	float stationLength = length;
	//glPushMatrix();

		//Front
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 1); glVertex3f( -stationWidth/2,  stationHeight/2, -stationLength/2 );
			glTexCoord2f(1, 1); glVertex3f(  stationWidth/2,  stationHeight/2, -stationLength/2 );
			glTexCoord2f(1, 0); glVertex3f(  stationWidth/2, -stationHeight/2, -stationLength/2 );
			glTexCoord2f(0, 0); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
		glEnd();
		//Back
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 1); glVertex3f(  stationWidth/2,  stationHeight/2, stationLength/2 );
			glTexCoord2f(1, 1); glVertex3f( -stationWidth/2,  stationHeight/2, stationLength/2 );
			glTexCoord2f(1, 0); glVertex3f( -stationWidth/2, -stationHeight/2, stationLength/2 );
			glTexCoord2f(0, 0); glVertex3f(  stationWidth/2, -stationHeight/2, stationLength/2 );
		glEnd();
		//Right
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glTexCoord2f(0, 1);  glVertex3f( -stationWidth/2,  stationHeight/2,  stationLength/2 );
			glTexCoord2f(16, 1); glVertex3f( -stationWidth/2,  stationHeight/2, -stationLength/2 );
			glTexCoord2f(16, 0); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
			glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, -stationHeight/2,  stationLength/2 );
		glEnd();
		//Left
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 1);  glVertex3f( stationWidth/2,  stationHeight/2, -stationLength/2 );
			glTexCoord2f(16, 1); glVertex3f( stationWidth/2,  stationHeight/2,  stationLength/2 );
			glTexCoord2f(16, 0); glVertex3f( stationWidth/2, -stationHeight/2,  stationLength/2 );
			glTexCoord2f(0, 0);  glVertex3f( stationWidth/2, -stationHeight/2, -stationLength/2 );
		glEnd();
		//Top
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glTexCoord2f(0, 16); glVertex3f( -stationWidth/2, stationHeight/2,  stationLength/2 );
			glTexCoord2f(1, 16); glVertex3f(  stationWidth/2, stationHeight/2,  stationLength/2 );
			glTexCoord2f(1, 0);  glVertex3f(  stationWidth/2, stationHeight/2, -stationLength/2 );
			glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, stationHeight/2, -stationLength/2 );
		glEnd();
		//Bottom
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 16); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
			glTexCoord2f(1, 16); glVertex3f(  stationWidth/2, -stationHeight/2, -stationLength/2 );
			glTexCoord2f(1, 0);  glVertex3f(  stationWidth/2, -stationHeight/2,  stationLength/2 );
			glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, -stationHeight/2,  stationLength/2 );
		glEnd();

	//glPopMatrix();
}