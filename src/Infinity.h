//Infinity.h
//Declaration of the class representing Infinity vessel

#ifndef INFINITY_H
#define INFINITY_H

#include "DockingStation.h"
#include "Camera.h"
#include "Light.h"
#include "Dust.h"
#include "EngineBlast.h"

class Infinity {
	//ship's hull dimentions
	float height;		
	float width;	
	float length;

	//ship's armory dimentions
	float armoryWidth, armoryHeight, armoryLength;

	//ship's docking station dimentions
	float stationWidth, stationHeight, stationLength;

	float engineLength;
	GLUquadricObj* plasma;
	float thrust;
	Light* engineTopLight;
	Light* engineBottomLight;

	//ship's position
	float position[3];
	float startPosition[3];
	float armoryPosition[3];
	float stationPosition[3];
	float engineLightPosition[4];
	float engineLightAmbient[4];
	float engineLightDiffuse[4];
	float engineLightSpecular[4];
	float engineLightDirection[3];
	float engineLightCutoff[1];


	//textures
	GLuint tex1;	//Vessel's texture
	GLuint tex2;	//Widescreen's texture
	GLuint tex3;	//Engine's texture

	DockingStation* dockingStation;
	Dust* blast;
	EngineBlast* blast1;
	EngineBlast* blast2;

public:
	//constructors and destructor
	Infinity();
	Infinity(float* position);
	~Infinity();

	//drawing and moving
	void drawInfinity(int);
	void drawHull();
	void drawArmoryLeft();
	void drawArmoryRight();
	void drawStationLeft();
	void drawStationRight();
	void drawEngines(int);
	void moveInfinity(float, float);
	void update(int);
	void setPosition(float*);
	void drawBlast(Camera*);
	void drawEngineBlasts(Camera*);

	//getters
	float getWidth();
	float getHeight();
	float getLength();
	float* getPosition();
	float getX();
	float getY();
	float getZ();
	float* getArmoryLeftPosition();
	float* getArmoryRightPosition();
	float getArmoryWidth();
	float getArmoryHeight();
	float getArmoryLength();
	float* getStationLeftPosition();
	float* getStationRightPosition();
	float getStationWidth();
	float getStationHeight();
	float getStationLength();
	float getEngineLength();
};

#endif//INFINITY_H