#include "Farm.h"

Farm::Farm() {
	crop = nullptr;
}
Farm::~Farm() {
	delete crop;
}
float Farm::getCropGrowth() {
	if (crop == nullptr) return 0;
	return crop->getCropGrowth();
}
void Farm::grow(float maxAmount, float speedModifier) {
	if (crop != nullptr) crop->grow(maxAmount, speedModifier);
}
int Farm::getTextureIndex() {
	if (!isComplete()) return 0;
	return 2;
}
char Farm::getID() {
	return 'F';
}
void Farm::harvest(ItemContainer* to) {
	if (crop == nullptr) return;
	if (!crop->isFinished()) return;

	ItemStack* stack = crop->harvest();
	to->add(stack);

	delete crop;
	crop = nullptr;
}