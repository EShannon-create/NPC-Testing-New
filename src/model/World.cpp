#include "World.h"
#include <time.h>

#define NOISE_SCALE 0.05f;

int peopleCount = 16;

World::World(int width, int height) : width(width), height(height){
	map = new Tile*[width * height];

	Perlin* heightMap = new Perlin(time(0));
	Perlin* fertilityMap = new Perlin(time(0)+1);

	for (int i = 0; i < width * height; ++i) {

		float x = (i % width)*NOISE_SCALE;
		float y = (i / width)*NOISE_SCALE;

		float terrainHeight = heightMap->sample(x, y);
		float fertility = fertilityMap->sample(x, y);

		map[i] = new Tile(terrainHeight, fertility);
	}

	delete heightMap;
	delete fertilityMap;
	updateIndex = 0;
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
void World::updateTiles(int count) {
	int c = count > width * height ? width * height : count;

	for (int i = updateIndex; i < updateIndex+c; i++) {
		Tile* tile = map[mod(i,width*height)];
		int x = i % width;
		int y = i / width;
		Tile* north = getTile(x, y + 1);
		Tile* south = getTile(x, y - 1);
		Tile* east = getTile(x + 1, y);
		Tile* west = getTile(x - 1, y);

		float speedModifier = (float)(width * height) / c;

		tile->updateGrowth(north, south, east, west, speedModifier);
	}
	updateIndex += c;
	if (updateIndex > width * height) updateIndex -= width * height;
}