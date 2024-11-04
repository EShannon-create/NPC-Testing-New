/*
This is currently based off of a Raylib example file
*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "view/TileRenderer.h"
#include "controller/PlayerControl.h"
#include "model/World.h"
#include "model/Person.h"
#include "view/EntityRenderer.h"
#include <stdio.h>

//CONSTANTS
#define TITLE "Human Cattle II - Chud Wars"
#define RESOURCES_FOLDER "resources"
#define WORLD_SIZE 1000
#define TILE_SIZE 32
#define TILE_UPDATES_PER_TICK 100000//On my computer, it takes about a quarter million to start struggling to keep 60 FPS, should be a setting
//

//VARIABLES
int screenWidth = 1280;
int screenHeight = 720;
bool drawFPS = false;
//

//DATA
World* world;
Person* player;
Person** people;
int population = 16;
//

//METHODS
void GameLoop();
void FPS();
void SaveMapImage();
//

void initializePeople() {
	people = new Person * [population];
	people[0] = player;
	for (int i = 1; i < population; i++) {
		people[i] = nullptr;
	}
}
void initialize() {
	SetTargetFPS(60);
	world = new World(WORLD_SIZE,WORLD_SIZE);
	player = new Person();
	initializePeople();
	people[1] = new Person(1, 1);

	InitializeTextures();
}

void clear() {
	delete world;
	delete player;
	delete[] people;
	UninitializeTextures();
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
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
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
void resetTiles() {
	delete world;
	world = new World(WORLD_SIZE, WORLD_SIZE);
}
void GameLoop() {
	// drawing
	BeginDrawing();

	// Setup the backbuffer for drawing (clear color and depth buffers)
	ClearBackground(GRAY);

	HandleInputs(world,player);

	if (IsKeyPressed(KEY_R)) resetTiles();//These are outside of the HandleInputs() function for debugging purposes... they should be removed from this program entirely eventually
	if (IsKeyPressed(KEY_BACKSLASH)) drawFPS = !drawFPS;
	if (IsKeyPressed(KEY_I)) SaveMapImage();

	// draw our textures to the screen
	DrawTiles(screenHeight,screenWidth,-player->getX(), -player->getY(), world);
	DrawEntities(screenHeight, screenWidth, -player->getX(), -player->getY(), people, population);
	FPS();


	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();




	//This should be moved to a central MODEL UPDATER
	world->updateTiles(TILE_UPDATES_PER_TICK);
}
void SaveMapImage() {
	Image image = GenImageColor(WORLD_SIZE, WORLD_SIZE, BLANK);
	for (int y = 0; y < WORLD_SIZE; y++) {
		for (int x = 0; x < WORLD_SIZE; x++) {
			Tile* tile = world->getTile(x,y);
			int fg = tile->fertilityGrade();
			Color color = tile->isWater() ? BLUE :
				fg == 0 ? YELLOW :
				fg == 1 ? BROWN :
				fg == 2 ? DARKGREEN : GREEN;
			ImageDrawPixel(&image, x, y, color);
		}
	}
	ExportImage(image, "surely this name will help find it.png");
	UnloadImage(image);
}
