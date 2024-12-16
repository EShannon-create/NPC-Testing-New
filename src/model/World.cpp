#include "World.h"
#include <time.h>
#include <stdio.h>

#define NOISE_SCALE 0.05f
#define TERRAIN_ZOOM_SCALE 33
#define FERTILITY_ZOOM_SCALE 10
#define DAY_LENGTH 24*60 //Remember, 1 second IRL -> 1 minute in game, this is the real life seconds for an in game day
#define DROPOFF_LIMIT 0.8

int peopleCount = 16;

float World::calculateDropOff(float x, float y) {
	float dx = x / width / NOISE_SCALE * 2 - 1.0f;
	float dy = y / height / NOISE_SCALE * 2 - 1.0f;

	float d = dx * dx + dy * dy;
	//printf("(%f,%f) %f - %f\n", dx, dy, d, (d < DROPOFF_LIMIT * DROPOFF_LIMIT ? 1.0 : 0.0));

	return d < DROPOFF_LIMIT * DROPOFF_LIMIT ? 0 : DROPOFF_LIMIT-d;
}

World::World(int width, int height) : width(width), height(height){
	currentTime = 0;
	date = 1;
	month = 1;
	year = 1;

	map = new Tile*[width * height];

	Octave* heightMap = new Octave(time(0),TERRAIN_ZOOM_SCALE);
	Octave* fertilityMap = new Octave(time(0)*2,FERTILITY_ZOOM_SCALE);

	const int spot = width * height / 100;

	for (int i = 0; i < width * height; ++i) {

		float x = (i % width)*NOISE_SCALE;
		float y = (i / width)*NOISE_SCALE;



		float terrainHeight = heightMap->sample(x, y);//+calculateDropOff(x, y);
		float fertility = fertilityMap->sample(x, y);

		map[i] = new Tile(terrainHeight, fertility);
		if ((i+1) % (spot) == spot - 1) printf(".");
		if ((i + 1) % (spot*10) == spot*10 - 1) printf("\n");
	}

	delete heightMap;
	delete fertilityMap;
	updateIndex = 0;
	Tile::InitRandom(time(0));

	analyze();
}
World::~World() {
	delete[] map;
}
int mod(int dividend, int divisor) {
	int mod = dividend % divisor;
	return mod < 0 ? mod + divisor : mod;
}
Tile* World::getTile(int x, int y) {//This causes a donut world
	int i = mod(y,height) * width + mod(x,width);
	return map[i];
}
void World::updateTiles(int count, float delta_t) {
	int c = count > width * height ? width * height : count;

	float speedModifier = delta_t*(float)(width * height) / c;

	for (int i = updateIndex; i < updateIndex+c; i++) {
		Tile* tile = map[mod(i,width*height)];
		int x = i % width;
		int y = i / width;
		Tile* north = getTile(x, y + 1);
		Tile* south = getTile(x, y - 1);
		Tile* east = getTile(x + 1, y);
		Tile* west = getTile(x - 1, y);

		tile->updateGrowth(north, south, east, west, speedModifier);
	}
	updateIndex += c;
	if (updateIndex > width * height) updateIndex -= width * height;
}
void World::updateClock(float delta_t) {
	currentTime += delta_t;
	if (currentTime > DAY_LENGTH) {
		currentTime -= DAY_LENGTH;
		date++;
	}
	else return;

	int daysInMonth =
		(month == 2) ?
		(year % 400 == 0 || year % 4 == 0 && year % 100 != 0) ? 29 : 28
		:
		(month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
	if (date > daysInMonth) {
		date = 1;
		month++;
	}
	if (month > 12) {
		month = 1;
		year++;
	}

}
char* World::getTime() {
	int minutes = (int)currentTime % 60;//Seconds will always be rounded to 0 in the above conversion
	int hours = (int)(currentTime / 60.0f) % 12;
	if (hours == 0) hours = 12;
	bool pm = (int)(currentTime / 60.0f) % 24 > 11;

	char* tr = new char[20]; // YYYY/MM/DD HH:SS XM

	tr[0] = year / 1000 % 10 + 48;
	tr[1] = year / 100 % 10 + 48;
	tr[2] = year / 10 % 10 + 48;
	tr[3] = year % 10 + 48;
	tr[4] = '/';
	tr[5] = month >= 10 ? '1' : '0';
	tr[6] = month % 10 + 48;
	tr[7] = '/';
	tr[8] = date / 10 % 10 + 48;
	tr[9] = date % 10 + 48;
	tr[10] = ' ';
	tr[11] = hours >= 10 ? '1' : '0';
	tr[12] = hours % 10 + 48;
	tr[13] = ':';
	tr[14] = minutes / 10 % 10 + 48;
	tr[15] = minutes % 10 + 48;
	tr[16] = ' ';
	tr[17] = pm ? 'P' : 'A';
	tr[18] = 'M';
	tr[19] = '\0';

	return tr;
}
float World::getSunAngle() {
	float f = fmodf(currentTime * 360.0 / (float)(DAY_LENGTH)  - 90,360.0);
	if (f < 0) f += 360;
	return f;
}
void World::analyze() {
	int desertCount = 0;
	int lowFertCount = 0;
	int highFertCount = 0;
	int jungleCount = 0;
	for (int i = 0; i < width * height; i++) {
		Tile* t = map[i];
		int fert = t->fertilityGrade();
		switch (fert) {
		case 0: desertCount++; break;
		case 1: lowFertCount++; break;
		case 2: highFertCount++; break;
		case 3: jungleCount++; break;
		}
	}
	printf("Desert Count: %d\nLow Fertility Count: %d\nHigh Fertility Count: %d\nJungle Count: %d\n",desertCount,lowFertCount,highFertCount,jungleCount);
}