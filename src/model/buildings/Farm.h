#ifndef FARM_H
#define FARM_H

#include "Building.h"

class Farm : public Building {
public:
	Farm();
	~Farm();
	float getCropGrowth();
	void grow(float,float);
	int getTextureIndex();
	char getID();
private:
	float cropGrowth;
	float getCropGrowthSpeed();
};

#endif