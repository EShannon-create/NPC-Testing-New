#include "Person.h"
#include "World.h"
#include "buildings/Farm.h"
#include <stdio.h>

int worldWidth = 0;
int worldHeight = 0;

#define BUILDING_AMOUNT_PER_TIME 0.05 //This is very low I know, but it should take a lot of chuddies a lot of time to build a building
#define BUILDING_TIME 60.0
#define BUILDING_EXHAUSTION 5
#define FORAGING_TIME 15.0
#define FORAGING_EXHAUSTION 0.3
#define WALKING_TIME 0.75 //Assume a tile is an acre (square)
                          //Therefore a tile is ~208 ft (linear)
                          //Average walking speed is 4.7 ft/s
                          //Therefore it should take about 45 s to walk a tile
                          //One in-game day is 24 min (1 hr -> 1 min)
                          //At that scale, 0.75 seconds to walk a tile
#define SLEEP_TIME 480.0
#define EAT_TIME 1.5

#define WALKING_EXHAUSTION 0.01
#define RUNNING_TIME WALKING_TIME/8.5 //Usain bolt runs 8.5 times faster than the average walking speed
#define RUNNING_EXHAUSTION 0.1 //It's less efficient to run than walk
#define SWIMMING_TIME 1.6 //Average swim speed is ~2.2 ft/s for a decently strong swimmer, assuming you're already at max velocity, which is a little less than half average walking time
#define SWIMMING_EXHAUSTION 0.75 //It's extremely inefficient to swim

#define SQRT2 1.41421356237309504880 //Relevant

#define START_HEALTH 10.0
#define START_HUNGER 2000.0
#define MAX_HUNGER 2000.0
#define START_STAMINA 10.0
#define EXHAUSTION_RATE 0.1
#define STAMINA_RECOVERY_RATE 0.5 //Per second
#define METABOLISM_CALORIES 1.5 //Calories passively burned per second
#define STAMINA_RECOVERY_CALORIES 3.0 //Calories burned to recover stamina

#define STARVATION_DAMAGE START_HEALTH/MAX_HUNGER //Damage done per calorie below 0 per tick

