#include <windows.h>
//#include <GL/gl.h>
#include <iostream>
#include "glut.h"
#include "Light.h"


Light::Light()
	{
	std::cout<<"Light::Light()\n";

	number = GL_LIGHT0;

	position_[0] = -50;
	position_[1] = 50;
	position_[2] = 0;
	position_[3] = 1.0;
	ambient_[0] = 0.0;
	ambient_[1] = 0.0;
	ambient_[2] = 0.0;
	ambient_[3] = 1.0;
	diffuse_[0] = 0.0;
	diffuse_[1] = 1.0;
	diffuse_[2] = 0.0;
	diffuse_[3] = 1.0;
	specular_[0] = 0.0;
	specular_[1] = 0.0;
	specular_[2] = 0.0;
	specular_[3] = 1.0;

	mat_ambient_[0] = 1.0;
	mat_ambient_[1] = 1.0;
	mat_ambient_[2] = 1.0;
	mat_ambient_[3] = 1.0;
	mat_specular_[0] = 1.0;
	mat_specular_[1] = 1.0;
	mat_specular_[2] = 1.0;
	mat_specular_[3] = 1.0;

	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient_ );
	glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular_ );
	glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );

	glLightfv( GL_LIGHT0, GL_POSITION, position_ );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_ );
    
	glShadeModel( GL_SMOOTH );

	glEnable( GL_NORMALIZE );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	//glEnable( GL_LIGHT1 );
	//GLfloat diff[] = {0.0, 0.0, 0.0, 1.0};
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	//glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse_);
		
}

Light::Light(float* position, float* ambient, float* diffuse, float* specular, GLenum number){
	std::cout<<"Light::Light()\n";
	this->number = number;
	position_[0] = position[0];
	position_[1] = position[1];
	position_[2] = position[2];
	position_[3] = position[3];
	ambient_[0] = ambient[0];
	ambient_[1] = ambient[1];
	ambient_[2] = ambient[2];
	ambient_[3] = ambient[3];
	diffuse_[0] = diffuse[0];
	diffuse_[1] = diffuse[1];
	diffuse_[2] = diffuse[2];
	diffuse_[3] = diffuse[3];
	specular_[0] = specular[0];
	specular_[1] = specular[1];
	specular_[2] = specular[2];
	specular_[3] = specular[3];


	mat_ambient_[0] = 1.0;
	mat_ambient_[1] = 1.0;
	mat_ambient_[2] = 1.0;
	mat_ambient_[3] = 1.0;
	mat_specular_[0] = 1.0;
	mat_specular_[1] = 1.0;
	mat_specular_[2] = 1.0;
	mat_specular_[3] = 1.0;

	
	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient_ );
	glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular_ );
	glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );

	glLightfv( number, GL_POSITION, position_ );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_ );
    
	glShadeModel( GL_SMOOTH );

	glEnable( GL_NORMALIZE );
	glEnable( GL_LIGHTING );
	glEnable( number ); 
	

}


Light::~Light() {
	std::cout<<"Light::~Light()\n";
}

void Light::setPosition() {
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_); // intensywnosc
	//glLightfv(GL_LIGHT0, GL_POSITION, position_);

	glLightfv(number, GL_DIFFUSE, diffuse_); 
	glLightfv(number, GL_POSITION, position_);
}

void Light::updatePosition(){
	glLightfv(number, GL_POSITION, position_);
}

float* Light::getPosition(){
	return position_;
}


void Light::setBoudaries(float* direction, float* cutoff, GLenum number){
	glLightfv( number, GL_SPOT_DIRECTION, direction);
	glLightfv( number, GL_SPOT_CUTOFF, cutoff);
}


void Light::changeDiffuse(int frame_no){

	float min = 0.7;
	float zakres = (1 - min)/2;


	float dif = min+zakres + sin((float) frame_no*3.14f/30.0f)*zakres;

	diffuse_[0] = dif;
	diffuse_[1] = 0;
	diffuse_[2] = 0;

	glLightfv(number, GL_DIFFUSE, diffuse_);

}