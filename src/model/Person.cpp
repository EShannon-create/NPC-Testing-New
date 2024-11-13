#include "Person.h"
#include "World.h"

int worldWidth = 0;
int worldHeight = 0;

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
	if (y < 0) y += worldHeight;
}
void Person::moveDown() {
	y++;
	if (y >= worldHeight) y -= worldHeight;
}
void Person::moveLeft() {
	x--;
	if (x < 0) x += worldHeight;
}
void Person::moveRight() {
	x++;
	if (x >= worldHeight) x -= worldHeight;
}
int Person::getX() {
	return x;
}
int Person::getY() {
	return y;
}
void Person::forage(World* world) {
	world->getTile(this->getX(), this->getY())->setWildGrowth(0);
}
void setWorldDimensions(int width, int height) {
	worldHeight = height;
	worldWidth = width;
}
int getWorldHeight() {
	return worldHeight;
}
int getWorldWidth() {
	return worldWidth;
}