Person::Person() : Person(0,0) {
}
Person::Person(int x, int y) : x(x), y(y) {
	actionTimer = 0.0f;
	waitText = nullptr;
	inventory = new Inventory();

	health = START_HEALTH;
	hunger = START_HUNGER;
	stamina = START_STAMINA;
	max_stamina = START_STAMINA;
}
Person::~Person() {
	delete inventory;
}
Inventory* Person::getInventory() {
	return inventory;
}
void Person::move(int x, int y, bool running, World* world) {
	bool swimming = world->getTile(this->x, this->y)->isWater() && world->getTile(this->x + x, this->y + y)->isWater();
	
	float exhaust = swimming ? SWIMMING_EXHAUSTION : running ? RUNNING_EXHAUSTION : WALKING_EXHAUSTION;
	float time = swimming ? SWIMMING_TIME : running ? RUNNING_TIME : WALKING_TIME;

	if (!this->exhaust(exhaust)) return;
	if (x != 0 && y != 0) time *= SQRT2;

	wait(
		swimming ? ".... Swimming\0" :
		running ? ".... Running\0" : ".... Walking\0",
		time
	);
	

	this->x += x;
	this->y += y;
	if (y < 0) y += worldHeight;
	else if (y > worldHeight) y -= worldHeight;
	if (x < 0) x -= worldWidth;
	else if (x > worldWidth) x -= worldWidth;
}
int Person::getX() {
	return x;
}
int Person::getY() {
	return y;
}
Tile* Person::getOn(World* world) {
	return world->getTile(this->getX(), this->getY());
}
void Person::tileInteract(World* world) {
	if (acting() || !exhaust(FORAGING_EXHAUSTION)) return;

	Tile* tile = getOn(world);
	Building* building = tile->getBuilding();

	if (building == nullptr) {
		if (tile->harvest(inventory)) wait(".... Foraging\0", FORAGING_TIME);
	}
	else switch (building->getID()) {
	case 'F':
		if (tile->harvest(inventory)) wait(".... Harvesting\0", FORAGING_TIME);
		else {
			tile->clearWildGrowth();
			wait(".... Weeding\0", FORAGING_TIME);
		}

	case 'M':
		// to do
		break;
	}

}
void setWorldDimensions(int width, int height) {
	worldHeight = height;
	worldWidth = width;
}
int getWorldHeight() {
	return worldHeight;
}
int getWorldWidth() {
	return worldWidth;
}
bool Person::build(World* world, char buildingID) {
	if (acting() || !exhaust(BUILDING_EXHAUSTION)) return false;
	wait(".... Building\0",BUILDING_TIME);
	return getOn(world)->build(buildingID, BUILDING_AMOUNT_PER_TIME);
}
bool Person::acting() {
	return actionTimer > 0.0f;
}
void Person::update(float delta_t) {
	if(actionTimer > 0.0f) actionTimer -= delta_t;
	if (actionTimer < 0.0f) {
		actionTimer = 0.0f;
	}

	if (stamina < max_stamina) {
		hunger -= (max_stamina - stamina < STAMINA_RECOVERY_RATE * delta_t ? max_stamina - stamina : STAMINA_RECOVERY_RATE * delta_t) * STAMINA_RECOVERY_CALORIES;
		stamina += STAMINA_RECOVERY_RATE * delta_t;
	}
	if (stamina > max_stamina) stamina = max_stamina;

	hunger -= METABOLISM_CALORIES * delta_t;
	if (hunger < 0) {
		health += STARVATION_DAMAGE * hunger; //Always decreases since hunger < 0
		hunger = 0;
	}
}
void Person::wait(char* text, float time) {
	waitText = text;
	actionTimer += time;
}
char* Person::getWaitText() {
	char a = (int)(actionTimer / 10)%10+48;
	char b = ((int)actionTimer) % 10 + 48;
	char c = (int)(actionTimer * 10) % 10 + 48;

	int len = 5;
	for (int i = 0; i < 32; i++) {
		if (waitText[i] == '\0') {
			len = i+1;
			break;
		}
	}
	char* tr = new char[len];
	for (int i = 4; i < len; i++) tr[i] = waitText[i];//I don't care that this whole method is shitty

	tr[0] = a;
	tr[1] = b;
	tr[2] = '.';
	tr[3] = c;
	tr[len-1] = '\0';
	return tr;
}
float Person::getWaitTime() {
	return actionTimer;
}
void Person::organizeInventory() {
	inventory->collapse();
	waitText = waitText;
}
void Person::takeDamage(float amount) {
	health -= amount;
}
bool Person::exhaust(float amount) {
	if (stamina < amount) return false;
	stamina -= amount;
	max_stamina -= amount*EXHAUSTION_RATE;
	return true;
}
void Person::rest() {
	stamina = START_STAMINA;
	max_stamina = START_STAMINA;
}
float Person::healthBar() {
	return health / START_HEALTH;
}
float Person::hungerBar() {
	return hunger / START_HUNGER;
}
float Person::staminaBar() {
	return stamina / START_STAMINA;
}
void Person::sleep() {
	wait("....-Sleeping\0", SLEEP_TIME);
	rest();
}
bool Person::isSleeping() {
	return acting() && waitText != nullptr && waitText[4] == '-';
}
void Person::eat(float calories) {
	hunger += calories;
	if (hunger > MAX_HUNGER) hunger = MAX_HUNGER;
	wait(".... Eating\0", EAT_TIME);
}
bool Person::eat(int index) {
	if (acting()) return false;

	ItemStack* item = inventory->get(index);
	if (item == nullptr) return false;
	if (!item->isFood()) return false;

	float calories = item->getCalories();
	eat(calories);

	if (item->getQuantity() == 1) inventory->pop(index);
	item->decrease(1);

	return true;
}
bool Person::eat() {
	return eat(inventory->getSelectionIndex());
}
void Person::plant(World* world) {
	Tile* t = world->getTile(x, y);
	if (t->getBuilding() == nullptr || t->getBuilding()->getID() != 'F') return;


	Farm* farm = static_cast<Farm*>(t->getBuilding());
	int selectionIndex = inventory->getSelectionIndex();
	ItemStack* item = inventory->get(selectionIndex);
	Crop* crop = Crop::getCrop(item);
	if (crop == nullptr) return;
	if (!farm->plant(crop)) return;

	if (item->getQuantity() == 1) inventory->pop(selectionIndex);
	item->decrease(1);
}