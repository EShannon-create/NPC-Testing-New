#include "ClickControl.h"

#include <stdio.h>

int scrollIndex = 0;
char chars[] = {'F','H','S','M','O'};
const int arrLen = 5;

void HandleClicks(World* world, Person* person, int screenWidth, int screenHeight, int TILE_SIZE) {
	if (IsMouseButtonDown(0)) {
		const float wheel = GetMouseWheelMove();
		if (wheel < 0) scrollIndex++;
		else if (wheel > 0) scrollIndex--;
		if (scrollIndex < 0) scrollIndex += arrLen;
	}
	else if (IsMouseButtonReleased(0)) {
		Vector2 v = GetMousePosition();

		int tileX = person->getX() + v.x / TILE_SIZE - screenWidth / 2 / TILE_SIZE+1;
		int tileY = person->getY() + v.y / TILE_SIZE - screenHeight / 2 / TILE_SIZE+1;

		Tile* tile = world->getTile(tileX,tileY);

		Tile*** area;
		if (chars[scrollIndex % arrLen] == 'M') {
			area = new Tile * *[5];
			for (int i = 0; i < 5; i++) {
				area[i] = new Tile * [5];
				for (int j = 0; j < 5; j++) area[i][j] = world->getTile(tileX + i-2, tileY + j-2);
			}
		}
		else area = nullptr;

		tile->build(area,chars[scrollIndex % arrLen],1.0f);
		printf("Built %c at (%d,%d)\nPlayer at (%d,%d)\n", chars[scrollIndex % arrLen], tileX, tileY,person->getX(),person->getY());
	}
}