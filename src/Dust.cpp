#include <windows.h>
//#include <GL/gl.h>
//#include <GL/GLUT.H>
#include "GLUT.H"
#include <iostream>
#include "dust.h"
#include "ImageLoader.h"
#include "Camera.h"

Dust::Dust(): slowdown_(40), maxParticles_(10000), active_(maxParticles_) {
	std::cout<<"Dust::Dust()\n";

	particle_ = new Particles[maxParticles_];

	texture_ = loadTexture("textures/particle.bmp");

	reset();
}

Dust::~Dust() {
	std::cout<<"Dust::~Dust()\n";
	
	delete particle_;
}

void Dust::drawDust(float xx, float yy, float zz, Camera* cam, float kat, float promien) {
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
	
	// lecimy rysowanie pylku
	for (int lop = 0; lop < maxParticles_; lop++)					// lop Through All The Particles
	{
		if (particle_[lop].active)							// If The Particle Is Active
		{
			float x=particle_[lop].x;						// Grab Our Particle X Position
			float y=particle_[lop].y;						// Grab Our Particle Y Position
			float z=particle_[lop].z;					// Particle Z Pos

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
					glVertex3f((r[0]+u[0])*(particle_[lop].size),(r[1]+u[1])*(particle_[lop].size),(r[2]+u[2])*(-particle_[lop].size));
					glTexCoord2f(0,	1);
					glVertex3f((r[0]-u[0])*(-particle_[lop].size),(r[1]-u[1])*(particle_[lop].size),(r[2]-u[2])*(particle_[lop].size));
					glTexCoord2f(1,	0);
					glVertex3f((r[0]+u[0])*(-particle_[lop].size),(r[1]+u[1])*(particle_[lop].size),(r[2]+u[2])*(-particle_[lop].size));
					glTexCoord2f(0,	0);	
					glVertex3f((r[0]-u[0])*(particle_[lop].size),(r[1]-u[1])*(particle_[lop].size),(r[2]-u[2])*(particle_[lop].size));
					/*
					glNormal3f(0,-1,0);
					glTexCoord2f(1,	0);	glVertex3f( particle_[lop].size,	particle_[lop].size,	particle_[lop].size);
					glTexCoord2f(0,	0);	glVertex3f( -particle_[lop].size,	particle_[lop].size,	particle_[lop].size);
					glTexCoord2f(0,	1);	glVertex3f( -particle_[lop].size,	particle_[lop].size,	-particle_[lop].size);
					glTexCoord2f(1,	1);	glVertex3f(	 particle_[lop].size,	particle_[lop].size,	-particle_[lop].size);
				*/glEnd();
				
			glPopMatrix();										// Done Building Triangle Strip

			particle_[lop].x+=particle_[lop].xi/(slowdown_*1000);// Move On The X Axis By X Speed
			particle_[lop].y+=particle_[lop].yi/(slowdown_*1000);// Move On The Y Axis By Y Speed
			particle_[lop].z+=particle_[lop].zi/(slowdown_*1000);// Move On The Z Axis By Z Speed

			particle_[lop].xi+=particle_[lop].xg;			// Take Pull On X Axis Into Account
			particle_[lop].yi+=particle_[lop].yg;			// Take Pull On Y Axis Into Account
			particle_[lop].zi+=particle_[lop].zg;			// Take Pull On Z Axis Into Account
			particle_[lop].life-=particle_[lop].fade;		// Reduce Particles Life By 'Fade'

			if (particle_[lop].life < 0.0f) {					// If Particle Is Burned Out
				particle_[lop].active = false;
				--active_;
			}
		}
    }

	
	glPopMatrix();
	glDepthMask(GL_TRUE) ;
	glDisable(GL_BLEND);		
	glEnable( GL_DEPTH_TEST );
}

void Dust::reset() {
	for (int lop=0; lop < maxParticles_; lop++) {
		particle_[lop].active=true;								// Make All The Particles Active
		particle_[lop].life=3.0f;								// Give All The Particles Full Life
		particle_[lop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle_[lop].x = 0;
		particle_[lop].y = 0;
		particle_[lop].z = 0;
		particle_[lop].xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
		particle_[lop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particle_[lop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
		particle_[lop].xg=0.0f;									// Set Horizontal Pull To Zero
		particle_[lop].yg=0.00f;								// Set Vertical Pull Downward
		particle_[lop].zg=0.0f;									// Set Pull On Z Axis To Zero
		particle_[lop].size = 0.20f;
	}

	active_ = maxParticles_;
}
