#pragma once

#include "Building.h"

class Shack : public Building {
public:
	Shack();
	~Shack();
	int getTextureIndex() override;
	char getID() override;
	bool canSleep() override;
protected:
	float buildingEffort() override;
};