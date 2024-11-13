#include "PlayerControl.h"
#include <stdio.h>

bool keydown = false;


#define WALK_UP KEY_W
#define WALK_DOWN KEY_S
#define WALK_LEFT KEY_A
#define WALK_RIGHT KEY_D
#define RUN KEY_LEFT_SHIFT

#define HARVEST_WILD_GROWTH KEY_E
#define STUDY_TILE KEY_Q
#define CONSTRUCT_BUILDING KEY_B
#define OPEN_INVENTORY KEY_I

void HandleInputs(World* world, Person* player) {

	if (IsKeyDown(RUN) || !keydown) {
		if (IsKeyDown(WALK_UP)) player->moveUp();
		if (IsKeyDown(WALK_DOWN)) player->moveDown();
		if (IsKeyDown(WALK_LEFT)) player->moveLeft();
		if (IsKeyDown(WALK_RIGHT)) player->moveRight();
		keydown = IsKeyDown(WALK_UP) || IsKeyDown(WALK_DOWN) || IsKeyDown(WALK_LEFT) || IsKeyDown(WALK_RIGHT);
	}
	else if (IsKeyUp(WALK_UP) && IsKeyUp(WALK_DOWN) && IsKeyUp(WALK_LEFT) && IsKeyUp(WALK_RIGHT)) keydown = false;

	if (IsKeyPressed(HARVEST_WILD_GROWTH))  player->forage(world);
	if (IsKeyPressed(STUDY_TILE)) {
		char* str = world->getTile(player->getX(), player->getY())->getInfo();
		printf(str);
		delete str;
	}
}