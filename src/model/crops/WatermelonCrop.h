#ifndef WATERMELON_H
#define WATERMELON_H

#include "Crop.h"

class WatermelonCrop : public Crop {
public:
	float getMinimumGrowthToHarvest();
	void harvest(ItemContainer*);
};

#endif