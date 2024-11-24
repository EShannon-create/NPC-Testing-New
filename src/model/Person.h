#ifndef PERSON_H
#define PERSON_H

#include "World.h"

void setWorldDimensions(int,int);
int getWorldHeight();
int getWorldWidth();

class Person {
public:
	Person();
	Person(int, int);
	~Person();
	void move(int, int, bool);
	int getX();
	int getY();
	void forage(World*);
	bool build(World*, char);
	bool isActing();
	void update(float);
	char* getWaitText();
	float getWaitTime();
private:
	int x;
	int y;

	float actionTimer;
	void wait(char*,float);
	char* waitText;

	Tile* getOn(World*);
};

#endif
