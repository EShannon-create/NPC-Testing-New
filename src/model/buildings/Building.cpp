#include "Building.h"

Building::Building() {
	completion = 0;
}
Building::~Building() {

}
void Building::construct(float amount) {
	completion += amount;
	if (completion > 1.0f) completion = 1.0f;
}
bool Building::isComplete() {
	return completion >= 1.0f;
}
int Building::getTextureIndex() { return 0; }
char Building::getID() {
	return 'm';
}