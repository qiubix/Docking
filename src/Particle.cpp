//Particle.cpp
//...


#include <iostream>
#include "Particle.h"

//Particle::Particle(){
//	std::cout << "Particle::Particle()\n";
//}
//
//Particle::~Particle(){
//	std::cout << "Particle::~Particle()\n";
//}

void Particle::reset(){
	active=true;								// Make All The Particles Active
	life=3.0f;								// Give All The Particles Full Life
	fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
	x = 0;
	y = 0;
	z = 0;
	xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
	yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
	zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
	xg=0.0f;									// Set Horizontal Pull To Zero
	yg=0.00f;								// Set Vertical Pull Downward
	zg=0.0f;									// Set Pull On Z Axis To Zero
	size = 0.20f;
}