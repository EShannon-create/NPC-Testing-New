#pragma once

#include "Building.h"

class Shack : public Building {
public:
	Shack();
	~Shack();
	int getTextureIndex();
	char getID();
	bool canSleep();
protected:
	float buildingEffort();
};