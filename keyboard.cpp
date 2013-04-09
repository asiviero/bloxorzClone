#include "inc.h"

extern Block *b1;
extern float camDistance[3];
extern float angle[3];
extern bool keyStates[255];

void specialKeysHandler(int button, int x, int y) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch(button) {
		case GLUT_KEY_UP :
			b1->moveBlock(up);
			break;
		case GLUT_KEY_DOWN :
			b1->moveBlock(down);
			break;
		case GLUT_KEY_LEFT :
			b1->moveBlock(leftd);
			break;
		case GLUT_KEY_RIGHT :
			b1->moveBlock(rightd);
			break;
	}
   	glutPostRedisplay();


}

void initializeKeyStates() {
	for(int i=0; i<255; i++) keyStates[i] = false;
}

void keyboardHandler(unsigned char button, int x, int y) {
		keyStates[button] = true;
		glutPostRedisplay();

}

void keyboardUpHandler(unsigned char button, int x, int y) {
		keyStates[button] = false;
		glutPostRedisplay();

}

void performKeyOperations() {
	bool pressed = false;
	if(keyStates['w'] == true) {
		angle[X_AXIS] -= 0.1;
		pressed = true;
	}
	if(keyStates['s'] == true) {
		angle[X_AXIS] += 0.1;
		pressed = true;
	}
	if(keyStates['d'] == true) {
		angle[Y_AXIS] -= 0.1;
		pressed = true;
	}
	if(keyStates['a'] == true) {
		angle[Y_AXIS] += 0.1;
		pressed = true;
	}
	if(keyStates['z'] == true) {
			angle[Z_AXIS] -= 0.1;
			pressed = true;
	}
	if(keyStates['c'] == true) {
		angle[Z_AXIS] += 0.1;
		pressed = true;
	}
	if(keyStates['o'] == true) {
		camDistance[Z_AXIS] -= 0.1;
		pressed = true;
	}
	if(keyStates['p'] == true) {
		camDistance[Z_AXIS] += 0.1;
		pressed = true;
	}
	if(keyStates['l'] == true) {
		camDistance[Y_AXIS] -= 0.1;
		pressed = true;
	}
	if(keyStates['k'] == true) {
		camDistance[Y_AXIS] += 0.1;
		pressed = true;
	}
	if(keyStates['m'] == true) {
		camDistance[X_AXIS] -= 0.1;
		pressed = true;
	}
	if(keyStates['n'] == true) {
		camDistance[X_AXIS] += 0.1;
		pressed = true;
	}
	if(pressed == true) {
		glutPostRedisplay();
	}
}
