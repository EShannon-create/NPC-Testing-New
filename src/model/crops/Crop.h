#ifndef CROP_H
#define CROP_H

//#include "model/items/ItemStack.h"

class Crop {
public:
	Crop();
	~Crop();
	float getCropGrowth();
	void grow(float, float);
	//ItemStack* harvest();
	bool isFinished();
private:
	float cropGrowth;
	float getCropGrowthSpeed();
	float getMinimumGrowthToHarvest();
};

#endif