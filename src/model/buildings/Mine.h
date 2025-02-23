#ifndef MINE_H
#define MINE_H

#include "Building.h"
#include "model/Tile.h"
#include "model/items/containers/ItemContainer.h"

class Mine : public Building {
public:
	Mine(Tile***);
	~Mine();
	bool mine(ItemContainer*);
	int getTextureIndex();
	char getID();
private:
	Tile*** tiles;
};

#endif