//Skybox.h
//Definition of class Skybox responsible for background.


#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <string>
#include "Camera.h"
//#include <GL/GLUT.H>
#include "GLUT.H"


class Skybox {
	float width;

	std::string file_[6];
	GLuint cube[6];

	Camera *camera;

public:
	Skybox();
	~Skybox();
	void drawSkybox(Camera* cam);

private:
	void loadAllTextures();
};

#endif