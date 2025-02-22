#include "House.h"

House::House() {

}
House::~House() {

}
int House::getTextureIndex() {
	if (!isComplete()) return 0;
	return 1;
}
char House::getID() {
	return 'H';
}
bool House::canSleep() { return true; }
float House::buildingEffort() {
	return 20.0f;
}