//Pelican.cpp
//Implementation of methods of the class Pelican


#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
#include "GLUT.H"
#include <iostream>
#include <math.h>
#include <limits>
#include "Pelican.h"
//#include "Drawer.h"
#include "ImageLoader.h"



Pelican::Pelican():height(1.5f),width(7.0f),length(8.5f)
{
	std::cout<<"Pelican::Pelican()\n";
	angle=0;
	pitch=0;
	radius=0;
	isAlive = true;
	tex1 = loadTexture("textures/metal6.bmp");
	tex2 = loadTexture("textures/szyba.bmp");
	tex3 = loadTexture("textures/metal3.bmp");
	explosion = new Dust();
}

Pelican::Pelican(float* position):width(7.0f),height(1.5f),length(8.5f),angle(0),pitch(0),radius(0)
{
	std::cout<<"Pelican::Pelican()\n";
	isAlive = true;
	tex1 = loadTexture("textures/metal6.bmp");
	tex2 = loadTexture("textures/szyba.bmp");
	tex3 = loadTexture("textures/metal3.bmp");
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	explosion = new Dust();
}

Pelican::~Pelican() 
{
	std::cout<<"Pelican::~Pelican()\n";
}

//drawing pelican dropship
void Pelican::drawPelican()
{
	if(isAlive){
		glPushMatrix();
			glTranslatef(position[0],position[1],position[2]);
			glRotatef(angle, 0, 0, 1);
			glRotatef(pitch, 1, 0, 0);
			//glTranslatef(0,radius,0);
			glScalef(0.5f,0.5f,0.5f);
			glRotatef(180, 0, 1, 0);
			//glRotatef(90, 1, 0, 0);
			GLfloat diff[] = {1.0, 1.0, 1.0, 1.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
			glDisable(GL_CULL_FACE);
		

			//======================== COCKPIT ===========================
			//cockpit - front
			glBindTexture(GL_TEXTURE_2D, tex1);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);		glVertex3f(	 1.0f, -3.0f,	0.0f);
				glTexCoord2f(1,1);		glVertex3f(	-1.0f, -3.0f,	0.0f);
				glTexCoord2f(1,0);		glVertex3f(	-1.0f, -2.0f,	0.0f);
				glTexCoord2f(0,1);		glVertex3f(	 1.0f, -2.0f,	0.0f);
			glEnd();

			//cockpit - windscreen
			glBindTexture(GL_TEXTURE_2D, tex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);		glVertex3f(	 1.0f, -2.0f,	0.0f);
				glTexCoord2f(1,1);		glVertex3f(	-1.0f, -2.0f,	0.0f);
				glTexCoord2f(1,0);		glVertex3f(	-2.0f,	0.0f,	3.0f);
				glTexCoord2f(0,1);		glVertex3f(	 2.0f,	0.0f,	3.0f);
			glEnd();

			//cockpit sides - left
			glBindTexture(GL_TEXTURE_2D, tex1);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);		glVertex3f( -1.0f, -2.0f, 0.0f);
				glTexCoord2f(0,1);		glVertex3f( -1.0f, -3.0f, 0.0f);
				glTexCoord2f(1,1);		glVertex3f( -2.0f, -3.0f, 3.0f);
				glTexCoord2f(1,0);		glVertex3f( -2.0f,  0.0f, 3.0f);
			glEnd();

			//cockpit sides - right
			glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
				glTexCoord2f(0,0);		glVertex3f(  1.0f, -2.0f, 0.0f);
				glTexCoord2f(0,1);		glVertex3f(  2.0f,  0.0f, 3.0f);
				glTexCoord2f(1,1);		glVertex3f(  2.0f, -3.0f, 3.0f);
				glTexCoord2f(1,0);		glVertex3f(  1.0f, -3.0f, 0.0f);
			glEnd();

			//cockpit - bottom
			glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);
				glTexCoord2f(0,0);		glVertex3f(  2.0f,  0.0f, 4.0f);
				glTexCoord2f(1,1);		glVertex3f( -2.0f,  0.0f, 4.0f);
				glTexCoord2f(1,0);		glVertex3f( -2.0f, -3.0f, 4.0f);
				glTexCoord2f(0,1);		glVertex3f(  2.0f, -3.0f, 4.0f);
			glEnd();

			//========================== HULL =============================
			//hull - top
			glBindTexture(GL_TEXTURE_2D, tex1);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUAD_STRIP);
				glTexCoord2f( 1,0);		glVertex3f(	 3.0f,	0.0f,	3.0f);
				glTexCoord2f(-1,0);		glVertex3f(	-3.0f,	0.0f,	3.0f);
				glTexCoord2f(0,-1);		glVertex3f(	 3.0f,	0.0f,	8.0f);
				glTexCoord2f( 0,1);		glVertex3f(	-3.0f,	0.0f,	8.0f);
				glTexCoord2f( 1,1);		glVertex3f(	 2.0f,	0.0f,	10.0f);
				glTexCoord2f( 0,0);		glVertex3f(	-2.0f,	0.0f,	10.0f);
				glTexCoord2f( 1,0);		glVertex3f(	 2.0f,	0.0f,	12.0f);
				glTexCoord2f( 0,1);		glVertex3f(	-2.0f,	0.0f,	12.0f);
				glTexCoord2f( 0,0);		glVertex3f(	 3.0f,	0.0f,	13.0f);
				glTexCoord2f( 1,1);		glVertex3f(	-3.0f,	0.0f,	13.0f);
				glTexCoord2f( 0,1);		glVertex3f(	 3.0f,	0.0f,	15.0f);
				glTexCoord2f( 1,0);		glVertex3f(	-3.0f,	0.0f,	15.0f);
				glTexCoord2f( 1,1);		glVertex3f(	 1.5f,	0.0f,	15.0f);
				glTexCoord2f( 0,0);		glVertex3f(	-1.5f,	0.0f,	15.0f);
				glTexCoord2f( 0,1);		glVertex3f(	 1.0f,	0.0f,	17.0f);
				glTexCoord2f( 1,0);		glVertex3f(	-1.0f,	0.0f,	17.0f);
			glEnd();

			//sides - left
			glBegin(GL_QUAD_STRIP);
			glNormal3f(1,0,0);
				glTexCoord2f( 1,0);		glVertex3f(	-2.0f,	 0.0f,	3.0f);
				glTexCoord2f( 0,1);		glVertex3f(	-2.0f,	-3.0f,	3.0f);
				glTexCoord2f( 0,0);		glVertex3f(	-2.0f,	 0.0f,	6.0f);
				glTexCoord2f( 1,1);		glVertex3f(	-2.0f,	-3.0f,	6.0f);
				glTexCoord2f( 0,1);		glVertex3f(	-2.0f,	0.0f,	6.0f);
				glTexCoord2f( 1,0);		glVertex3f(	-2.0f,	-2.0f,	6.0f);
				glTexCoord2f( 1,1);		glVertex3f(	-2.0f,	0.0f,	12.0f);
				glTexCoord2f( 0,0);		glVertex3f(	-2.0f,	-0.5f,	12.0f);
				glTexCoord2f( 0,1);		glVertex3f(	-1.0f,	0.0f,	17.0f);
				glTexCoord2f( 1,0);		glVertex3f(	-1.0f,	-0.5f,	17.0f);
			glEnd();

			//sides - right
			glBegin(GL_QUAD_STRIP);
			glNormal3f(-1,0,0);
				glTexCoord2f( 1,0);		glVertex3f(	2.0f,	-3.0f,	3.0f);
				glTexCoord2f( 0,1);		glVertex3f(	2.0f,	 0.0f,	3.0f);
				glTexCoord2f( 0,0);		glVertex3f(	2.0f,	-3.0f,	6.0f);
				glTexCoord2f( 1,1);		glVertex3f(	2.0f,	 0.0f,	6.0f);
				glTexCoord2f( 0,1);		glVertex3f(	2.0f,	-2.0f,	6.0f);
				glTexCoord2f( 1,0);		glVertex3f(	2.0f,	0.0f,	6.0f);
				glTexCoord2f( 1,1);		glVertex3f(	2.0f,	-0.5f,	12.0f);
				glTexCoord2f( 0,0);		glVertex3f(	2.0f,	0.0f,	12.0f);
				glTexCoord2f( 0,1);		glVertex3f(	1.0f,	-0.5f,	17.0f);
				glTexCoord2f( 1,0);		glVertex3f(	1.0f,	0.0f,	17.0f);
			glEnd();

			//back
			glBindTexture(GL_TEXTURE_2D, tex3);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f( 1,1);		glVertex3f( -1.0f, 0.0f, 17.0f);
				glTexCoord2f( 0,1);		glVertex3f( -1.0f, -0.5f, 17.0f);
				glTexCoord2f( 0,0);		glVertex3f(  1.0f, -0.5f, 17.0f);
				glTexCoord2f( 1,0);		glVertex3f(  1.0f, 0.0f, 17.0f);
			glEnd();

			//bottom
			glBindTexture(GL_TEXTURE_2D, tex1);
			glBegin(GL_QUAD_STRIP);
			glNormal3f(0.0f, -1.0f, 0.0f);
				glTexCoord2f(-1,0);		glVertex3f(  1.0f, -0.5f, 17.0f);
				glTexCoord2f( 1,0);		glVertex3f( -1.0f, -0.5f, 17.0f);
				glTexCoord2f( 0,1);		glVertex3f(  2.0f, -0.5f, 12.0f);
				glTexCoord2f( 0,-1);	glVertex3f( -2.0f, -0.5f, 12.0f);
				glTexCoord2f( 0,1);		glVertex3f(  2.0f, -0.5f,  3.0f);
				glTexCoord2f( 1,0);		glVertex3f( -2.0f, -0.5f,  3.0f);
			glEnd();

			glBegin(GL_QUAD_STRIP);
				glTexCoord2f(-1,0);		glVertex3f(  2.0f, -3.0f, 6.0f);
				glTexCoord2f( 1,0);		glVertex3f( -2.0f, -3.0f, 6.0f);
				glTexCoord2f( 0,1);		glVertex3f(  2.0f, -3.0f, 3.0f);
				glTexCoord2f( 0,-1);	glVertex3f( -2.0f, -3.0f, 3.0f);
				glTexCoord2f( 0,1);		glVertex3f(  1.0f, -3.0f, 0.0f);
				glTexCoord2f( 1,0);		glVertex3f( -1.0f, -3.0f, 0.0f);
			glEnd();

			//=========================== WINGS ============================
			//wings
			glBindTexture(GL_TEXTURE_2D, tex1);
			glBegin(GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f );
				glTexCoord2f(-1,0);		glVertex3f( -3.0f, 0.0f, 3.0f);
				glTexCoord2f( 1,0);		glVertex3f( -7.0f, 0.0f, 5.0f);
				glTexCoord2f( 0,1);		glVertex3f( -6.0f, 0.0f, 6.0f);
				glTexCoord2f( 0,-1);	glVertex3f( -4.0f, 0.0f, 6.0f);
				glTexCoord2f( 0,1);		glVertex3f( -4.0f, 0.0f, 8.0f);
				glTexCoord2f( 1,0);		glVertex3f( -3.0f, 0.0f, 8.0f);
			glEnd();
		
			glBegin(GL_POLYGON);
			glNormal3f(0,1,0);
				glTexCoord2f(-1,0);		glVertex3f( 3.0f, 0.0f, 3.0f);
				glTexCoord2f( 1,0);		glVertex3f( 3.0f, 0.0f, 8.0f);
				glTexCoord2f( 0,1);		glVertex3f( 4.0f, 0.0f, 8.0f);
				glTexCoord2f( 0,-1);	glVertex3f( 4.0f, 0.0f, 6.0f);
				glTexCoord2f( 0,1);		glVertex3f( 6.0f, 0.0f, 6.0f);
				glTexCoord2f( 1,0);		glVertex3f( 7.0f, 0.0f, 5.0f);
			glEnd();

						
			glBindTexture(GL_TEXTURE_2D, 0);
			glEnable(GL_CULL_FACE);
		
		glPopMatrix();
	}
}

