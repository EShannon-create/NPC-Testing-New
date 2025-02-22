#include "Building.h"

Building::Building() {
	completion = 0;
}
Building::~Building() {

}
void Building::construct(float amount) {
	completion += amount;
}
bool Building::isComplete() {
	return completion >= buildingEffort();
}
int Building::getTextureIndex() { return 0; }
char Building::getID() {
	return 'm';
}
float Building::buildingEffort() { return 1.0f; }
bool Building::canSleep() { return false; }