#include "Crop.h"
#include "WatermelonCrop.h"

Crop::Crop() {
	cropGrowth = 0;
}
Crop::~Crop() {

}
float Crop::getCropGrowth() {
	return cropGrowth;
}
void Crop::grow(float maxAmount, float speedModifier) {
	if (cropGrowth == maxAmount) return;
	cropGrowth += getCropGrowthSpeed() * speedModifier;
	if (cropGrowth > maxAmount) cropGrowth = maxAmount;
}
void Crop::harvest(ItemContainer* ic) {
	return;
}
bool Crop::isFinished() {
	return cropGrowth >= getMinimumGrowthToHarvest();
}
float Crop::getMinimumGrowthToHarvest() {
	return 1000;
}
float Crop::getCropGrowthSpeed() {
	return 0.0015f;
}
Crop* Crop::getCrop(ItemStack* item) {
	switch (item->getID()) {
	default: return nullptr;
	case WATERMELON_SEED: return new WatermelonCrop();
	}
}

/*
Inclusive [min,max]
*/
int roll(int min, int max) {
	return rand() % (++max - min) + min;
}