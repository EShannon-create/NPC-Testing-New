#include "Recipe.h"

Recipe::Recipe(int size, ItemID* items, int* quantities, ItemID yields, int quantity, std::string name) : 
	items(items), quantities(quantities), name(name), yields(yields), quantity(quantity), ingredients(size) {

}
Recipe::Recipe(ItemID item, int quantityA, ItemID yields, int quantityB, std::string name) :
	Recipe(1, new ItemID(item), new int(quantityA), yields, quantityB, name)
{
}
Recipe::~Recipe() {
	delete items;
	delete quantities;
}
bool Recipe::craft(ItemContainer* ic) {
	return craft(ic, ic);
}
bool Recipe::craft(ItemContainer* from, ItemContainer* to) {
	if (!canCraft(from)) return false;

	for (int i = 0; i < ingredients; i++) {
		from->take(items[i], quantities[i]);
	}

	return to->add(ItemStack::create(yields,quantity));
}
bool Recipe::canCraft(ItemContainer* from) {
	for (int i = 0; i < ingredients; i++) {
		if (!itemOkay(from, i)) return false;
	}
	return true;
}
bool Recipe::itemOkay(ItemContainer* from, int index) {
	int has = 0;
	for (int i = 0; i < from->getSize(); i++) {
		if (from->get(i)->getID() == items[index]) has += from->get(i)->getQuantity();
		if (has >= quantities[index]) return true;
	}
	return false;
}