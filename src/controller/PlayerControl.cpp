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
#define INVENTORY_UP KEY_UP
#define INVENTORY_DOWN KEY_DOWN

void HandleInputs(World* world, Person* player) {

	bool running = IsKeyDown(RUN);
	if (running || !keydown) {
		int x = 0;
		int y = 0;
		if (IsKeyDown(WALK_UP)) y--;
		if (IsKeyDown(WALK_DOWN)) y++;
		if (IsKeyDown(WALK_LEFT)) x--;
		if (IsKeyDown(WALK_RIGHT)) x++;
		keydown = IsKeyDown(WALK_UP) || IsKeyDown(WALK_DOWN) || IsKeyDown(WALK_LEFT) || IsKeyDown(WALK_RIGHT);
		if(keydown) player->move(x, y, running);
	}
	else if (IsKeyUp(WALK_UP) && IsKeyUp(WALK_DOWN) && IsKeyUp(WALK_LEFT) && IsKeyUp(WALK_RIGHT)) keydown = false;

	if (IsKeyPressed(HARVEST_WILD_GROWTH))  player->forage(world);
	if (IsKeyPressed(STUDY_TILE)) {
		char* str = world->getTile(player->getX(), player->getY())->getInfo();
		printf(str);
		delete str;
	}
	if (IsKeyPressed(CONSTRUCT_BUILDING)) player->build(world, 'H');
	if (IsKeyPressed(KEY_F)) player->build(world, 'F');
	if (IsKeyPressed(INVENTORY_UP)) player->getInventory()->up();
	if (IsKeyPressed(INVENTORY_DOWN)) player->getInventory()->down();
}