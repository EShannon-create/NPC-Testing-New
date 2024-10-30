#include "World.h"
#include <time.h>

#define NOISE_SCALE 0.05f;

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
}
World::~World() {
	delete[] map;
}
int mod(int dividend, int divisor) {
	int mod = dividend % divisor;
	return mod < 0 ? mod + divisor : mod;
}
Tile* World::getTile(int x, int y) {//This causes a donut world
	int i = mod(y,height) * width + mod(x,height);
	return map[i];
}