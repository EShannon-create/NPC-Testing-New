#include "Tile.h"
#include "buildings/Mine.h"
#include "buildings/Smeltry.h"
#include <string>
#include <math.h>
//#include <stdio.h>

#define LAND_THRESHOLD 0
#define WILD_GROWTH_SPEED 0.00005
#define FERTILITY_GRADES 4
#define MINIMUM_FERTILITY_FOR_HARVEST 0.4
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

Tile::Tile(float height, float fertility, float minerals[]) : height(height), fertility(fertilityModifier(fertility)) {
	wildGrowth = this->fertility;
	building = nullptr;
	for (int i = 0; i < MINERAL_TYPES; i++) {
		this->minerals[i] = minerals[i];
	}
}
Tile::~Tile() {
	//This will be relevant when I add buildings
	delete building;
	delete[] minerals;
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
	float cropGrowth = 0;
	Farm* farm = nullptr;
	if (building != nullptr && building->getID() == 'F') {
		//printf("Farm exists\n");
		farm = static_cast<Farm*>(building);
		cropGrowth = farm->getCropGrowth();
	}
	else if (building != nullptr) {
		wildGrowth = 0;
		return;
	}
	
	
	if (wildGrowth + cropGrowth == fertility) return;

	//printf("Passed return...\n");

	if (farm) {
		//printf("Farm exists... growing...\n");
		farm->grow(fertility - wildGrowth, speedModifier);
		cropGrowth = farm->getCropGrowth();

		wildGrowth += cropGrowth * WILD_GROWTH_SPEED * speedModifier * 2;
	}

	wildGrowth += north->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += south->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += east->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;
	wildGrowth += west->getWildGrowth() * WILD_GROWTH_SPEED * speedModifier;

	if (wildGrowth+cropGrowth > fertility) wildGrowth = fertility-cropGrowth;
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
	float cropGrowth = 0.f;

	if (building != nullptr && building->getID() == 'F') {
		Farm* farm = static_cast<Farm*>(building);
		cropGrowth = farm->getCropGrowth();
	}

	std::string s = "Wild Growth: " + std::to_string(wildGrowth) 
		+ (cropGrowth >= 0 ? "\nCrop Growth: " + std::to_string(cropGrowth) : "")
		+ "\nFertility: " + std::to_string(fertility)
		+ "\nCoal: " + std::to_string(minerals[0])
		+ "\nIron: " + std::to_string(minerals[1])
		+ "\nCopper: " + std::to_string(minerals[2])
		+ "\nTin: " + std::to_string(minerals[3])
		+ "\nGold: " + std::to_string(minerals[4])
		+ "\nBuilding: " +
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
bool Tile::build(Tile*** tiles, char ID, float amount) {
	if (building != nullptr && building->getID() != ID) return false;
	if (building != nullptr && building->isComplete()) return false;
	if (building == nullptr) switch (ID) {
	case 'F':
		building = new Farm();
		break;
	case 'H':
		building = new House();
		break;
	case 'S':
		building = new Shack();
		break;
	case 'M':
		if (!tiles) return false;
		building = new Mine(tiles);
		break;
	case 'O':
		building = new Smeltry();
	}
	
	building->construct(amount);
	return true;
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
	ic->add(stick);

	clearWildGrowth();

	return true;
}
bool Tile::harvestCropGrowth(ItemContainer* ic) {
	Farm* farm = static_cast<Farm*>(building);
	return farm->harvest(ic);
}
bool Tile::harvest(ItemContainer* ic) {
	if (building != nullptr && building->getID() == 'F') return harvestCropGrowth(ic);
	else return harvestWildGrowth(ic);
}
void Tile::InitRandom(int seed) {
	srand(seed);
}
float Tile::getMineralValue(int mineral) {
	return minerals[mineral];
}
float Tile::mine(int mineral, float amount) {
	float toReturn = minerals[mineral] * amount;
	minerals[mineral] -= toReturn;
	return toReturn;
}
Building* Tile::getBuilding() {
	return building;
}
void Tile::clearWildGrowth() {
	wildGrowth = 0;
}