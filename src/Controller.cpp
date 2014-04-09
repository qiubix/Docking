//Controller.cpp
//...

#include <iostream>
#include <Windows.h>
#include "Controller.h"

Controller::Controller(){
	std::cout << "Controller::Controller();\n";
	model = new Model();
}

Controller::Controller(View* view){
	std::cout << "Controller::Controller();\n";
	this->view = view;
	model = new Model();
}

Controller::Controller(Model* model, View* view){
	std::cout << "Controller::Controller();\n";
	this->model = model;
	this->view = view;
}

Controller::~Controller(){
	std::cout << "Controller::~Controller();\n";
}

Model* Controller::getModel(){
	return model;
}

//function setting mode of the game (START, PAUSE, RESTART)
void Controller::setGameState(int mode){
	model->setGameState(mode);
}

void Controller::pause(){
	setGameState(PAUSE);
}

void Controller::togglePause(){
	int GAME_STATE = model->getGameState();
	if(GAME_STATE == PAUSE) setGameState(START);
	else setGameState(PAUSE);
}

void Controller::updateFrameNo(){
	if(model->getGameState() == START) model->increaseFrameNo();
	if(model->getGameState() == PAUSE) return; //model->setFrameNo(0);
	if(model->getGameState() == RESTART) model->setFrameNo(0);
}

void Controller::update(){
	updateFrameNo();
	model->getInfinity()->moveInfinity(model->getPelican()->getAngle(),model->getPelican()->getPitch());
	model->getInfinity()->update(model->getFrameNo());
	checkCollisions();
	//model->getLight()->changeDiffuse(model->getFrameNo());
}

void Controller::restartGame(){
	model->setGameState(RESTART);
	model->reset();
	model->getPelican()->restartPelican();
}

void Controller::cameraHandler(){
	if(GetKeyState('W') & 0x80) {
		pitchCamera(UP);
	}
	if(GetKeyState('S') & 0x80) {
		pitchCamera(DOWN);
	}
	if(GetKeyState('A') & 0x80) {		
		yawCamera(LEFT);
	}     
	if(GetKeyState('D') & 0x80) {
		yawCamera(RIGHT);
	}
	if(GetKeyState('Q') & 0x80) {
		zoomCamera(UP);
	}
	if(GetKeyState('E') & 0x80) {
		zoomCamera(DOWN);
	}
}



void Controller::pitchPelican(bool up){
	float pelicanPitchSpeed = PELICAN_PITCH_SPEED;
	if(up)
		model->getPelican()->pitchPelican(-pelicanPitchSpeed);
	else
		model->getPelican()->pitchPelican(pelicanPitchSpeed);
}

void Controller::rotatePelican(bool left){
	float pelicanRotationSpeed = PELICAN_ROTATION_SPEED;
	if(left)
		model->getPelican()->rotatePelican(-pelicanRotationSpeed);
	else
		model->getPelican()->rotatePelican(pelicanRotationSpeed);
}

void Controller::pitchCamera(bool up){
	float cameraPitchSpeed = CAMERA_PITCH_SPEED;
	if(up)
		model->getCamera()->Pitch(cameraPitchSpeed);
	else
		model->getCamera()->Pitch(-cameraPitchSpeed);
}

void Controller::yawCamera(bool left){
	float cameraYawSpeed = CAMERA_YAW_SPEED;
	if(left)
		model->getCamera()->Yaw(-cameraYawSpeed);
	else
		model->getCamera()->Yaw(cameraYawSpeed);
}

void Controller::zoomCamera(bool up){
	float cameraZoomSpeed = CAMERA_ZOOM_SPEED;
	if(up)
		model->getCamera()->Zoom(cameraZoomSpeed);
	else
		model->getCamera()->Zoom(-cameraZoomSpeed);
}







//checks all objects for collisions and react properly
void Controller::checkCollisions(){
	if(isPelicanCollision()){ 
		pause();
		//model->getPelican()->resetPelican();
		model->getPelican()->blowPelican(model->getCamera());
	}
}

