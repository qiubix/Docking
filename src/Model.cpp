//Model.cpp
//...

#include <iostream>
#include <stdio.h>
#include "Model.h"

#define PELICAN_POSITION {0,0,5}
#define INFINITY_POSITION {20,20,200}

//class default constructor
Model::Model():frame_no(0),gameState(0){
	std::cout << "Model::Model()\n";
	float pelicanPosition[3] = {0,0,5};
	float infinityPosition[3] = {20,20,200};
	camera = new Camera(0,3,-25);
	skybox = new Skybox();
	pelican = new Pelican(pelicanPosition);
	infinity = new Infinity(infinityPosition);
	light = new Light();
	light->setPosition();
}

//class constructor, takes objects pointers
Model::Model(Camera* camera, Pelican* pelican, Infinity* infinity, Light* light){
	std::cout << "Model::Model()\n";
	this->camera = camera;
	this->pelican = pelican;
	this->infinity = infinity;
	this->light = light;
}


//class destructor
Model::~Model(){
	std::cout << "Model::~Model()\n";
	delete light;
	delete infinity;
	delete pelican;
	delete skybox;
	delete camera;
}

Camera* Model::getCamera() {	return camera; }

Skybox* Model::getSkybox() {	return skybox; }

Pelican* Model::getPelican() {	return pelican;	}

Infinity* Model::getInfinity(){	return infinity;}

Light* Model::getLight() {		return light;	}

int Model::getFrameNo() {		return frame_no;}

void Model::increaseFrameNo(){	frame_no++; }

void Model::setFrameNo(int frame_no){ this->frame_no = frame_no; }

int Model::getGameState(){		return gameState;}

void Model::setGameState(int gameState){ this->gameState = gameState; }

void Model::reset(){
	float newInfinityPosition[3] = INFINITY_POSITION;
	this->infinity->setPosition(newInfinityPosition);
}

float* Model::getCameraPosition(){		return camera->m_position;	}

float* Model::getPelicanPosition(){		return pelican->getPosition();	}

float* Model::getInfinityPosition(){	return infinity->getPosition();	}

