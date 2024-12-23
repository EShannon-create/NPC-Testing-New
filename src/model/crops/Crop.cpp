#include "Crop.h"

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
ItemStack* Crop::harvest() {
	return ItemStack::create(STICK, 1);
}
bool Crop::isFinished() {
	return cropGrowth >= getMinimumGrowthToHarvest();
}
float Crop::getMinimumGrowthToHarvest() {
	return 1000;
}
float Crop::getCropGrowthSpeed() {
	return 0.005f;
}