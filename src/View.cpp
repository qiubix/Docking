//View.cpp
//...

#include <iostream>
#include "View.h"
#include "GLUT.H"
//#include <GL/GLUT.H>

View::View(){
	std::cout << "View::View();\n";
}

View::View(Model* model){
	std::cout << "View::View();\n";
	this->model = model;
}

View::~View(){
	std::cout << "View::~View();\n";
}

void View::drawAll(int frame_no){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, 200, 0.0, 200);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2i(10, 10);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//setting the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double) glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 10, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	model->getCamera()->GetViewMatrix();

	//drawing skybox
	model->getSkybox()->drawSkybox(model->getCamera());

	//drawing the Pelican dropship
	model->getPelican()->drawPelican();

	//frame_no++;
	model->getInfinity()->drawInfinity(model->getFrameNo());
}