#ifndef ITEM_CONTAINER_H
#define ITEM_CONTAINER_H

#include "model/items/ItemStack.h"

class ItemContainer {
public:
	ItemContainer(int);
	~ItemContainer();
	ItemStack* get(int);
	ItemStack* pop(int);
	bool addAtIndex(ItemStack*, int);
	bool add(ItemStack*);
	static bool move(ItemContainer*, int, ItemContainer*);
	void collapse();
	int getSize();
private:
	ItemStack** items;
	const int size;
};

#endif