//checks if pelican collides with infinity vessel
bool Controller::isPelicanCollision(){
	//========================= INFINITY ==================================
	//infinity's stern position
	float infinityStern = model->getInfinity()->getZ() - model->getInfinity()->getLength()/2 - model->getInfinity()->getEngineLength();
	//infinity's bows position
	float infinityBows = model->getInfinity()->getZ() + model->getInfinity()->getLength()/2;
	//infinity's hull left side position
	float infinityLeft = model->getInfinity()->getX() + model->getInfinity()->getWidth()/2;
	//infinity's hull right side position
	float infinityRight = model->getInfinity()->getX() - model->getInfinity()->getWidth()/2;
	//infinity's top position
	float infinityTop = model->getInfinity()->getY() + model->getInfinity()->getHeight()/2;
	//infinity's bottom position
	float infinityBottom = model->getInfinity()->getY() - model->getInfinity()->getHeight()/2;

	//infinity's left armory position - back
	float infinityLeftArmoryBack = model->getInfinity()->getArmoryLeftPosition()[2] - model->getInfinity()->getArmoryLength()/2;
	//infinity's left armory position - front
	float infinityLeftArmoryFront = model->getInfinity()->getArmoryLeftPosition()[2] + model->getInfinity()->getArmoryLength()/2;
	//infinity's left armory position - side
	float infinityLeftArmorySide = model->getInfinity()->getArmoryLeftPosition()[0] + model->getInfinity()->getArmoryWidth()/2;
	//infinity's left armory position - top
	float infinityLeftArmoryTop = model->getInfinity()->getArmoryLeftPosition()[1] + model->getInfinity()->getArmoryHeight()/2;
	//infinity's left armory position - bottom
	float infinityLeftArmoryBottom = model->getInfinity()->getArmoryLeftPosition()[1] - model->getInfinity()->getArmoryHeight()/2;

	//infinity's right armory position - back
	float infinityRightArmoryBack = model->getInfinity()->getArmoryRightPosition()[2] - model->getInfinity()->getArmoryLength()/2;
	//infinity's right armory position - front
	float infinityRightArmoryFront = model->getInfinity()->getArmoryRightPosition()[2] + model->getInfinity()->getArmoryLength()/2;
	//infinity's right armory position - side
	float infinityRightArmorySide = model->getInfinity()->getArmoryRightPosition()[0] - model->getInfinity()->getArmoryWidth()/2;
	//infinity's right armory position - top
	float infinityRightArmoryTop = model->getInfinity()->getArmoryRightPosition()[1] + model->getInfinity()->getArmoryHeight()/2;
	//infinity's right armory position - bottom
	float infinityRightArmoryBottom = model->getInfinity()->getArmoryRightPosition()[1] - model->getInfinity()->getArmoryHeight()/2;

	//infinity's left station position - back
	float infinityLeftStationBack = model->getInfinity()->getStationLeftPosition()[2] - model->getInfinity()->getStationLength()/2;
	//infinity's left station position - front
	float infinityLeftStationFront = model->getInfinity()->getStationLeftPosition()[2] + model->getInfinity()->getStationLength()/2;
	//infinity's left station position - side
	float infinityLeftStationSide = model->getInfinity()->getStationLeftPosition()[0] + model->getInfinity()->getStationWidth()/2;
	//infinity's left station position - top
	float infinityLeftStationTop = model->getInfinity()->getStationLeftPosition()[1] + model->getInfinity()->getStationHeight()/2;
	//infinity's left station position - bottom
	float infinityLeftStationBottom = model->getInfinity()->getStationLeftPosition()[1] - model->getInfinity()->getStationHeight()/2;

	//infinity's right station position - back
	float infinityRightStationBack = model->getInfinity()->getStationRightPosition()[2] - model->getInfinity()->getStationLength()/2;
	//infinity's right station position - front
	float infinityRightStationFront = model->getInfinity()->getStationRightPosition()[2] - model->getInfinity()->getStationLength()/2;
	//infinity's right station position - side
	float infinityRightStationSide = model->getInfinity()->getStationRightPosition()[0] - model->getInfinity()->getStationWidth()/2;
	//infinity's right station position - top
	float infinityRightStationTop = model->getInfinity()->getStationRightPosition()[1] + model->getInfinity()->getStationHeight()/2;
	//infinity's right station position - bottom
	float infinityRightStationBottom = model->getInfinity()->getStationRightPosition()[1] - model->getInfinity()->getStationHeight()/2;


	//========================= PELICAN ===================================
	//pelican's bows position
	float pelicanBows = model->getPelican()->getZ();
	//pelican's stern position
	float pelicanStern = model->getPelican()->getZ() - model->getPelican()->getLength();
	//pelican's left wing position
	float pelicanLeftWing = model->getPelican()->getX() + model->getPelican()->getWidth()/2;
	//pelican's right wing position
	float pelicanRightWing = model->getPelican()->getX() - model->getPelican()->getWidth()/2;
	//pelican's top position
	float pelicanTop = model->getPelican()->getY();
	//pelican's bottom position
	float pelicanBottom = model->getPelican()->getY() - model->getPelican()->getHeight();


	//std::cout << "infinity stern position = " << infinityStern << "\n";
	//std::cout << "pelican bows position = " << pelicanBows << "\n";



	//========================= COLLISIONS ====================================
	//collision with Infinity's hull
	if(infinityStern < pelicanBows && infinityBows > pelicanStern)									//Z
		if(infinityLeft > pelicanRightWing && infinityRight < pelicanLeftWing)						//X
			if(infinityBottom < pelicanTop && infinityTop > pelicanBottom)							//Y
				return true;

	//collision with left armory
	if(infinityLeftArmoryBack < pelicanBows && infinityLeftArmoryFront > pelicanStern)				//Z
		if(infinityLeftArmorySide > pelicanRightWing && infinityLeft < pelicanLeftWing)				//X
			if(infinityLeftArmoryBottom < pelicanTop && infinityLeftArmoryTop > pelicanBottom)		//Y
				return true;

	//collision with right armory
	if(infinityRightArmoryBack < pelicanBows && infinityRightArmoryFront > pelicanStern)			//Z
		if(infinityRightArmorySide < pelicanLeftWing && infinityRight > pelicanRightWing)			//X
			if(infinityRightArmoryBottom < pelicanTop && infinityRightArmoryTop > pelicanBottom)	//Y
				return true;

	//collision with left station
	if(infinityLeftStationBack < pelicanBows && infinityLeftStationFront > pelicanStern)			//Z
		if(infinityLeftStationSide > pelicanRightWing && infinityLeft < pelicanLeftWing)			//X
			if(infinityLeftStationBottom < pelicanTop && infinityLeftStationTop > pelicanBottom)	//Y
				return true;

	//collision with right station
	if(infinityRightStationBack < pelicanBows && infinityRightStationFront > pelicanStern)			//Z
		if(infinityRightStationSide < pelicanLeftWing && infinityRight > pelicanRightWing)			//X
			if(infinityRightStationBottom < pelicanTop && infinityRightStationTop > pelicanBottom)	//Y
				return true;

	//hurray!! nothing collided!!
	return false;
}

bool Controller::isCameraCollision(){

	return false;
}



//checks if there is collision beetween Infinity and object with given position
bool Controller::isCollision(float* position){

	return false;
}

