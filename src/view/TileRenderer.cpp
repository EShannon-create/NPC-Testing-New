#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "model/Perlin.h"
#include <time.h>

#define TILE_SIZE 32

Texture grass;
Texture water;
Perlin* heightMap;

void initializeTiles() {
	grass = LoadTexture("grass.png");
	water = LoadTexture("water.png");
	heightMap = new Perlin(time(0));
}
void clearTiles() {
	UnloadTexture(grass);
	UnloadTexture(water);
	delete heightMap;
}
void DrawTiles(int screenHeight, int screenWidth, int offsetX, int offsetY) {
	int tileHeight = screenHeight % TILE_SIZE == 0 ? screenHeight / TILE_SIZE : screenWidth / TILE_SIZE + 1;
	int tileWidth = screenWidth % TILE_SIZE == 0 ? screenWidth / TILE_SIZE : screenWidth / TILE_SIZE + 1;

	//DrawTexture(grass, 0, 0, WHITE);

	
	for (int i = 0; i < tileHeight; i++) {
		for (int j = 0; j < tileWidth; j++) {
			int y = i * TILE_SIZE;
			int x = j * TILE_SIZE;

			int si = i - offsetY;
			int sj = j - offsetX;

			if (heightMap->sample(si*0.1, sj*0.1) > 0) DrawTexture(grass, x, y, WHITE);
			else DrawTexture(water, x, y, WHITE);
		}
	}
	
}
void resetTiles() {
	delete heightMap;
	heightMap = new Perlin(time(0));
}