#include "TileRenderer.h"
#include <stdio.h>

#define TILE_SIZE 32
#define FERTILITY_GRADES 4
#define BUILDING_TEXTURES 7

#define GOLDEN_HOUR Color{200,140,40,255}
#define NIGHT Color{90,112,150,255}
#define DAY Color{255,255,255,255}
#define TWILIGHT_ANGLE 15

#define MINERAL_INDICATOR_MODULUS 5
#define MINERAL_INDICATOR_DISPLAY_LENGTH 20
#define MINERAL_INDICATOR_DELAY 60

Texture2D* land;
Texture2D* growth;
Texture2D* buildingTextures;
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

	buildingTextures = new Texture2D[BUILDING_TEXTURES];
	buildingTextures[0] = LoadTexture("construction.png");
	buildingTextures[1] = LoadTexture("house.png");
	buildingTextures[2] = LoadTexture("empty farm.png");
	buildingTextures[3] = LoadTexture("stick hut.png");
	buildingTextures[4] = LoadTexture("mineshaft.png");
	buildingTextures[5] = LoadTexture("growing farm.png");
	buildingTextures[6] = LoadTexture("ready farm.png");
}
void UninitializeTextures() {
	for (int i = 0; i < FERTILITY_GRADES; i++) UnloadTexture(land[i]);
	for (int i = 0; i < FERTILITY_GRADES-1; i++) UnloadTexture(growth[i]);
	for (int i = 0; i < BUILDING_TEXTURES; i++) UnloadTexture(buildingTextures[i]);
	for (int i = 0; i < MINERAL_TYPES; i++) UnloadTexture(indicatorTextures[i]);
	UnloadTexture(water);
	UnloadTexture(chuddie);
	delete[] land;
	delete[] growth;
	delete[] buildingTextures;
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
			if (person->acting()) {
				char* text = person->getWaitText();
				DrawText(text, draw_x * TILE_SIZE + TILE_SIZE, draw_y * TILE_SIZE,TILE_SIZE/2,WHITE);
				//printf("%f\n",person->getWaitTime());
				delete text;
			}
		}
	}
}

Color getTint(float sunAngle) {
	if (sunAngle < TWILIGHT_ANGLE) {
		float x = (sunAngle) / TWILIGHT_ANGLE;
		return ColorLerp(GOLDEN_HOUR, DAY, x);
	}
	if (sunAngle < 180-TWILIGHT_ANGLE) return DAY;
	if (sunAngle < 180) {
		float x = (sunAngle - 180 + TWILIGHT_ANGLE) / TWILIGHT_ANGLE;
		return ColorLerp(DAY, GOLDEN_HOUR, x);
	}
	if (sunAngle < 180+TWILIGHT_ANGLE) {
		float x = (sunAngle - 180) / TWILIGHT_ANGLE;
		return ColorLerp(GOLDEN_HOUR, NIGHT, x);
	}
	if (sunAngle < 360-TWILIGHT_ANGLE) return NIGHT;
	if (sunAngle < 360) {
		float x = (sunAngle - 360 + TWILIGHT_ANGLE) / TWILIGHT_ANGLE;
		return ColorLerp(NIGHT, GOLDEN_HOUR, x);
	}

	return RED;
}

void DrawTiles(int screenHeight, int screenWidth, int offsetX, int offsetY, World* world, int frame) {
	int tileHeight = getTileHeight(screenHeight);
	int tileWidth = getTileWidth(screenWidth);

	Color tint = getTint(world->getSunAngle());
	
	for (int i = 0; i < tileHeight; i++) {
		for (int j = 0; j < tileWidth+1; j++) {
			int y = i * TILE_SIZE;
			int x = j * TILE_SIZE;

			int si = i - offsetY - tileHeight / 2 + 1;
			int sj = j - offsetX - tileWidth / 2 + 1;

			//if (si == 0 && sj == 0) continue;

			Tile* tile = world->getTile(sj, si);
			if (tile->isWater()) DrawTexture(water, x, y, tint);
			else {
				int grade = tile->fertilityGrade();
				DrawTexture(land[grade], x, y, tint);


				int growthGrade = tile->growthGrade();
				//printf("Wild Growth: %f, Grade: %d\n",tile->getWildGrowth(),growthGrade);
				if (growthGrade > 0) DrawTexture(growth[growthGrade - 1], x, y, tint);

				int buildingTexture = tile->getBuildingTextureIndex();
				if (buildingTexture == -1) continue;

				DrawTexture(buildingTextures[buildingTexture], x, y, tint);
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