#pragma once

#include "model/Recipe.h"
#include "Building.h"
#include "controller/ChoiceMenu.h"

class Crafter : public Building{
public:
	Crafter();
	~Crafter();
	virtual Recipe** recipes();
	virtual int recipeCount();
	ChoiceMenu* choiceMenu();
private:
	ChoiceMenu* menu;
	bool craft(Person*, World*, char);
};