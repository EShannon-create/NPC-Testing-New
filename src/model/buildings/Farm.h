#ifndef FARM_H
#define FARM_H

#include "Building.h"
#include "model/items/containers/ItemContainer.h"
#include "model/items/ItemStack.h"

class Farm : public Building {
public:
	Farm();
	~Farm();
	float getCropGrowth();
	void grow(float,float);
	int getTextureIndex();
	char getID();
	void harvest(ItemContainer*);
private:
	float cropGrowth;
	float getCropGrowthSpeed();
};

#endif