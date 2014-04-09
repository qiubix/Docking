//Pelican.h
//Declaration of the class representing Pelican dropship

#ifndef PELICAN_H
#define PELICAN_H

//#include <GL/GLUT.H>
#include "GLUT.H"
#include "Dust.h"
#include "Camera.h"

class Pelican {
	//ship's dimentions
	float width;	
	float height;		
	float length;

	//ship's position
	float position[3];

	//explosion animation
	Dust* explosion;

	//is the ship still alive?
	bool isAlive;

	//textures
	GLuint tex1;	//tekstura statku
	GLuint tex2;	//szyby kabiny
	GLuint tex3;	//wydechu

public:
	float angle;
	float pitch;
	float radius;

public:
	//constructors and destructor
	Pelican();
	Pelican(float* position);
	~Pelican();

	//drawing and moving
	void drawPelican();
	void rotatePelican(float);	                
	void pitchPelican(float);	                
	void resetPelican();
	void restartPelican();
	void blowPelican(Camera* camera);

	//getters
	float* getPosition();
	float getX();
	float getY();
	float getZ();
	float getAngle();
	float getPitch();
	float getWidth();
	float getHeight();
	float getLength();
};

#endif//PELICAN_H