/*
 * main.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "inc.h"

Platform *p1;
Block *b1;

float camDistance = 0;
// A very simple function to flush the screen and load the "cube"
void initScreen (void)
{
/*  select clearing (background) color       */
    //glClearColor (1.0, 1.0, 1.0, 0.0);
    glClearColor (0.0, 0.0, 0.0, 0.0);
       glShadeModel (GL_FLAT);
/*  initialize viewing values  */
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, MAX_PLATFORM_SIZE_X, 0, MAX_PLATFORM_SIZE_Y, 0, 100);
    glLoadIdentity();
    glFrustum(0,MAX_PLATFORM_SIZE_X,0,MAX_PLATFORM_SIZE_Y,-100,100);
    glMatrixMode(GL_MODELVIEW);*/
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}



void fsmFunction(void) {
	/*glEnable(GL_DEPTH_TEST);
	glClear (GL_COLOR_BUFFER_BIT);
//	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-10+camDistance,0,0,0,0,1,0);

	glTranslatef(0,0,-camDistance);

	// Draw the Brick
//	glPushMatrix();
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS],0);
		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS],0);
		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS]+1,0);
		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS]+1,0);
	glEnd();
//	glPopMatrix();


	glFlush();
	//glutSwapBuffers();

	//glutPostRedisplay();*/

	/*
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
*/
	   glClear (GL_COLOR_BUFFER_BIT);
	   glColor3f (1.0, 1.0, 1.0);
	   glLoadIdentity ();             /* clear the matrix */
	           /* viewing transformation  */
	   glTranslatef(-MAX_PLATFORM_SIZE_X/2,-MAX_PLATFORM_SIZE_Y/2,0);
	   gluLookAt (0, 0, 10.0-camDistance	, 0,0, 0.0, camDistance, 1.0, 0.0);
	   glScalef (1.0, 1.0, 1.0);      /* modeling transformation */
	   //glutWireCube (1.0);

	   	glPushMatrix();
	   	glColor3f(1,0,0);

	   	glBegin(GL_POLYGON);
	   		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS],0);
	   		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS],0);
	   		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS]+1,0);
	   		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS]+1,0);
	   	glEnd();

	   	glBegin(GL_POLYGON);
			glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS],1);
			glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS],1);
			glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS]+1,1);
			glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS]+1,1);
		glEnd();



	   	glPopMatrix();

	   glFlush ();

	   	   cout << "Block Point: " << b1->Position[0][X_AXIS] << " " << b1->Position[0][Y_AXIS] << " " << b1->Position[1][X_AXIS] << " " << b1->Position[1][Y_AXIS] <<"\n";
}


int main(int argc, char** argv) {

	// Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(1200,800);
	glutInitWindowSize(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
	int intMainWindowID;
	intMainWindowID = glutCreateWindow("Bloxorz Clone");

	p1 = new Platform("../platforms/plat.txt");

	b1 = new Block(p1->StartPosition);

	//glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(specialKeysHandler);

	initScreen();
	glutDisplayFunc(fsmFunction);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
