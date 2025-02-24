#pragma once

#include "Crafter.h"

class Smeltry : public Crafter {
public:
	Smeltry();
	~Smeltry();
	Recipe** recipes() override;
	int recipeCount() override;
	int getTextureIndex() override;
	char getID() override;
protected:
	float buildingEffort() override;
};