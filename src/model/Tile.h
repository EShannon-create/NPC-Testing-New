#ifndef TILE_H
#define TILE_H

#include "buildings/Building.h"
#include "buildings/Farm.h"
#include "buildings/House.h"
#include "buildings/Shack.h"
#include "buildings/Mine.h"
#include "items/containers/ItemContainer.h"
#include "items/ItemStack.h"
#include <random>

#define MINERAL_TYPES 5

class Tile {
public:
	Tile(float, float, float[]);
	~Tile();
	bool isLand();
	bool isWater();
	float getWildGrowth();
	void updateGrowth(Tile*, Tile*, Tile*, Tile*, float);
	void clearWildGrowth();
	int fertilityGrade();
	int growthGrade();
	char* getInfo();

	bool build(World*, int, int, char, float);
	void destroy();
	int getBuildingTextureIndex();
	bool harvest(ItemContainer*);

	Building* getBuilding();

	float getMineralValue(int);
	float mine(int,float);

	static void InitRandom(int);
private:
	float height;
	float fertility;
	float wildGrowth;
	Building* building;
	float minerals[5];

	bool harvestWildGrowth(ItemContainer*);
	bool harvestCropGrowth(ItemContainer*);
};
#endif
