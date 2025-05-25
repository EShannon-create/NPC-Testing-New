#include "PlayerControl.h"
#include "model/buildings/Crafter.h"
#include <stdio.h>

bool keydown = false;


#define WALK_UP KEY_W
#define WALK_DOWN KEY_S
#define WALK_LEFT KEY_A
#define WALK_RIGHT KEY_D
#define RUN KEY_LEFT_SHIFT

#define INTERACT KEY_E
#define STUDY_TILE KEY_Q
#define CONSTRUCT_BUILDING KEY_B
#define ORGANIZE_INVENTORY KEY_I
#define SELECTION_UP KEY_UP
#define SELECTION_DOWN KEY_DOWN
#define SLEEP KEY_SLASH
#define SELECT KEY_ENTER
#define PLANT_SEED KEY_PERIOD

ChoiceMenu* buildings;
ChoiceMenu* openChoiceMenu;

bool build(Person*, World*, char);

ChoiceMenu* getOpenChoiceMenu() {
	return openChoiceMenu;
}

void InitializeChoiceMenus() {
	openChoiceMenu = nullptr;

	int buildingCount = 5;
	std::string* buildingNames = new std::string [buildingCount];
	char* buildingControls = new char[buildingCount];
	buildingNames[0] = "-Shack"; buildingControls[0] = 'S';
	buildingNames[1] = "-House"; buildingControls[1] = 'H';
	buildingNames[2] = "-Farm"; buildingControls[2] = 'F';
	buildingNames[3] = "-Mine"; buildingControls[3] = 'M';
	buildingNames[4] = "-Smeltry"; buildingControls[4] = 'O';
	buildings = new ChoiceMenu(
		buildingCount,
		buildingNames,
		build,
		buildingControls
	);
}
void DestroyChoiceMenus() {
	delete buildings;
}

void HandleInputs(World* world, Person* player) {
	if (IsKeyPressed(STUDY_TILE)) {
		char* str = world->getTile(player->getX(), player->getY())->getInfo();
		printf(str);
		delete str;
	}

	if (player->acting()) return;

	bool running = IsKeyDown(RUN);
	int x = 0;
	int y = 0;
	if (IsKeyDown(WALK_UP)) y--;
	if (IsKeyDown(WALK_DOWN)) y++;
	if (IsKeyDown(WALK_LEFT)) x--;
	if (IsKeyDown(WALK_RIGHT)) x++;
	keydown = IsKeyDown(WALK_UP) || IsKeyDown(WALK_DOWN) || IsKeyDown(WALK_LEFT) || IsKeyDown(WALK_RIGHT);
	if(keydown) player->move(x, y, running, world);

	if (IsKeyPressed(INTERACT)) {
		Tile* tile = player->getOn(world);
		Building* building = tile->getBuilding();

		if(building && building->getID() == 'O') openChoiceMenu = static_cast<Crafter*>(building)->choiceMenu();
		else player->tileInteract(world);
		if (openChoiceMenu) {
			printf("OpenChoiceMenu %d\n",openChoiceMenu->getChoices());
			for (int i = 0; i < openChoiceMenu->getChoices(); i++) printf("%d. %s\n",i+1,openChoiceMenu->getChoiceName(i));
		}
	}
	if (IsKeyPressed(CONSTRUCT_BUILDING)) {
		Building* b = world->getTile(player->getX(), player->getY())->getBuilding();
		if (b) {
			if (b->isComplete()) return;
			build(player, world, b->getID());
		}
		else openChoiceMenu = buildings;
	}
	if (IsKeyPressed(SELECTION_UP)) {
		if (openChoiceMenu) openChoiceMenu->previous();
		else player->getInventory()->up();
	}
	if (IsKeyPressed(SELECTION_DOWN)) {
		if (openChoiceMenu) openChoiceMenu->next();
		else player->getInventory()->down();
	}
	if (IsKeyPressed(ORGANIZE_INVENTORY)) player->organizeInventory();
	if (IsKeyPressed(SLEEP)) player->sleep(world);
	if (IsKeyPressed(SELECT)) {
		if (openChoiceMenu) {
			openChoiceMenu->doChoice(player, world);
			openChoiceMenu = nullptr;
		}
		else player->eat();
	}
	if (IsKeyPressed(PLANT_SEED)) player->plant(world);

}
bool build(Person* p, World* w, char c) {
	return p->build(w, c);
}