//rotating pelican
void Pelican::rotatePelican(float k)
{
	//std::cout<<"kat= "<<angle<<"cos= "<<cosf(angle*3.1415/180)<<"sin= "<<sinf(angle*3.1415/180)<<std::endl;
	angle=angle+k;
	if (angle>30) angle=angle-k;
	if (angle<-30) angle=angle-k;

}

//pitching pelican
void Pelican::pitchPelican(float k)
{
	pitch = pitch + k;
	if ( pitch > 10) pitch = pitch - k;
	if ( pitch < -10 ) pitch = pitch - k;
}

//reseting pelican's orientation
void Pelican::resetPelican(){
	angle = 0;
	pitch = 0;
}

void Pelican::restartPelican(){
	resetPelican();
	isAlive = true;
}

void Pelican::blowPelican(Camera* camera){
	isAlive = false;
	resetPelican();
	explosion->drawDust(position[0],position[1]-height/2,position[2],camera,0,0);
}



float Pelican::getAngle(){	return angle; }

float Pelican::getPitch(){	return pitch; }

float* Pelican::getPosition(){ return position; }

float Pelican::getX(){ return position[0]; }

float Pelican::getY(){ return position[1]; }

float Pelican::getZ(){ return position[2]; }

float Pelican::getWidth(){ return width; }

float Pelican::getHeight(){ return height; }

float Pelican::getLength(){ return length; }
