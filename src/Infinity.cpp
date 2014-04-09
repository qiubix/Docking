//Infinity.cpp
//Implementation of methods of the class Infinity

#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
#include "GLUT.H"
#include <iostream>
#include <math.h>
#include <limits>
#include "Infinity.h"
#include "ImageLoader.h"
#include "Materials.h"


#define SPEED 0.2


Infinity::Infinity(): width(20.0f),height(40.0f),length(200.0f),armoryWidth(5.0f),armoryHeight(10.0f),armoryLength(160.0f)
{
	std::cout<<"Infinity::Infinity()\n";
	tex1 = loadTexture("textures/hull1.bmp");
	tex2 = loadTexture("textures/metal5.bmp");
	tex3 = loadTexture("textures/wydech.bmp");
	float dockingStationPosition[3] = { 
		this->position[0]-width/2-5,
		this->position[1]+height/4+2,
		this->position[2] 
	};
	dockingStation = new DockingStation(this->position);
	stationWidth = dockingStation->getWidth();
	stationHeight = dockingStation->getHeight();
	stationLength = dockingStation->getLength();
	engineLength = 10.0f;
	plasma = gluNewQuadric();
	thrust = 20;
	//blast = new Dust();
}



Infinity::Infinity(float* position): width(20.0f),height(40.0f),length(200.0f),armoryWidth(5.0f),armoryHeight(10.0f),armoryLength(160.0f)
{
	std::cout << "Infinity::Infinity()\n";

	tex1 = loadTexture("textures/hull1.bmp");
	tex2 = loadTexture("textures/metal5.bmp");
	tex3 = loadTexture("textures/wydech.bmp");


	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	this->startPosition[0] = position[0];
	this->startPosition[1] = position[1];
	this->startPosition[2] = position[2];
	

	float dockingStationPosition[3] = { 
		this->position[0]-width/2-5,
		this->position[1]+height/2+2,
		this->position[2] 
	};
	dockingStation = new DockingStation(dockingStationPosition);
	stationWidth = dockingStation->getWidth();
	stationHeight = dockingStation->getHeight();
	stationLength = dockingStation->getLength();

	engineLength = 10.0f;
	plasma = gluNewQuadric();
	thrust = 20;

	engineLightPosition[0] = this->position[0];
	engineLightPosition[1] = this->position[1]+height/2;
	engineLightPosition[2] = this->position[2]-length/2-engineLength/2-20;
	engineLightPosition[3] = 1;
	engineLightAmbient[0]  = 0.0;
	engineLightAmbient[1]  = 0.0;
	engineLightAmbient[2]  = 0.0;
	engineLightAmbient[3]  = 1;
	engineLightDiffuse[0]  = 0.9;
	engineLightDiffuse[1]  = 0.9;
	engineLightDiffuse[2]  = 0.9;
	engineLightDiffuse[3]  = 1;
	engineLightSpecular[0] = 0;
	engineLightSpecular[1] = 0;
	engineLightSpecular[2] = 0;
	engineLightSpecular[3] = 0;

	engineTopLight = new Light(engineLightPosition,engineLightAmbient, engineLightDiffuse, engineLightSpecular, GL_LIGHT2);
	engineLightPosition[1] = this->position[1]-height/2;
	engineBottomLight = new Light(engineLightPosition,engineLightAmbient, engineLightDiffuse, engineLightSpecular, GL_LIGHT3);
	
	engineLightDirection[0] = 0;
	engineLightDirection[1] = 0;
	engineLightDirection[2] = -1;
	engineLightCutoff[0] = 20;

	//engineTopLight->setBoudaries(engineLightDirection,engineLightCutoff,GL_LIGHT2);

	//engineBottomLight->setBoudaries(engineLightDirection,engineLightCutoff,GL_LIGHT3);


}

Infinity::~Infinity() 
{
	std::cout<<"Infinity::~Infinity()\n";
	//TODO - destructors

}

