//Controller.h
//...

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include "Model.h"
#include "View.h"


//States of the game
#define START	1
#define PAUSE	0
#define RESTART 2

//directions
#define UP		true
#define DOWN	false
#define LEFT	true
#define RIGHT	false

//Speed variables
#define PELICAN_PITCH_SPEED		1
#define PELICAN_ROTATION_SPEED	1
#define CAMERA_PITCH_SPEED		0.01f
#define CAMERA_YAW_SPEED		0.01f
#define CAMERA_ZOOM_SPEED		0.15f



class Controller {
private:
	Model* model;
	View* view;

public:
	//constructors and destructor
	Controller();
	Controller(View* view);
	Controller(Model* model, View* view);
	~Controller();

	//setters, getters and updaters
	Model* getModel();
	void setGameState(int);
	void pause();
	void togglePause();
	void updateFrameNo();
	void update();
	void restartGame();
	void cameraHandler();

	//moving ships and camera
	void pitchPelican(bool);
	void rotatePelican(bool);
	void pitchCamera(bool);
	void yawCamera(bool);
	void zoomCamera(bool);

	//collisions
	void checkCollisions();
	bool isPelicanCollision();
	bool isCameraCollision();
	bool isCollision(float* position);
};


#endif//CONTROLLER_H