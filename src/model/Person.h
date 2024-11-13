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
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int getX();
	int getY();
	
	void forage(World*);
private:
	int x;
	int y;
};

#endif
