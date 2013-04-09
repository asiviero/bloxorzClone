/*
 * Platform.h
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

class Platform {
public:
	bool PlatformMatrix[MAX_PLATFORM_SIZE_X][MAX_PLATFORM_SIZE_Y];
	int StartPosition[2][2];
	int Goal[2];

	Platform(char *platfile);
	virtual ~Platform();
	virtual void Render();
};

#endif /* PLATFORM_H_ */
