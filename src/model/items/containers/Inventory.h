#ifndef INVENTORY_H
#define INVENTORY_H

#include "ItemContainer.h"

class Inventory : public ItemContainer {
public:
	Inventory();
	void up();
	void down();
	ItemStack* getSelected();
	int getSelectionIndex();
private:
	int selectionIndex;
};

#endif
