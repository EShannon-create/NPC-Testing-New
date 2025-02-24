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
bool Building::canSleep() { return false; }