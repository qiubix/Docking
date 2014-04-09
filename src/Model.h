//Model.h
//...

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Camera.h"
#include "Skybox.h"
#include "Pelican.h"
#include "Infinity.h"
//#include "Handle.h"
#include "Light.h"

class Model{
private:
	Camera* camera;
	Skybox* skybox;
	Pelican* pelican;
	Infinity* infinity;
	//std::vector<Handle*> handles;
	Light* light;
	int frame_no;
	int gameState;
public:
	//constructors and destructor
	Model();
	Model(Camera*, Pelican*, Infinity*, Light*);
	~Model();

	//getters of pointers to model objects 
	Camera* getCamera();
	Skybox* getSkybox();
	Pelican* getPelican();
	Infinity* getInfinity();
	Light* getLight();

	//frame number settings
	int getFrameNo();
	void increaseFrameNo();
	void setFrameNo(int);

	//Game state settings
	int getGameState();
	void setGameState(int);
	void reset();

	//getters of objects' positions
	float* getCameraPosition();
	float* getPelicanPosition();
	float* getInfinityPosition();
};

#endif//MODEL_H