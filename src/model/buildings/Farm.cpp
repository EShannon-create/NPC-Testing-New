#include "Farm.h"

Farm::Farm() {
	cropGrowth = 0;
}
Farm::~Farm() {

}
float Farm::getCropGrowth() {
	return cropGrowth;
}
void Farm::grow(float maxAmount, float speedModifier) {
	if (cropGrowth == maxAmount) return;
	cropGrowth += this->getCropGrowthSpeed()*speedModifier;
	if (cropGrowth > maxAmount) cropGrowth = maxAmount;
}
float Farm::getCropGrowthSpeed() {
	return 0.005f;
}
int Farm::getTextureIndex() {
	if (!isComplete()) return 0;
	return 2;
}
char Farm::getID() {
	return 'F';
}