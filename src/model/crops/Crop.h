#ifndef CROP_H
#define CROP_H

#include "model/items/ItemStack.h"
#include "model/items/containers/ItemContainer.h"
#include <random>

class Crop {
public:
	Crop();
	~Crop();
	float getCropGrowth();
	void grow(float, float);
	virtual void harvest(ItemContainer*);
	bool isFinished();
	static Crop* getCrop(ItemStack*);
private:
	float cropGrowth;
	float getCropGrowthSpeed();
	virtual float getMinimumGrowthToHarvest();
};

int roll(int, int);

#endif