/*
 * inc.h
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#ifndef INC_H_
#define INC_H_


// System Libs
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cmath>
#include <pthread.h>
#include <time.h>

// Graphic Libs
#include <GL/gl.h>
#include <GL/glut.h>
#include "Box2D/Box2D.h"
#include <png.h>
#include <SOIL.h>

// These constants stand for the width and height of the main window
#define MAIN_WINDOW_WIDTH 400
#define MAIN_WINDOW_HEIGHT 400

// These constants stand for the maximum coordinates allowed in a screen
#define X_AXIS_SIZE 2e2
#define Y_AXIS_SIZE 2e2
#define Z_AXIS_SIZE 2e2

// Constants used in motion vectors, such as position, speed and acceleration
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define MAX_PLATFORM_SIZE_X 100
#define MAX_PLATFORM_SIZE_Y 100

enum moveDirection {
	up = 1,
	down = -1,
	leftd = -2,
	rightd = 2
};

#include "Platform.h"
#include "Block.h"



#endif /* INC_H_ */
