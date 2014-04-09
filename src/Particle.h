//Particle.h
//Defines class representing particle

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle{
	bool active;
	float life;
	float fade;
	float x,y,z;
	float xi,yi,zi;
	float xg,yg,zg;
	float size;
public:
	friend class EngineBlast;
	//Particle();
	//~Particle();
	void reset();
};

#endif//PARTICLE_H