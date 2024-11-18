#include "Person.h"
#include "World.h"
#include "buildings/Farm.h"
#include <stdio.h>

int worldWidth = 0;
int worldHeight = 0;

#define BUILDING_AMOUNT_PER_HOUR 0.05 //This is very low I know, but it should take a lot of chuddies a lot of time to build a building
#define HOUR_LENGTH 60.0
#define WALKING_TIME 0.75 //Assume a tile is an acre (square)
                          //Therefore a tile is ~208 ft (linear)
                          //Average walking speed is 4.7 ft/s
                          //Therefore it should take about 45 s to walk a tile
                          //One in-game day is 24 min (1 hr -> 1 min)
                          //At that scale, 0.75 seconds to walk a tile
#define RUNNING_TIME WALKING_TIME/8.5 //Usain bolt runs 8.5 times faster than the average walking speed
#define SQRT2 1.41421356237309504880 //Relevant

Person::Person() : Person(0,0) {

}
Person::Person(int x, int y) : x(x), y(y) {
	actionTimer = 0.0f;
	waitText = nullptr;
}
Person::~Person() {

}
void Person::move(int x, int y, bool running) {
	if (isActing()) return;

	float time = running ? RUNNING_TIME : WALKING_TIME;
	if (x != 0 && y != 0) time *= SQRT2;

	wait(
		running ? ".... Running\0" : ".... Walking\0",
		time
	);

	this->x += x;
	this->y += y;
	if (y < 0) y += worldHeight;
	else if (y > worldHeight) y -= worldHeight;
	if (x < 0) x -= worldWidth;
	else if (x > worldWidth) x -= worldWidth;
}
int Person::getX() {
	return x;
}
int Person::getY() {
	return y;
}
Tile* Person::getOn(World* world) {
	return world->getTile(this->getX(), this->getY());
}
void Person::forage(World* world) {
	if (isActing()) return;
	this->wait(".... Foraging\0",HOUR_LENGTH);
	getOn(world)->setWildGrowth(0);
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
bool Person::build(World* world, char buildingID) {
	if (isActing()) return false;
	this->wait(".... Building\0",HOUR_LENGTH);
	return getOn(world)->build(buildingID, BUILDING_AMOUNT_PER_HOUR);
}
bool Person::isActing() {
	return actionTimer > 0.0f;
}
void Person::update(float delta_t) {
	if(actionTimer > 0.0f) actionTimer -= delta_t;
	if (actionTimer < 0.0f) {
		actionTimer = 0.0f;
	}
}
void Person::wait(char* text, float time) {
	waitText = text;
	actionTimer += time;
}
char* Person::getWaitText() {
	char a = (int)(actionTimer / 10)%10+48;
	char b = ((int)actionTimer) % 10 + 48;
	char c = (int)(actionTimer * 10) % 10 + 48;

	int len = 5;
	for (int i = 0; i < 32; i++) {
		if (waitText[i] == '\0') {
			len = i+1;
			break;
		}
	}
	char* tr = new char[len];
	for (int i = 4; i < len; i++) tr[i] = waitText[i];//I don't care that this whole method is shitty

	tr[0] = a;
	tr[1] = b;
	tr[2] = '.';
	tr[3] = c;
	tr[len-1] = '\0';
	return tr;
}
float Person::getWaitTime() {
	return actionTimer;
}