#ifndef TILE_H
#define TILE_H

#include "buildings/Building.h"
#include "buildings/Farm.h"
#include "buildings/House.h"
#include "items/containers/ItemContainer.h"
#include "items/ItemStack.h"
#include <random>

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
	char* getInfo();

	bool build(char, float);
	void destroy();
	int getBuildingTextureIndex();
	bool harvest(ItemContainer*);

	static void InitRandom(int);
private:
	float height;
	float fertility;
	float wildGrowth;
	Building* building;

	bool harvestWildGrowth(ItemContainer*);
	bool harvestCropGrowth(ItemContainer*);
	static int roll(int, int);
};

#endif
