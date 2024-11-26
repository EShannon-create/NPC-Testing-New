#include "Tile.h"
#include <string>
//#include <stdio.h>

#define LAND_THRESHOLD 0
#define WILD_GROWTH_SPEED 0.005
#define FERTILITY_GRADES 4

Tile::Tile(float height, float fertility) : height(height), fertility(fertility/2+0.5f) {
	wildGrowth = fertility / 2 + 0.5f;//Can I reference self.fertility?
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
void Tile::setWildGrowth(float value) {
	wildGrowth = value;
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