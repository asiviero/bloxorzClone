/*
 * Block.h
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "inc.h"

class Block : public Renderable {
public:
	int Position[2][2];

	Block(int pos[2][2]);
	virtual ~Block();

	void moveBlock(moveDirection m);
	bool isBlockOnPosition(int pos[2]);
	bool isBlockOutOfPlatform(bool PlatformMatrix[MAX_PLATFORM_SIZE_X][MAX_PLATFORM_SIZE_Y]);
	bool isBlockStanding();
	virtual void Render();
};

#endif /* BLOCK_H_ */
