/*
 * keyboard.h
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

void specialKeysHandler(int button, int x, int y);
void keyboardHandler(unsigned char button, int x, int y);
void initializeKeyStates();
void keyboardHandler(unsigned char button, int x, int y);
void keyboardUpHandler(unsigned char button, int x, int y);
void performKeyOperations();

#endif /* KEYBOARD_H_ */
