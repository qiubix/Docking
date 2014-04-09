//EngineBlast.cpp
//...

//#include <GL/GLUT.H>
#include "GLUT.H"
#include "EngineBlast.h"
#include "ImageLoader.h"
#include <iostream>

EngineBlast::EngineBlast(): slowdown_(40), maxParticles_(1000), active_(maxParticles_) {
	std::cout<<"EngineBlast::EngineBlast()\n";

	particle_ = new Particle[maxParticles_];

	texture_ = loadTexture("textures/particle.bmp");

	reset();
}

EngineBlast::~EngineBlast() {
	std::cout<<"EngineBlast::~EngineBlast()\n";
	
	delete particle_;
}

void EngineBlast::drawBlast(float xx, float yy, float zz, Camera* cam, float kat, float promien) {
	// no active particles - end
	if (active_ == 0)
		return;

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D,texture_);			// Select Our Texture
	glDisable(GL_CULL_FACE);							
	glEnable(GL_ALPHA_TEST);							

	glPushMatrix();
	glTranslatef(xx, yy, zz-0.5);
	glDepthMask(GL_FALSE) ;
	glRotatef(kat, 0, 0, 1);
	glTranslatef(0,promien,0);
	//glRotatef(90, 1, 0, 0);
	
	// drawing dust
	for (int loop = 0; loop < maxParticles_; loop++)					// lop Through All The Particles
	{
		if (particle_[loop].active)							// If The Particle Is Active
		{
			float x=particle_[loop].x;						// Grab Our Particle X Position
			float y=particle_[loop].y;						// Grab Our Particle Y Position
			float z=particle_[loop].z;					// Particle Z Pos

			float r[3],u[3];
			r[0]=cam->viewMatrix[0];
			r[1]=cam->viewMatrix[4];
			r[2]=cam->viewMatrix[8];
        	u[0]=cam->viewMatrix[1];
			u[1]=cam->viewMatrix[5];
			u[2]=cam->viewMatrix[9];

        	glPushMatrix();
				glTranslatef(x, (y < 0 ? -y : y), z);
				
				// draw particle
				glBegin(GL_QUADS);
					glNormal3f(0,1,0);
					glTexCoord2f(1,	1);
					glVertex3f((r[0]+u[0])*(particle_[loop].size),(r[1]+u[1])*(particle_[loop].size),(r[2]+u[2])*(-particle_[loop].size));
					glTexCoord2f(0,	1);					
					glVertex3f((r[0]-u[0])*(-particle_[loop].size),(r[1]-u[1])*(particle_[loop].size),(r[2]-u[2])*(particle_[loop].size));
					glTexCoord2f(1,	0);					
					glVertex3f((r[0]+u[0])*(-particle_[loop].size),(r[1]+u[1])*(particle_[loop].size),(r[2]+u[2])*(-particle_[loop].size));
					glTexCoord2f(0,	0);					
					glVertex3f((r[0]-u[0])*(particle_[loop].size),(r[1]-u[1])*(particle_[loop].size),(r[2]-u[2])*(particle_[loop].size));
					/*
					glNormal3f(0,-1,0);
					glTexCoord2f(1,	0);	glVertex3f( particle_[lop].size,	particle_[lop].size,	particle_[lop].size);
					glTexCoord2f(0,	0);	glVertex3f( -particle_[lop].size,	particle_[lop].size,	particle_[lop].size);
					glTexCoord2f(0,	1);	glVertex3f( -particle_[lop].size,	particle_[lop].size,	-particle_[lop].size);
					glTexCoord2f(1,	1);	glVertex3f(	 particle_[lop].size,	particle_[lop].size,	-particle_[lop].size);
				*/glEnd();
				
			glPopMatrix();										// Done Building Triangle Strip

			particle_[loop].x+=particle_[loop].xi/(slowdown_*1000);// Move On The X Axis By X Speed
			particle_[loop].y+=particle_[loop].yi/(slowdown_*1000);// Move On The Y Axis By Y Speed
			particle_[loop].z+=particle_[loop].zi/(slowdown_*1000);// Move On The Z Axis By Z Speed

			particle_[loop].xi+=particle_[loop].xg;			// Take Pull On X Axis Into Account
			particle_[loop].yi+=particle_[loop].yg;			// Take Pull On Y Axis Into Account
			particle_[loop].zi+=particle_[loop].zg;			// Take Pull On Z Axis Into Account
			particle_[loop].life-=particle_[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particle_[loop].life < 0.0f) {					// If Particle Is Burned Out
				//particle_[loop].active = false;
				//--active_;
				particle_[loop].reset();
			}
		}
    }

	
	glPopMatrix();
	glDepthMask(GL_TRUE) ;
	glDisable(GL_BLEND);		
	glEnable( GL_DEPTH_TEST );
}

void EngineBlast::reset(){
	for (int loop = 0; loop < maxParticles_; loop++)					// lop Through All The Particles
		particle_[loop].reset();
	active_ = maxParticles_;
}

void EngineBlast::setCamera(Camera* camera){
	this->camera = camera;
}