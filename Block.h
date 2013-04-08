/*
 * Block.h
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "inc.h"

class Block {
public:
	int Position[2][2];

	Block(int pos[2][2]);
	virtual ~Block();

	void moveBlock(moveDirection m);
};

#endif /* BLOCK_H_ */
