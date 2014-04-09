//EngineBlast.h
//...

#ifndef ENGINE_BLAST_H
#define ENGINE_BLAST_H

#include "Particle.h"
#include "Camera.h"
//#include <GL/GL.h>
//#include <GL/GLUT.H>
#include "GLUT.H"

class EngineBlast{

	Particle* particle_;
	GLuint texture_;
	Camera* camera;
	
	float	slowdown_;				// Slow Down Particles
	int maxParticles_;
	int active_;	

public:
	EngineBlast();
	~EngineBlast();
	void drawBlast(float,float,float,Camera*,float,float);
	void reset();
	void setCamera(Camera* camera);
};


#endif//ENGINE_BLAST_H