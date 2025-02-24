#ifndef PERSON_H
#define PERSON_H

#include "World.h"
#include "model/items/containers/Inventory.h"

void setWorldDimensions(int,int);
int getWorldHeight();
int getWorldWidth();

class Person {
public:
	Person();
	Person(int, int);
	~Person();
	void move(int, int, bool, World* world);
	int getX();
	int getY();

	void tileInteract(World*);
	bool build(World*, char);
	void plant(World*);

	bool acting();
	void update(float);
	char* getWaitText();
	float getWaitTime();
	Inventory* getInventory();
	void organizeInventory();

	float healthBar();
	float hungerBar();
	float staminaBar();

	void takeDamage(float);
	bool eat();
	bool eat(int);

	void sleep(World*);
	bool isSleeping();

	Tile* getOn(World*);
private:
	int x;
	int y;

	float health;
	float hunger;
	float stamina;
	float max_stamina;
	bool exhaust(float);
	void rest();
	void eat(float);

	float actionTimer;
	void wait(char*,float);
	char* waitText;

	Inventory* inventory;
};

#endif
