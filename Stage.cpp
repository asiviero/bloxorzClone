/*
 * Stage.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: andre
 */

#include "inc.h"
#include "Stage.h"

Stage::Stage(char *platFile) {
	p1 = new Platform(platFile);
	b1 = new Block(p1->StartPosition);

}

Stage::~Stage() {

	// TODO Auto-generated destructor stub
	delete p1;
	delete b1;
}

void Stage::Render() {

	glClearColor (0.0, 0.0, 0.0, 0.0);
		       glShadeModel (GL_FLAT);

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(55,1,0,5);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();



	glEnable(GL_DEPTH_TEST);
		   glClear (GL_COLOR_BUFFER_BIT);
		   glColor3f (1.0, 1.0, 1.0);
		   glLoadIdentity ();             /* clear the matrix */
		   glRotatef(angle[X_AXIS],1,0,0);
		   glRotatef(angle[Y_AXIS],0,1,0);
		   glRotatef(angle[Z_AXIS],0,0,1);

		   glTranslatef(-MAX_PLATFORM_SIZE_X/2,-MAX_PLATFORM_SIZE_Y/2,0);
		   gluLookAt (-camDistance[X_AXIS], -camDistance[Y_AXIS], 12.0-camDistance[Z_AXIS],
				   -camDistance[X_AXIS], -camDistance[Y_AXIS], -camDistance[Z_AXIS], 0.0, 1.0, 0.0);

	       /* viewing transformation  */

		   //glTranslatef(0,0,10);

		   //glScalef (1.0, 1.0, 1.0);      /* modeling transformation */
		   //glutWireCube (1.0);

		   p1->Render();
		   b1->Render();

		   glFlush ();
		   performKeyOperations();
}