void Infinity::drawInfinity(int frame_no)
{
	//position[2] = position[2] -((float) frame_no)*SPEED;
	GLfloat diff[] = {1.0, 1.0, 1.0, 1.0};
	//float armoryWidth = width/4;
	glPushMatrix();
	//glTranslatef(0,0,-((float) frame_no)*SPEED);
	glTranslatef(position[0],position[1],position[2]);
	//position[2] = position[2] -((float) frame_no)*SPEED;
	
		//=============================== HULL ======================================
		//Main body

		glPushMatrix();
			metalMaterial();
			glEnable(GL_TEXTURE_2D);
			//glDisable(GL_DEPTH_TEST);
			//glDisable(GL_LIGHTING);
			//glDisable(GL_BLEND);
 
			drawHull();
	
			//glEnable(GL_DEPTH_TEST);
		glPopMatrix();


		//======================= Side panels - right ====================
		//DOCKING STATION
		glPushMatrix();
			glTranslatef(-15,12,0);
			drawStationRight();
		glPopMatrix();

		//bottom - ARMORY
		glPushMatrix();
			glTranslatef(-(width/2+armoryWidth/2),-10,0);
			drawArmoryRight();
		glPopMatrix();
		
		//======================= Side panels - left =====================
		
		//top - DOCKING STATION
		glPushMatrix();
			glTranslatef(15,12,0);
			drawStationLeft();
		glPopMatrix();

		//bottom - ARMORY
		glPushMatrix();
			glTranslatef((width/2+armoryWidth/2),-10,0);
			drawArmoryLeft();
		glPopMatrix();
		


		//================================= ENGINES ==================================
		
		drawEngines(frame_no);
		engineTopLight->changeDiffuse(frame_no);
		engineBottomLight->changeDiffuse(frame_no);

		//=================================== BRIDGE ===================================
		glPushMatrix();
			glTranslatef(0, 15, -50);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_GEN_S);
			glBindTexture(GL_TEXTURE_2D, tex2);
			glutSolidSphere(10,12,12);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();

}


void Infinity::drawHull(){

	//Front
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 1); glVertex3f( -width/2,  height/2, -length/2 );
		glTexCoord2f(1, 1); glVertex3f(  width/2,  height/2, -length/2 );
		glTexCoord2f(1, 0); glVertex3f(  width/2, -height/2, -length/2 );
		glTexCoord2f(0, 0); glVertex3f( -width/2, -height/2, -length/2 );
	glEnd();
	//Back
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 1); glVertex3f(  width/2,  height/2, length/2 );
		glTexCoord2f(1, 1); glVertex3f( -width/2,  height/2, length/2 );
		glTexCoord2f(1, 0); glVertex3f( -width/2, -height/2, length/2 );
		glTexCoord2f(0, 0); glVertex3f(  width/2, -height/2, length/2 );
	glEnd();
	//Right
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( -width/2,  height/2,  length/2 );
		glTexCoord2f(5, 1); glVertex3f( -width/2,  height/2, -length/2 );
		glTexCoord2f(5, 0); glVertex3f( -width/2, -height/2, -length/2 );
		glTexCoord2f(0, 0); glVertex3f( -width/2, -height/2,  length/2 );
	glEnd();
	//Left
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( width/2,  height/2, -length/2 );
		glTexCoord2f(5, 1); glVertex3f( width/2,  height/2,  length/2 );
		glTexCoord2f(5, 0); glVertex3f( width/2, -height/2,  length/2 );
		glTexCoord2f(0, 0); glVertex3f( width/2, -height/2, -length/2 );
	glEnd();
	//Top
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 10); glVertex3f( -width/2, height/2,  length/2 );
		glTexCoord2f(1, 10); glVertex3f(  width/2, height/2,  length/2 );
		glTexCoord2f(1, 0); glVertex3f(  width/2, height/2, -length/2 );
		glTexCoord2f(0, 0); glVertex3f( -width/2, height/2, -length/2 );
	glEnd();
	//Bottom
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 10); glVertex3f( -width/2, -height/2, -length/2 );
		glTexCoord2f(1, 10); glVertex3f(  width/2, -height/2, -length/2 );
		glTexCoord2f(1, 0);  glVertex3f(  width/2, -height/2,  length/2 );
		glTexCoord2f(0, 0);  glVertex3f( -width/2, -height/2,  length/2 );
	glEnd();

}

