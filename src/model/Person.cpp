#include "Person.h"

Person::Person() : x(0), y(0) {
	//x = 0;
	//y = 0;
}
Person::Person(int x, int y) : x(x), y(y) {

}
Person::~Person() {

}
void Person::moveUp() {
	y--;
}
void Person::moveDown() {
	y++;
}
void Person::moveLeft() {
	x--;
}
void Person::moveRight() {
	x++;
}
int Person::getX() {
	return x;
}
int Person::getY() {
	return y;
}