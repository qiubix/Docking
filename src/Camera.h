//Camera.h
//Declaration of class Camera

#ifndef CAMERA_H_
#define CAMERA_H_

#include <math.h>

// class representing camera, contains a methods allowing to rotate and zoom the view. 
class Camera
{
private:
 //   float m_position[3];     // pozycja kamery
    float m_lookAt[3];       // punkt na ktory patrzy
    //glm::vec3   m_up;           // orientacja, to jest kierunek gdzie jest góra
    //float       m_fov;          // kat widzenia
 
    float theta, phi, R;    // wspolrzedne sferyczne
                            // theta - szerokosc geograficzna
                            // phi - dlugosc
 
public:

	float viewMatrix[16];
	float m_position[3];     // pozycja kamery
 
	Camera(float x, float y, float z);
 
	//moving camera
    void Yaw(float angle);
    void Pitch(float angle);
    void Zoom(float amount);
 
    void GetViewMatrix();
 
	//returns right/left angle
    float GetYaw() const{
        return phi;
    }
 
	//retunrs up/down angle
    float GetPitch() const{
        return theta;
    }
 
	//returns distance from center
    float GetDistanceFromCenter() const{
		return sqrtf(m_position[0]*m_position[0]+m_position[1]*m_position[1]+m_position[2]*m_position[2]);
    }
 
private:
    void Update();
};
 
#endif // CAMERA_H_