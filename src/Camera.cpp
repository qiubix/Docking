//Camera.cpp
//Definitions of methods of the Camera class

#include "Camera.h"
#include <math.h>
#include <windows.h>
#include <iostream>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "GLUT.H"

 
Camera::Camera(float x, float y, float z)
{
	std::cout << "Camera::Camera()\n";

	m_position[0]=x;
	m_position[1]=y;
	m_position[2]=z;

	R = sqrtf(x*x+y*y+z*z);
    phi = atanf(m_position[2] / m_position[0]);
    theta = asinf(m_position[1] / R);
}
 
// ==============================================
// Turns the camera right and left 
void Camera::Yaw(float angle)
{
    phi += angle;
    Update();
}
 
// ==============================================
// Rotates the camera up and down 
void Camera::Pitch(float angle)
{
	if (theta+angle>1.5||theta+angle<-1.5) return;
    theta += angle;
    Update();
}
 
// ==============================================
// Zooms the camera 
void Camera::Zoom(float amount)
{
	if (R-amount<18||R-amount>300) return;
	R -= amount;
    Update();
}
 
// ==============================================
// Updates the position the camera is looking at 
void Camera::GetViewMatrix()
{
    gluLookAt(m_position[0],m_position[1],m_position[2],
		0,0,0,
		0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX,viewMatrix);
}
 
// ==============================================
//Updates position of the camera 
void Camera::Update()
{
    m_position[0] = R * cosf(theta) * cosf(phi);
    m_position[1] = R * sinf(theta);
    m_position[2] = R * cosf(theta) * sinf(phi);
}