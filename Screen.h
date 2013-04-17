/*
 * Screen.h
 *
 *  Created on: Apr 17, 2013
 *      Author: andre
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "inc.h"
class Screen : public Renderable {
public:
	virtual void Render()=0;
};

#endif /* SCREEN_H_ */
