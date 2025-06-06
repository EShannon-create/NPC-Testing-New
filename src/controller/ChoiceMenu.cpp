#include "ChoiceMenu.h"

ChoiceMenu::ChoiceMenu(int choices, std::string* names, std::function<bool(Person*, World*, char)> func, char* controls) : choices(choices), names(names), func(func), controls(controls) {
	index = 0;
}
ChoiceMenu::~ChoiceMenu() {
	delete[] names;
	delete[] controls;
}
void ChoiceMenu::next() {
	index++;
	if (index >= choices) index = 0;
}
void ChoiceMenu::previous() {
	index--;
	if (index < 0) index = choices;
}
int ChoiceMenu::getChoices() {
	return choices;
}
char* ChoiceMenu::getChoiceName(int i) {
	char* toReturn = new char[32];
	strcpy(toReturn, names[i].c_str());
	return toReturn;
}
int ChoiceMenu::getSelectedIndex() {
	return index;
}
bool ChoiceMenu::doChoice(Person* person, World* world) {
	return func(person, world, controls[index]);
}