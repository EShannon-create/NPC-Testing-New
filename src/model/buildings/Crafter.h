#pragma once

#include "model/Recipe.h"
#include "Building.h"
#include "controller/ChoiceMenu.h"

class Crafter : public Building{
public:
	Crafter(const int,Recipe**);
	~Crafter();
	ChoiceMenu* choiceMenu();
private:
	ChoiceMenu* menu;
	bool craft(Person*, World*, char);
	Recipe** recipes;
};