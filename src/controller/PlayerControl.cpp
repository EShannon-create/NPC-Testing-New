#include "PlayerControl.h"

bool keydown = false;

void HandleInputs(World* world, Person* player) {

	if (IsKeyDown(KEY_LEFT_SHIFT) || !keydown) {
		if (IsKeyDown(KEY_W)) player->moveUp();
		if (IsKeyDown(KEY_S)) player->moveDown();
		if (IsKeyDown(KEY_A)) player->moveLeft();
		if (IsKeyDown(KEY_D)) player->moveRight();
		keydown = IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D);
	}
	else if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) keydown = false;

	if (IsKeyPressed(KEY_E))  world->getTile(player->getX(), player->getY())->setWildGrowth(0);
}