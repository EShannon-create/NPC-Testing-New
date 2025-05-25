#include "Crafter.h"
#include <stdio.h>

Crafter::Crafter(const int count, Recipe** recipes) {
	this->recipes = recipes;
	std::string* names = new std::string[count];
	char* controls = new char[count];

	for (int i = 0; i < count; i++) {
		names[i] = recipes[i]->name;
		controls[i] = i;
		printf("%s\n", recipes[i]->name.data());
	}

	std::function<bool(Person*, World*, char)> f = [this](Person* p, World* w, char c) {return this->craft(p, w, c);};
	//Holy cancer! I hate C++!

	menu = new ChoiceMenu(count,names,f,controls);
	printf("Choice Menu Original %d\n", menu->getChoices());
	printf("Choice Menu Original %d\n", menu->getChoices());
	for (int i = 0; i < menu->getChoices(); i++) printf("%d. %s\n", i + 1, menu->getChoiceName(i));
}
Crafter::~Crafter() {
	delete menu;
}

ChoiceMenu* Crafter::choiceMenu() {
	return menu;
}
bool Crafter::craft(Person* player, World*, char control) {
	printf("%s %s\n", menu->getChoiceName((int)control), recipes[(int)control]->name);
	return recipes[(int)control]->craft(player->getInventory(),player->getInventory());
}