/*
 * main.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "inc.h"

Platform *p1;
Block *b1;

// A very simple function to flush the screen and load the "cube"
void initScreen (void)
{
/*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, X_AXIS_SIZE, 0, Y_AXIS_SIZE, 0, Z_AXIS_SIZE);
}


void fsmFunction(void) {

	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// Looping
	glutPostRedisplay();
	glutSwapBuffers();

	cout << "Plat Goal: " << p1->Goal[X_AXIS] << " " << p1->Goal[Y_AXIS] << "\n";
//	cout << "Plat Starting Point: " << p1->StartPosition[0][X_AXIS] << " " << p1->StartPosition[0][Y_AXIS] << " " << p1->StartPosition[1][X_AXIS] << " " << p1->StartPosition[1][Y_AXIS] <<"\n";
	cout << "Block Point: " << b1->Position[0][X_AXIS] << " " << b1->Position[0][Y_AXIS] << " " << b1->Position[1][X_AXIS] << " " << b1->Position[1][Y_AXIS] <<"\n";

	// Check for out of platform
	if(b1->isBlockOutOfPlatform(p1->PlatformMatrix)) {
		cout << "Out of Platform!\n";
	}

	// Check if objective reached
	if(b1->isBlockOnPosition(p1->Goal)) {
		cout << "Objective Reached!\n";
	}

}


int main(int argc, char** argv) {

	// Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(1200,800);
	glutInitWindowSize(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
	int intMainWindowID;
	intMainWindowID = glutCreateWindow("Super Bira World");

	p1 = new Platform("../platforms/plat.txt");

	b1 = new Block(p1->StartPosition);

	//glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(specialKeysHandler);

	initScreen();
	glutDisplayFunc(fsmFunction);
	glutMainLoop();

	return 0;
}
