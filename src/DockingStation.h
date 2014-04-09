//DockingStation.h
//Class representing docking station on the side of Infinity

#ifndef DOCKING_STATION_H
#define DOCKING_STATION_H

//#include <GL/GLUT.H>
#include "glut.h"

class DockingStation{
private:
	float position[3];
	float width, height, length;
	GLuint tex;

public:
	//constructors and destructor
	DockingStation(float* position);
	DockingStation(float width, float height, float length, float* position);
	~DockingStation();

	//getters
	float getWidth();
	float getHeight();
	float getLength();
	float* getPosition();

	//drawing
	void drawDockingStation();
};


#endif//DOCKING_STATION_H