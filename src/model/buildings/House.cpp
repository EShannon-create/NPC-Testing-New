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