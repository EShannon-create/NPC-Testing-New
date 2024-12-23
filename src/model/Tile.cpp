#include "Tile.h"
#include <string>
#include <math.h>
//#include <stdio.h>

#define LAND_THRESHOLD 0
#define WILD_GROWTH_SPEED 0.005
#define FERTILITY_GRADES 4
#define MINIMUM_FERTILITY_FOR_HARVEST 0.25
#define FERTILITY_PER_HARVEST_ROLL 0.15

#define MINIMUM_MANGOS_PER_ROLL 0
#define MAXIMUM_MANGOS_PER_ROLL 2
#define MINIMUM_STICKS_PER_ROLL 1
#define MAXIMUM_STICKS_PER_ROLL 4

float fertilityModifier(float input) {
	float g = input < 0 ? -input : input;
	float sqrt = std::sqrt(g) * (input < 0 ? -1 : 1);
	//printf("Input: %f, Not Normalized: %f, Output: %f\n", input,sqrt,sqrt*0.5+0.5);
	return sqrt * 0.5 + 0.5;
}

Tile::Tile(float height, float fertility) : height(height), fertility(fertilityModifier(fertility)) {
	wildGrowth = this->fertility;
	building = nullptr;
}
Tile::~Tile() {
	//This will be relevant when I add buildings
	delete building;
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
void Tile::updateGrowth(Tile* north, Tile* south, Tile* east, Tile* west, float speedModifier) {//Speed modifier is passed in as count, so if more tiles are updated per tick it does not effect how fast a tile's wild growth regenerates
	if (wildGrowth == fertility) return;

	//printf("Speed Modfifier: %f, %f\nWild Growth: %f\n", speedModifier, WILD_GROWTH_SPEED * speedModifier, wildGrowth);

	wildGrowth += north->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += south->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += east->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += west->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	
	if (wildGrowth > fertility) wildGrowth = fertility;

	//printf("Wild Growth: %f, Growth Grade: %d\n", wildGrowth, growthGrade());
}
int Tile::fertilityGrade() {
	float range = 1.0 / FERTILITY_GRADES;
	for (int i = FERTILITY_GRADES-1; i >= 0; i--) {
		if (fertility > i * range) return i;
	}
	return 0;
}
int Tile::growthGrade() {
	float range = 1.0 / FERTILITY_GRADES;
	for (int i = FERTILITY_GRADES - 1; i >= 0; i--) {
		if (wildGrowth > i * range) return i;
	}
	return 0;
}
char* Tile::getInfo() {
	std::string s = "Wild Growth: " + std::to_string(wildGrowth) + "\nFertility: " + std::to_string(fertility) + "\nBuilding: " +
		(building != nullptr ?
			std::to_string(building->getID())
			: "NONE")+"\n";
	char* str = new char[s.length() + 1];
	std::strcpy(str, s.c_str());
	return str;
}
void Tile::destroy() {
	delete building;
	building = nullptr;
}
bool Tile::build(char ID, float amount) {
	if (building != nullptr && building->getID() != ID) return false;
	if (building != nullptr && building->isComplete()) return false;
	if (building == nullptr) switch (ID) {
	case 'F':
		building = new Farm();
		break;
	case 'H':
		building = new House();
		break;
	}
	
	building->construct(amount);
}
int Tile::getBuildingTextureIndex() {
	if (building == nullptr) return -1;
	return building->getTextureIndex();
}
bool Tile::harvestWildGrowth(ItemContainer* ic) {
	const int rolls = (wildGrowth - MINIMUM_FERTILITY_FOR_HARVEST) / FERTILITY_PER_HARVEST_ROLL + 1;
	if (rolls < 1) return false;

	int mangos = 0;
	int sticks = 0;
	for (int i = 0; i < rolls; i++) {
		mangos += roll(MINIMUM_MANGOS_PER_ROLL, MAXIMUM_MANGOS_PER_ROLL);
		sticks += roll(MINIMUM_STICKS_PER_ROLL, MAXIMUM_STICKS_PER_ROLL);
	}

	ItemStack* mango = ItemStack::create(MANGO,mangos);
	ItemStack* stick = ItemStack::create(STICK, sticks);

	if (!ic->add(mango)) return false;
	if (!ic->add(stick)) return true;

	wildGrowth = 0;

	return true;
}
bool Tile::harvestCropGrowth(ItemContainer* ic) {
	Farm* farm = static_cast<Farm*>(building);

	return true;
}
bool Tile::harvest(ItemContainer* ic) {
	if (building != nullptr && building->getID() == 'F') return harvestCropGrowth(ic);
	else return harvestWildGrowth(ic);
}
void Tile::InitRandom(int seed) {
	srand(seed);
}
/*
Inclusive [min,max]
*/
int Tile::roll(int min, int max) {
	return rand() % (++max - min) + min;
}