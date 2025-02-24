#include "Crafter.h"

Crafter::Crafter() {
	const int count = recipeCount();
	std::string* names = new std::string[count];
	char* controls = new char[count];

	for (int i = 0; i < count; i++) {
		names[i] = recipes()[i]->name;
		controls[i] = i;
	}

	std::function<bool(Person*, World*, char)> f = [this](Person* p, World* w, char c) {return this->craft(p, w, c);};
	//Holy cancer! I hate C++!

	menu = new ChoiceMenu(count,names,f,controls);
}
Crafter::~Crafter() {
	delete menu;
}

int Crafter::recipeCount() { return 0; }
Recipe** Crafter::recipes() { return nullptr; }

ChoiceMenu* Crafter::choiceMenu() {
	return menu;
}
bool Crafter::craft(Person* player, World*, char control) {
	return recipes()[(int)control]->craft(player->getInventory(),player->getInventory());
}