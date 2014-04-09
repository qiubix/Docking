#ifndef DUST_H
#define DUST_H

#include "Camera.h"
//#include <GL/GLUT.H>
#include "GLUT.H"

class Dust {

	// struktura particla jednego
	typedef struct {						// Create A Structure For Particle
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
		float size;
	} Particles;							// Particles Structure

	Particles *particle_; // bufor particli
	GLuint texture_;
	
	float	slowdown_;				// Slow Down Particles
	int maxParticles_;
	int active_;	// ile jest aktywnych

public:
	Dust();
	~Dust();
	void drawDust(float, float, float, Camera*, float, float);
	void reset();	// resetuje do poczatkowych ustawien pylek

private:
	//void drawBox(float, float, float);	// rysuje particla boxowego
};

#endif