/*
 * Platform.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "inc.h"

Platform::Platform(char *platFile) {
	ifstream plF(platFile);

	// Reading the Goal
	plF >> Goal[X_AXIS] >> Goal[Y_AXIS];

	// Reading the Start Position
	plF >> StartPosition[0][X_AXIS] >> StartPosition[0][Y_AXIS] >> StartPosition[1][X_AXIS] >> StartPosition[1][Y_AXIS];

	// Initializing PlatformMatrix as false
	for(int i=0; i<MAX_PLATFORM_SIZE_X; i++) {
		for(int j=0; j<MAX_PLATFORM_SIZE_Y; j++) {
			PlatformMatrix[i][j] = false;
		}
	}

	// Reading the valid spots in the platform
	while(plF.good()) {
		int x,y;
		plF >> x >> y;
		PlatformMatrix[x][y] = true;
	}

	plF.close();
}

Platform::~Platform() {
	// TODO Auto-generated destructor stub
}

void Platform::Render() {
	for(int i=0; i<MAX_PLATFORM_SIZE_X; i++) {
		for(int j=0; j<MAX_PLATFORM_SIZE_Y; j++) {
			if(PlatformMatrix[i][j] == true) {
				glPushMatrix();
								   	if(i == Goal[X_AXIS] && j == Goal[Y_AXIS]) {
								   		glColor3f(0,0,0);
								   	} else {
								   		glColor3f(1,1,1);
								   	}
								   	glBegin(GL_POLYGON);
								   		glVertex3f(i,j,0);
								   		glVertex3f(i+1,j,0);
								   		glVertex3f(i+1,j+1,0);
								   		glVertex3f(i,j+1,0);
								   	glEnd();

								   	glBegin(GL_POLYGON);
										glVertex3f(i,j,0);
										glVertex3f(i,j,0.2);
										glVertex3f(i,j+1,0.2);
										glVertex3f(i,j+1,0);
									glEnd();

									glBegin(GL_POLYGON);
										glVertex3f(i+1,j,0);
										glVertex3f(i+1,j,0.2);
										glVertex3f(i+1,j+1,0.2);
										glVertex3f(i+1,j+1,0);
									glEnd();

								   	glBegin(GL_POLYGON);
										glVertex3f(i,j,0.2);
										glVertex3f(i+1,j,0.2);
										glVertex3f(i+1,j+1,0.2);
										glVertex3f(i,j+1,0.2);
									glEnd();

									glBegin(GL_POLYGON);
										glVertex3f(i,j+1,0);
										glVertex3f(i,j+1,0.2);
										glVertex3f(i+1,j+1,0.2);
										glVertex3f(i+1,j+1,0);
									glEnd();

									glBegin(GL_POLYGON);
										glVertex3f(i,j,0);
										glVertex3f(i,j,0.2);
										glVertex3f(i+1,j,0.2);
										glVertex3f(i+1,j,0);
									glEnd();

								   	glPopMatrix();

			}
		}
	}
}
