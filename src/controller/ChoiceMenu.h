#pragma once

#include <string>
#include <functional>
#include "model/World.h"
#include "model/Person.h"

class ChoiceMenu {
public:
	ChoiceMenu(int choices, std::string* names, std::function<bool(Person*, World*, char)> func);
	~ChoiceMenu();
	void next();
	void previous();
	int getChoices();
	char* getChoiceName(int);
	int getSelectedIndex();
	bool doChoice(Person*, World*);
private:
	const int choices;
	std::string* names;
	std::function<bool(Person*, World*, char)> func;
	int index;
};