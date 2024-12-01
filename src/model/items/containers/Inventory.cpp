#include "Inventory.h"

#define INVENTORY_SIZE 10

Inventory::Inventory() : ItemContainer(INVENTORY_SIZE) {
	selectionIndex = 0;
}
void Inventory::up() {
	selectionIndex--;
	if (selectionIndex < 0) selectionIndex += getSize();
}
void Inventory::down() {
	selectionIndex++;
	if (selectionIndex >= getSize()) selectionIndex -= getSize();
}
ItemStack* Inventory::getSelected() {
	return get(selectionIndex);
}
int Inventory::getSelectionIndex() {
	return selectionIndex;
}