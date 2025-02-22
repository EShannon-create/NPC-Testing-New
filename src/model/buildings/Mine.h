#pragma once

#include "model/World.h"

class Mine : public Building {
public:
	Mine(World*, int, int);
	~Mine();
	void mine(ItemContainer*);
	int getTextureIndex();
	char getID();
private:
	Tile*** tiles;
};