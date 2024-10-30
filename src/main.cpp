/*
This is currently based off of a Raylib example file
*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "view/TileRenderer.h"

//CONSTANTS
#define TITLE "NPC Ahh"
#define RESOURCES_FOLDER "resources"
//

//VARIABLES
Texture chuddie;

int screenWidth = 1280;
int screenHeight = 720;
bool drawFPS = true;

int offsetX = 0;
int offsetY = 0;
//

//METHODS
void GameLoop();
void FPS();
//

void initialize() {
	chuddie = LoadTexture("chuddie.png");
	initializeTiles();
}
void clear() {
	UnloadTexture(chuddie);
	clearTiles();
}

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, TITLE);

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

void HandleInputs() {
	if (IsKeyDown(KEY_R)) resetTiles();
	if (IsKeyDown(KEY_W)) offsetY++;
	if (IsKeyDown(KEY_S)) offsetY--;
	if (IsKeyDown(KEY_A)) offsetX++;
	if (IsKeyDown(KEY_D)) offsetX--;
}

void GameLoop() {
	// drawing
	BeginDrawing();

	// Setup the backbuffer for drawing (clear color and depth buffers)
	ClearBackground(GRAY);

	HandleInputs();

	// draw our textures to the screen
	DrawTiles(screenHeight,screenWidth,offsetX,offsetY);
	DrawTexture(chuddie, screenWidth/2-16, screenHeight/2-16, WHITE);//Magic numbers galore
	FPS();	


	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();
}
