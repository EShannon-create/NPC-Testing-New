#include "Farm.h"

Farm::Farm() {
	crop = nullptr;
}
Farm::~Farm() {
	delete crop;
}
float Farm::getCropGrowth() {
	if (crop == nullptr) return -1;
	return crop->getCropGrowth();
}
void Farm::grow(float maxAmount, float speedModifier) {
	if (crop != nullptr) crop->grow(maxAmount, speedModifier);
}
int Farm::getTextureIndex() {
	if (!isComplete()) return 0;
	if (!crop) return 2;
	if (!crop->isFinished()) return 5;
	return 6;
}
char Farm::getID() {
	return 'F';
}
bool Farm::harvest(ItemContainer* to) {
	if (crop == nullptr) return false;
	if (!crop->isFinished()) return false;

	crop->harvest(to);

	delete crop;
	crop = nullptr;
	return true;
}
bool Farm::plant(Crop* seed) {
	if (!isComplete()) return false;
	if (crop != nullptr) return false;
	crop = seed;
	return true;
}
float Farm::buildingEffort() {
	return 12.0f;
}