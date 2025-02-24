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
	int getTextureIndex() override;
	char getID() override;
protected:
	float buildingEffort() override;
private:
	Tile*** tiles;
};

#endif