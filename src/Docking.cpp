//Docking.cpp
//Main project file, initialization of window and registering callbacks.

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
//#include <GL/GLUT.h>
//#include <GL/GL.h>
#include "GLUT.H"

#include "Controller.h"
#include "View.h"

//States of the game
#define START 1
#define PAUSE 0
#define RESTART 2  

//directions
#define UP		true
#define DOWN	false
#define LEFT	true
#define RIGHT	false


Controller* controller;
View* view;


//actions taken at the end of the program
void end() {	
	delete view;
	delete controller;
}


//initialising objects and basic parameters. 
void init() {
	controller = new Controller();
	view = new View(controller->getModel());
	
	glDepthFunc( GL_LESS );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glutSetCursor( GLUT_CURSOR_NONE );

	//enables a special mode, in which all the surfaces disappear
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);			
}


void reshape(GLsizei w, GLsizei h) {
	if( h > 0 && w > 0 ) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (double) w / h, 0.01, 55);
		glMatrixMode(GL_MODELVIEW);
	}
}


void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//handling camera
	controller->cameraHandler();
	
	//drawing scene
	view->drawAll(controller->getModel()->getFrameNo());
	controller->update();
	
	glFlush();
	glutSwapBuffers();
}


//handles pressing of keys
void handleKeyPress(unsigned char key, int x, int y) {
	switch (key) {
        case 27 : exit(0); break;
		case 'p': controller->togglePause(); break;
		case 'o': controller->restartGame();
    }
}

//handles pressing of the special keys
void handleSpecialPress(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP: controller->pitchPelican(DOWN); break;
	case GLUT_KEY_DOWN: controller->pitchPelican(UP); break;
	case GLUT_KEY_LEFT: controller->rotatePelican(LEFT); break;
	case GLUT_KEY_RIGHT: controller->rotatePelican(RIGHT); break;
    }
}



int main(int argc, char **argv){

	//init GLUT and create window
	glutInit(&argc, argv);													//initialization
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );			//setting display mode
	glutInitWindowPosition( 300,300 );										//setting initial position of the window
	glutInitWindowSize ( 700, 700 );										//setting initial size of the window

	//creating window
	glutCreateWindow("Dokowanie statku");

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutIdleFunc( display );

	// listeners
	glutKeyboardFunc(handleKeyPress);
	glutSpecialFunc(handleSpecialPress);
	
	//defines actions performed at program exit and initializes objects
	atexit( end );
	init();

	std::cout << "After init. Entering GLUT event processing cycle...\n";

	//enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}