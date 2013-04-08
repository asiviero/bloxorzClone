#include "inc.h"

extern Block *b1;
extern float camDistance;

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
		case GLUT_KEY_END:
			camDistance += 0.5;
			break;
		case GLUT_KEY_HOME:
			camDistance -= 0.5;
			break;
	}

	glutPostRedisplay();
}
