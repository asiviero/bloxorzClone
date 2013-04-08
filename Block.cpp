/*
 * Block.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "Block.h"

Block::Block(int pos[2][2]) {
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			Position[i][j] = pos[i][j];
		}
	}

}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

void Block::moveBlock(moveDirection m) {

	// Check if positions are equal
	bool equalPositionFlag = false;

	equalPositionFlag = (Position[0][X_AXIS] == Position[1][X_AXIS]) && (Position[0][Y_AXIS] == Position[1][Y_AXIS]);

	// If equal, one of the blocks moves one square, while the other moves two
	if(equalPositionFlag == true) {
		switch(m) {
			case up:
			case down:
				Position[0][Y_AXIS] += m*1;
				Position[1][Y_AXIS] += m*2;
				break;
			case leftd:
			case rightd:
				Position[0][X_AXIS] += m/2*1;
				Position[1][X_AXIS] += m/2*2;
				break;
			default:
				break;
		}
	}
	// For the axis of movement, check if a square is on a higher coordinate than the other
	// If so, move the one with higher coordinates 1 square and the smaller, 2 (positive movement). Invert otherwise
	// If not, move both 1 square
	else {
		switch(m) {

			case up:
				sleep(1);

				if(Position[0][Y_AXIS] < Position[1][Y_AXIS]) {
					Position[0][Y_AXIS] += 2;
					Position[1][Y_AXIS] += 1;
				}
				else if(Position[0][Y_AXIS] > Position[1][Y_AXIS]) {
					Position[1][Y_AXIS] += 2;
					Position[0][Y_AXIS] += 1;
				}
				else {
					Position[0][Y_AXIS] += 1;
					Position[1][Y_AXIS] += 1;
				}
				break;
			case down:
				sleep(1);
				if(Position[0][Y_AXIS] < Position[1][Y_AXIS]) {
					Position[0][Y_AXIS] -= 1;
					Position[1][Y_AXIS] -= 2;
				}
				else if(Position[0][Y_AXIS] > Position[1][Y_AXIS]) {
					Position[1][Y_AXIS] -= 1;
					Position[0][Y_AXIS] -= 2;
				}
				else {
					Position[0][Y_AXIS] -= 1;
					Position[1][Y_AXIS] -= 1;
				}
				break;

			case leftd:
				sleep(1);
				if(Position[0][X_AXIS] < Position[1][X_AXIS]) {
					Position[0][X_AXIS] -= 1;
					Position[1][X_AXIS] -= 2;
				}
				else if(Position[0][X_AXIS] > Position[1][X_AXIS]) {
					Position[1][X_AXIS] -= 1;
					Position[0][X_AXIS] -= 2;
				}
				else {
					Position[0][X_AXIS] -= 1;
					Position[1][X_AXIS] -= 1;
				}
				break;

			case rightd:
				sleep(1);

				if(Position[0][X_AXIS] < Position[1][X_AXIS]) {
					Position[0][X_AXIS] += 2;
					Position[1][X_AXIS] += 1;
				}
				else if(Position[0][X_AXIS] > Position[1][X_AXIS]) {
					Position[1][X_AXIS] += 2;
					Position[0][X_AXIS] += 1;
				}
				else {
					Position[0][X_AXIS] += 1;
					Position[1][X_AXIS] += 1;
				}
				break;

			default:
				break;

		} // End switch

	} // End else
} // End function
