#ifndef LIGHT_H
#define LIGHT_H

class Light {
	GLfloat position_[4];
	GLfloat ambient_[4];
	GLfloat diffuse_[4];
	GLfloat specular_[4];
	GLenum number;

	GLfloat mat_ambient_[4];
	GLfloat mat_specular_[4];
	
public:
	Light();
	Light(float* position,float* ambient,float* diffuse,float* specular, GLenum number);
	~Light();
	void setPosition();
	float* getPosition();
	void updatePosition();
	void setPosition(float*, float*);
	void setBoudaries(float* direction, float* cutoff, GLenum number);
	void changeDiffuse(int);
};

#endif	