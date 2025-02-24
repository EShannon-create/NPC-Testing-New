#pragma once

#include "model/items/ItemStack.h"
#include "model/items/containers/ItemContainer.h"
#include <string>

class Recipe {
public:
	Recipe(int,ItemID*,int*,ItemID,int,std::string);
	Recipe(ItemID, int, ItemID, int, std::string);
	~Recipe();
	bool craft(ItemContainer*, ItemContainer*);
	bool craft(ItemContainer*);
	std::string name;
private:
	ItemID* items;
	int* quantities;
	ItemID yields;
	int quantity;
	int ingredients;
	bool canCraft(ItemContainer*);
	bool itemOkay(ItemContainer*, int);
};