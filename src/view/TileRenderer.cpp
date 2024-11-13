#include "TileRenderer.h"

#define TILE_SIZE 32
#define FERTILITY_GRADES 4

Texture2D* land;
Texture2D* growth;
Texture water;
Texture chuddie;

int modw(int);
int modh(int);
bool in(int, int, int);

void InitializeTextures() {
	land = new Texture2D [FERTILITY_GRADES];
	for (int i = 0; i < FERTILITY_GRADES; i++) {
		char index = i+48;
		char filename[10] = "land .png";
		filename[4] = index;//Sorry this is jank as fuck
		land[i] = LoadTexture(filename);
	}
	
	growth = new Texture2D[FERTILITY_GRADES - 1];
	for (int i = 0; i < FERTILITY_GRADES - 1; i++) {
		char index = i + 48;
		char filename[12] = "growth .png";
		filename[6] = index;//Sorry this is jank as fuck
		growth[i] = LoadTexture(filename);
	}

	water = LoadTexture("water.png");
	chuddie = LoadTexture("chuddie.png");
}
void UninitializeTextures() {
	for (int i = 0; i < FERTILITY_GRADES; i++) UnloadTexture(land[i]);
	for (int i = 0; i < FERTILITY_GRADES-1; i++) UnloadTexture(growth[i]);
	UnloadTexture(water);
	UnloadTexture(chuddie);
	delete[] land;
	delete[] growth;
}

int getTileHeight(int screenHeight) {
	return screenHeight % TILE_SIZE == 0 ? screenHeight / TILE_SIZE : screenHeight / TILE_SIZE + 1;
}
int getTileWidth(int screenWidth){
	return screenWidth % TILE_SIZE == 0 ? screenWidth / TILE_SIZE : screenWidth / TILE_SIZE + 1;
}

void DrawEntities(int screenHeight, int screenWidth, int offsetX, int offsetY, Person** people, int count) {
	int tileHeight = getTileHeight(screenHeight);
	int tileWidth = getTileWidth(screenWidth);

	for (int i = 0; i < count; i++) {
		Person* person = people[i];
		if (person == nullptr) continue;

		int ww = getWorldWidth();
		int wh = getWorldHeight();

		int x = modw(person->getX());
		int y = modh(person->getY());

		int min_x = modw(- offsetX - tileWidth / 2 + 1);
		int min_y = modh(- offsetY - tileHeight / 2 + 1);

		int max_x = modw(tileWidth / 2 + 1 - offsetX);
		int max_y = modh(tileHeight / 2 + 1 - offsetY);

		if (in(min_x,max_x,x) && in(min_y,max_y,y)) {
			int draw_x = modw(x+offsetX+ tileWidth / 2 - 1);
			int draw_y = modh(y+offsetY+tileHeight/2-1);
			DrawTexture(chuddie, draw_x*TILE_SIZE, draw_y * TILE_SIZE, WHITE);
		}
	}
}

void DrawTiles(int screenHeight, int screenWidth, int offsetX, int offsetY, World* world) {
	int tileHeight = getTileHeight(screenHeight);
	int tileWidth = getTileWidth(screenWidth);

	
	for (int i = 0; i < tileHeight; i++) {
		for (int j = 0; j < tileWidth+1; j++) {
			int y = i * TILE_SIZE;
			int x = j * TILE_SIZE;

			int si = i - offsetY - tileHeight / 2 + 1;
			int sj = j - offsetX - tileWidth / 2 + 1;

			//if (si == 0 && sj == 0) continue;

			Tile* tile = world->getTile(sj, si);
			if (tile->isWater()) DrawTexture(water, x, y, WHITE);
			else {
				int grade = tile->fertilityGrade();
				DrawTexture(land[grade], x, y, WHITE);
				int growthGrade = tile->growthGrade();
				//printf("Wild Growth: %f, Grade: %d\n",tile->getWildGrowth(),growthGrade);
				if (growthGrade > 0) DrawTexture(growth[growthGrade - 1], x, y, WHITE);
			}

		}
	}
	
}
int modw(int x) {
	int mod = x % getWorldWidth();
	return mod < 0 ? mod + getWorldWidth() : mod;
}
int modh(int y) {
	int mod = y % getWorldHeight();
	return mod < 0 ? mod + getWorldHeight() : mod;
}
bool in(int min, int max, int val) {
	if (min <= max) return val >= min && val <= max;
	else return val >= min || val <= max;
}