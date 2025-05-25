#pragma once

#include "Crafter.h"

class Smeltry : public Crafter {
public:
	Smeltry();
	~Smeltry();
	static Recipe** recipes();
	int getTextureIndex() override;
	char getID() override;
protected:
	float buildingEffort() override;
};