/*
 * TextScreen.h
 *
 *  Created on: Apr 17, 2013
 *      Author: andre
 */

#ifndef TEXTSCREEN_H_
#define TEXTSCREEN_H_


#include "inc.h"
#include "Screen.h"

class TextScreen : public Screen {
public:
	string texto;
	string subTitle;
	TextScreen(string texto, string subTitle);
	virtual void Render();
	//virtual ~TextScreen();
};

#endif /* TEXTSCREEN_H_ */