void Infinity::drawArmoryLeft(){

	//Front
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 2); glVertex3f( -armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 2); glVertex3f(  armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 0); glVertex3f(  armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Back
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 2); glVertex3f(  armoryWidth/2,  armoryHeight/2, armoryLength/2 );
		glTexCoord2f(1, 2); glVertex3f( -armoryWidth/2,  armoryHeight/2, armoryLength/2 );
		glTexCoord2f(1, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f(  armoryWidth/2, -armoryHeight/2, armoryLength/2 );
	glEnd();
	//Right
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( -armoryWidth/2,  armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(16, 1); glVertex3f( -armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(16, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
	glEnd();
	//Left
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(16, 1); glVertex3f( armoryWidth/2,  armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(16, 0); glVertex3f( armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Top
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 32); glVertex3f( -armoryWidth/2, armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(1, 32); glVertex3f(  armoryWidth/2, armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  armoryWidth/2, armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -armoryWidth/2, armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Bottom
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 32); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 32); glVertex3f(  armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
	glEnd();

}

void Infinity::drawArmoryRight(){
	//Front
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 2); glVertex3f( -armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 2); glVertex3f(  armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 0); glVertex3f(  armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Back
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 2); glVertex3f(  armoryWidth/2,  armoryHeight/2, armoryLength/2 );
		glTexCoord2f(1, 2); glVertex3f( -armoryWidth/2,  armoryHeight/2, armoryLength/2 );
		glTexCoord2f(1, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f(  armoryWidth/2, -armoryHeight/2, armoryLength/2 );
	glEnd();
	//Right
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( -armoryWidth/2,  armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(16, 1); glVertex3f( -armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(16, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( -armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
	glEnd();
	//Left
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1); glVertex3f( armoryWidth/2,  armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(16, 1); glVertex3f( armoryWidth/2,  armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(16, 0); glVertex3f( armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(0, 0); glVertex3f( armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Top
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 32); glVertex3f( -armoryWidth/2, armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(1, 32); glVertex3f(  armoryWidth/2, armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  armoryWidth/2, armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -armoryWidth/2, armoryHeight/2, -armoryLength/2 );
	glEnd();
	//Bottom
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 32); glVertex3f( -armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 32); glVertex3f(  armoryWidth/2, -armoryHeight/2, -armoryLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -armoryWidth/2, -armoryHeight/2,  armoryLength/2 );
	glEnd();
}

void Infinity::drawStationLeft(){

	//Front
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 1); glVertex3f( -stationWidth/2,  stationHeight/2, -stationLength/2 );
		glTexCoord2f(1, 1); glVertex3f(  stationWidth/2,  stationHeight/2, -stationLength/2 );
		glTexCoord2f(1, 0); glVertex3f(  stationWidth/2, -stationHeight/2, -stationLength/2 );
		glTexCoord2f(0, 0); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
	glEnd();
	//Back
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 1); glVertex3f(  stationWidth/2,  stationHeight/2, stationLength/2 );
		glTexCoord2f(1, 1); glVertex3f( -stationWidth/2,  stationHeight/2, stationLength/2 );
		glTexCoord2f(1, 0); glVertex3f( -stationWidth/2, -stationHeight/2, stationLength/2 );
		glTexCoord2f(0, 0); glVertex3f(  stationWidth/2, -stationHeight/2, stationLength/2 );
	glEnd();
	//Right
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 1);  glVertex3f( -stationWidth/2,  stationHeight/2,  stationLength/2 );
		glTexCoord2f(16, 1); glVertex3f( -stationWidth/2,  stationHeight/2, -stationLength/2 );
		glTexCoord2f(16, 0); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, -stationHeight/2,  stationLength/2 );
	glEnd();
	//Left
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1);  glVertex3f( stationWidth/2,  stationHeight/2, -stationLength/2 );
		glTexCoord2f(16, 1); glVertex3f( stationWidth/2,  stationHeight/2,  stationLength/2 );
		glTexCoord2f(16, 0); glVertex3f( stationWidth/2, -stationHeight/2,  stationLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( stationWidth/2, -stationHeight/2, -stationLength/2 );
	glEnd();
	//Top
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 16); glVertex3f( -stationWidth/2, stationHeight/2,  stationLength/2 );
		glTexCoord2f(1, 16); glVertex3f(  stationWidth/2, stationHeight/2,  stationLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  stationWidth/2, stationHeight/2, -stationLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, stationHeight/2, -stationLength/2 );
	glEnd();
	//Bottom
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 16); glVertex3f( -stationWidth/2, -stationHeight/2, -stationLength/2 );
		glTexCoord2f(1, 16); glVertex3f(  stationWidth/2, -stationHeight/2, -stationLength/2 );
		glTexCoord2f(1, 0);  glVertex3f(  stationWidth/2, -stationHeight/2,  stationLength/2 );
		glTexCoord2f(0, 0);  glVertex3f( -stationWidth/2, -stationHeight/2,  stationLength/2 );
	glEnd();



}

void Infinity::drawStationRight(){
	
	dockingStation->drawDockingStation();

}

void Infinity::drawEngines(int frame_no){
	GLfloat diff[] = {1.0, 1.0, 1.0, 1.0};


		//Bottom engine
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
			glColor3f(0.8, 0.2, 0.1); 
			glDisable(GL_CULL_FACE);
			glTranslatef(0,-10,-110);
			glutSolidCone(10.0,20.0,12,12);
		glPopMatrix();
		
		//Top engine
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
			glColor3f(0.8, 0.2, 0.1); 
			glDisable(GL_CULL_FACE);
			glTranslatef(0, 10,-110);
			glutSolidCone(10.0,20.0,12,12);
		glPopMatrix();

		glCullFace(GL_FRONT);
		//Plasma blast - top engine
		glPushMatrix();
			glTranslatef(0,height/4,-length/2-engineLength/2);
			glRotatef(180,1,0,0);	
			//glDisable(GL_CULL_FACE);
			glEnable(GL_EMISSION);
			plasmaMaterial(frame_no);
			gluCylinder(plasma,7,0,thrust,12,1);
			glDisable(GL_EMISSION);
		glPopMatrix();

		
		//Plasma blast - bottom engine
		glPushMatrix();
			glTranslatef(0,-height/4,-length/2-engineLength/2);
			glRotatef(180,1,0,0);	
			//glDisable(GL_CULL_FACE);
			glEnable(GL_EMISSION);
			plasmaMaterial(frame_no);
			gluCylinder(plasma,7,0,thrust,12,1);
			glDisable(GL_EMISSION);
		glPopMatrix();


		glCullFace(GL_BACK);
		//Plasma blast - top engine
		glPushMatrix();
			glTranslatef(0,height/4,-length/2-engineLength/2);
			glRotatef(180,1,0,0);	
			//glEnable(GL_CULL_FACE);
			glEnable(GL_EMISSION);
			plasmaMaterial(frame_no);
			gluCylinder(plasma,7,0,thrust,12,1);
			glDisable(GL_EMISSION);
		glPopMatrix();

		//Plasma blast - bottom engine
		glPushMatrix();
			glTranslatef(0,-height/4,-length/2-engineLength/2);
			glRotatef(180,1,0,0);	
			//glEnable(GL_CULL_FACE);
			glEnable(GL_EMISSION);
			plasmaMaterial(frame_no);
			gluCylinder(plasma,7,0,thrust,12,1);
			glDisable(GL_EMISSION);
		glPopMatrix();

}


void Infinity::moveInfinity(float horizontal, float vertical)
{
	position[0] = position[0] + horizontal/100;
	position[1] = position[1] + vertical/50;
}

void Infinity::update(int frame_no){
	position[2] = startPosition[2] -((float) frame_no)*SPEED;
	engineTopLight->getPosition()[2] = startPosition[2] -((float) frame_no)*SPEED;
	engineBottomLight->getPosition()[2] = startPosition[2] -((float) frame_no)*SPEED;
	engineTopLight->updatePosition();
	engineBottomLight->updatePosition();

	//position[2] = position[2];
	//std::cout << "position[2] = " << position[2] << "\n";
}

void Infinity::setPosition(float* position){
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
}

void Infinity::drawBlast(Camera* camera){
	blast->drawDust(position[0]-10,position[1]-height/2-10,position[2]-length,camera,60,20);
}

void Infinity::drawEngineBlasts(Camera* camera){
	blast1->drawBlast(position[0],position[1]+height/4,position[2]-length/2-5,camera,0,0);

	blast2->drawBlast(position[0],position[1]-height/4,position[2]-length/2-5,camera,0,0);

}


float Infinity::getWidth(){ return width; }

float Infinity::getHeight(){ return height; }

float Infinity::getLength(){ return length; }

float* Infinity::getPosition(){ return position; }

float Infinity::getX(){ return position[0]; }

float Infinity::getY(){ return position[1]; }

float Infinity::getZ(){ return position[2]; }

float* Infinity::getArmoryLeftPosition(){
	armoryPosition[0] =	position[0] + width/2 + armoryWidth/2; 
	armoryPosition[1] =	position[1] - height/4; 
	armoryPosition[2] =	position[2];
	return armoryPosition;
}

float* Infinity::getArmoryRightPosition(){
	armoryPosition[0] =	position[0] - width/2 - armoryWidth/2; 
	armoryPosition[1] =	position[1] - height/4; 
	armoryPosition[2] =	position[2];
	return armoryPosition;
}

float Infinity::getArmoryWidth(){ return armoryWidth; }

float Infinity::getArmoryHeight(){ return armoryHeight; }

float Infinity::getArmoryLength(){ return armoryLength; }


float* Infinity::getStationLeftPosition(){
	stationPosition[0] =	position[0] + width/2 + stationWidth/2; 
	stationPosition[1] =	position[1] + height/4 + 2; 
	stationPosition[2] =	position[2];
	return stationPosition;
}

float* Infinity::getStationRightPosition(){
	stationPosition[0] =	position[0] - width/2 - stationWidth/2; 
	stationPosition[1] =	position[1] + height/4 + 2; 
	stationPosition[2] =	position[2];
	return stationPosition;
}

float  Infinity::getStationWidth(){ return stationWidth; }

float  Infinity::getStationHeight(){ return stationHeight; }

float  Infinity::getStationLength(){ return stationLength; }

float Infinity::getEngineLength(){ return engineLength; }