#ifndef TILE_H
#define TILE_H

#include "buildings/Building.h"
#include "buildings/Farm.h"
#include "buildings/House.h"

class Tile {
public:
	Tile(float, float);
	~Tile();
	bool isLand();
	bool isWater();
	float getWildGrowth();
	void updateGrowth(Tile*, Tile*, Tile*, Tile*, float);
	int fertilityGrade();
	int growthGrade();
	void setWildGrowth(float);
	char* getInfo();

	bool build(char, float);
	void destroy();
	int getBuildingTextureIndex();
private:
	float height;
	float fertility;
	float wildGrowth;
	Building* building;
};

#endif
