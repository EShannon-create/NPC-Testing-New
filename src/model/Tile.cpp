#include "Tile.h"

#define LAND_THRESHOLD 0
#define WILD_GROWTH_SPEED 0

Tile::Tile(float height, float fertility) : height(height), fertility(fertility) {
	wildGrowth = fertility;
}
Tile::~Tile() {
	//This will be relevant when I add buildings
}
bool Tile::isLand() {
	return height > LAND_THRESHOLD;
}
bool Tile::isWater() {
	return !isLand();
}
float Tile::getWildGrowth() {
	return wildGrowth;
}
void Tile::updateGrowth(Tile* north, Tile* south, Tile* east, Tile* west) {
	//This WILL NOT WORK right now.

	if (wildGrowth == fertility) return;

	wildGrowth += north->getWildGrowth() * WILD_GROWTH_SPEED;
	wildGrowth += south->getWildGrowth() * WILD_GROWTH_SPEED;
	wildGrowth += east->getWildGrowth() * WILD_GROWTH_SPEED;
	wildGrowth += west->getWildGrowth() * WILD_GROWTH_SPEED;
	
	if (wildGrowth > fertility) wildGrowth = fertility;
}