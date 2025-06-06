#include "ItemContainer.h"

ItemContainer::ItemContainer(int size) : size(size) {
	items = new ItemStack*[size];
	for (int i = 0; i < size; i++) {
		items[i] = nullptr;
	}
}
ItemContainer::~ItemContainer() {
	for (int i = 0; i < size; i++) {
		delete items[i];
	}
	delete[] items;
}
ItemStack* ItemContainer::get(int index) {
	return items[index % size];
}
ItemStack* ItemContainer::pop(int index) {
	ItemStack* item = get(index);
	items[index % size] = nullptr;
	return item;
}
bool ItemContainer::addAtIndex(ItemStack* item, int index) {
	if (items[index] == nullptr) {
		items[index] = item;
		return true;
	}
	if (ItemStack::combine(items[index], item)) return true;
	return false;
}
bool ItemContainer::add(ItemStack* item) {
	for (int i = 0; i < size; i++) {
		if (addAtIndex(item, i)) return true;
	}
	return false;
}
bool ItemContainer::move(ItemContainer* from, int index, ItemContainer* to) {
	ItemStack* item = from->pop(index);
	if (item == nullptr) return false;
	if (to->add(item)) return true;
	from->addAtIndex(item, index);//should always work and return true unless something's gone horribly wrong :)
	return false;
}
void ItemContainer::collapse() {//Probably needs testing

	//

	for (int i = 0; i < size; i++) {
		ItemStack* to = items[i];
		for (int j = i + 1; j < size; j++) {
			ItemStack* from = items[j];
			if (ItemStack::combine(to, from)) items[j] = nullptr;
		}
	}

	//
}
int ItemContainer::getSize() {
	return size;
}
bool ItemContainer::take(ItemID id, int q) {
	int hasTaken = 0;
	for (int i = 0; i < size; i++) {
		if (id != items[i]->getID()) continue;

		if (items[i]->getQuantity() > q - hasTaken) {
			items[i]->decrease(q - hasTaken);
			return true;
		}
		else {
			int qua = items[i]->getQuantity();

			delete items[i];
			items[i] = nullptr;

			if (qua == q - hasTaken) return true;
			else hasTaken += qua;
		}
	}
	return false;
}