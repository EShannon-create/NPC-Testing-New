/*
This is currently based off of a Raylib example file
*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "view/TileRenderer.h"
#include "view/GUIRenderer.h"
#include "view/EntityRenderer.h"

#include "controller/PlayerControl.h"

#include "model/World.h"
#include "model/Person.h"

#include <stdio.h>

//CONSTANTS
#define TITLE "Human Cattle II - Chud Wars"
#define RESOURCES_FOLDER "resources"
#define WORLD_SIZE 1000 //4400 is an accurate earth-size
#define WORLD_ASPECT_RATIO 2 //Should be 2
#define TILE_SIZE 32
#define TILE_UPDATES_PER_TICK 100000//On my computer, it takes about a quarter million to start struggling to keep 60 FPS, should be a setting
//									  Don't worry btw there's logic compensating for less tile updates per tick, lowering this makes things like wild growth happen faster per update

//VARIABLES
int screenWidth = 1280;
int screenHeight = 720;
bool drawFPS = false;
double runtime = 0.0;
float runtimeSpeed = 1.0;
float skip = 0.0;
Texture sleeping;
//

//DATA
World* world;
Person* player;
Person** people;
int peopleArraySize = 16;
int population;
//

//METHODS
void GameLoop();
void FPS();
void SaveMapImage();
void CheckScreenSize();
void DrawClock();
//

void initializePeople() {
	people = new Person * [peopleArraySize];
	people[0] = player;
	population = 1;
	for (int i = 1; i < peopleArraySize; i++) {
		people[i] = nullptr;
	}
}
void resizePeopleArray() {
	peopleArraySize *= 2;
	Person** newPeople = new Person*[peopleArraySize];
	for (int i = 0; i < population; i++) {
		newPeople[i] = people[i];
	}
	delete[] people;
	people = newPeople;
}
void registerPerson(Person* person) {
	if (population >= peopleArraySize) resizePeopleArray();
	people[population] = person;
	population++;
}
void initialize() {
	SetTargetFPS(60);
	world = new World(WORLD_SIZE*WORLD_ASPECT_RATIO,WORLD_SIZE);
	setWorldDimensions(WORLD_SIZE*WORLD_ASPECT_RATIO, WORLD_SIZE);
	player = new Person(screenWidth/2,screenHeight/2);
	initializePeople();
	registerPerson(new Person(screenWidth / 2+1, screenHeight / 2));

	InitializeTextures();
	sleeping = LoadTexture("sleep.png");

	InitializeChoiceMenus();
}

void clear() {
	delete world;
	delete player;
	delete[] people;
	UninitializeTextures();
	UnloadTexture(sleeping);
	DestroyChoiceMenus();
}

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	//SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, TITLE);
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir(RESOURCES_FOLDER);

	initialize();
	
	// game loop
	while (!WindowShouldClose() && player != nullptr)		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		GameLoop();
	}

	// cleanup
	clear();

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void FPS() {
	if (!drawFPS) return;

	DrawRectangle(70, 70, 92, 34, DARKGRAY);
	DrawFPS(80, 80);
}
static void resetTiles() {
	delete world;
	world = new World(WORLD_SIZE*WORLD_ASPECT_RATIO, WORLD_SIZE);
}
void ChangeSpeed(bool increase) {
	if (increase) runtimeSpeed += 1;
	else if (runtimeSpeed <= 1) return;
	else runtimeSpeed -= 1;
}
void NormalDraw() {
	HandleInputs(world, player);

	if (IsKeyPressed(KEY_R)) resetTiles();//These are outside of the HandleInputs() function for debugging purposes... they should be removed from this program entirely eventually
	if (IsKeyPressed(KEY_BACKSLASH)) drawFPS = !drawFPS;
	if (IsKeyPressed(KEY_P)) SaveMapImage();
	if (IsKeyPressed(KEY_G)) printf("(%d,%d)\n", player->getX(), player->getY());
	if (IsKeyPressed(KEY_F11)) {
		ToggleBorderlessWindowed();
		screenWidth = GetScreenWidth();
		screenHeight = GetScreenHeight();
	}
	if (IsKeyPressed(KEY_LEFT_BRACKET) || IsKeyPressed(KEY_RIGHT_BRACKET)) ChangeSpeed(IsKeyPressed(KEY_RIGHT_BRACKET));
	if (IsKeyPressed(KEY_MINUS) && skip == 0) skip = player->getWaitTime();
	if(IsKeyPressed(KEY_EQUAL)) runtimeSpeed = 1;

	// draw our textures to the screen
	DrawTiles(screenHeight, screenWidth, -player->getX(), -player->getY(), world);
	DrawEntities(screenHeight, screenWidth, -player->getX(), -player->getY(), people, peopleArraySize);
	DrawGUI(player,getOpenChoiceMenu());
	DrawClock();
	FPS();
}
void SleepyTime() {
	DrawClock();
	DrawTexture(sleeping, 0, 0, WHITE);
}
void Kill(int index) {
	delete people[index];
	people[index] = nullptr;
	if (index == 0) player = nullptr;
	population--;
}
void GameLoop() {
	const float delta_t = GetFrameTime() * (player->isSleeping() ? 500 : 1) * runtimeSpeed + skip;
	skip = 0;
	//printf("Delta T: %f\n", delta_t);

	CheckScreenSize();
	// drawing
	BeginDrawing();

	// Setup the backbuffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	if (player->isSleeping()) SleepyTime();
	else NormalDraw();


	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();




	//This should be moved to a central MODEL UPDATER
	world->updateTiles(TILE_UPDATES_PER_TICK, delta_t);
	world->updateClock(delta_t);
	
	for (int i = 0; i < population; i++) {
		if (people[i] == nullptr) continue;

		people[i]->update(delta_t);
		if (people[i]->healthBar() < 0) Kill(i);
	}
}
void DrawClock() {
	char* timetxt = world->getTime();
	DrawText(timetxt, screenWidth/100, screenHeight/100, 16, WHITE);
	//printf(timetxt);
	delete timetxt;

	if (runtimeSpeed < 1.0) DrawText("Slow", screenWidth / 100, screenHeight / 100 + 20, 16, WHITE);
	else if (runtimeSpeed > 1.0) DrawText("Fast", screenWidth / 100, screenHeight / 100 + 20, 16, WHITE);
}
void SaveMapImage() {
	Image image = GenImageColor(WORLD_SIZE*WORLD_ASPECT_RATIO, WORLD_SIZE, BLANK);
	for (int y = 0; y < WORLD_SIZE; y++) {
		for (int x = 0; x < WORLD_SIZE*WORLD_ASPECT_RATIO; x++) {
			Tile* tile = world->getTile(x,y);
			int fg = tile->fertilityGrade();
			Color color = tile->isWater() ? BLUE :
				fg == 0 ? YELLOW :
				fg == 1 ? BROWN :
				fg == 2 ? DARKGREEN : GREEN;
			ImageDrawPixel(&image, x, y, color);
		}
	}
	for (int i = 0; i < population; i++) {
		Person* person = people[i];
		int x = person->getX();
		int y = person->getY();
		ImageDrawPixel(&image, x, y, RED);
	}
	ExportImage(image, "renders/world.png");

	Color full[MINERAL_TYPES] = { DARKGRAY, GREEN, RED, WHITE, YELLOW };
	for (int i = 0; i < MINERAL_TYPES; i++) {
		for (int y = 0; y < WORLD_SIZE; y++) {
			for (int x = 0; x < WORLD_SIZE * WORLD_ASPECT_RATIO; x++) {
				Tile* tile = world->getTile(x, y);
				if (tile->isWater()) continue;

				float mineral = tile->getMineralValue(i);

				Color color = ColorLerp(BLACK, full[i], tile->getMineralValue(i));
				ImageDrawPixel(&image, x, y, color);
			}
		}
		char dir[] = "renders/mineral .png";
		dir[15] = i + 49;
		ExportImage(image, dir);

	}
	UnloadImage(image);
}
void CheckScreenSize() {
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();
}