/*
 * Stage.h
 *
 *  Created on: Apr 17, 2013
 *      Author: andre
 */

#ifndef STAGE_H_
#define STAGE_H_
#include "inc.h"
#include "Screen.h"

class Stage : public Screen {
public:
	Block *b1;
	Platform *p1;

	Stage(char* platFile);
	virtual void Render();
	virtual ~Stage();
};

#endif /* STAGE_H_ */
