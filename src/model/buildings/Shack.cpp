#include "Shack.h"

Shack::Shack() {

}
Shack::~Shack() {

}
int Shack::getTextureIndex() {
	if (!isComplete()) return 0;
	return 3;
}
char Shack::getID() {
	return 'S';
}
bool Shack::canSleep() {
	return true;
}
float Shack::buildingEffort() {
	return 4.0f;
}