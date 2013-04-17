/*
 * TextScreen.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: andre
 */

#include "inc.h"

#include "TextScreen.h"

TextScreen::TextScreen(string texto, string subTitle) {
	// TODO Auto-generated constructor stub
	this->texto = texto;
	this->subTitle = subTitle;
}
/*
TextScreen::~TextScreen() {
	// TODO Auto-generated destructor stub
}*/

void TextScreen::Render() {
	glClearColor (1.0, 1.0,1.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
	//glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    glOrtho(0, X_AXIS_SIZE, 0, Y_AXIS_SIZE, 0, Z_AXIS_SIZE);

	//glClearColor (1.0, 1.0,1.0, 0.0);
	//gluLookAt(0,0,0,0,0,-1,0,1,0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	//glClear (GL_COLOR_BUFFER_BIT);
	// Game Title
	glRasterPos2f(20,150);
	glColor3f(0,0,0);
	//string GameTitle = "Welcome to Bloxorz Clone";
	  for (int i = 0; i < texto.length(); i++) {
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
	  }
	  glRasterPos2f(20,120);
	  for (int i = 0; i < subTitle.length(); i++) {
	  	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, subTitle[i]);
	  	  }
	  //int pos = 90;

	  glFlush();
	  //glutPostRedisplay();
}
