#include "ItemStack.h"


ItemStack::ItemStack(ItemID id) : ItemStack(id,1){

}
ItemStack::ItemStack(ItemID id, int quantity) : id(id), quantity(quantity) {

}
ItemStack::~ItemStack() {

}
int ItemStack::getQuantity() {
	return quantity;
}
bool ItemStack::sameItem(ItemStack* a, ItemStack* b) {
	return a->id == b->id;
}
bool ItemStack::combine(ItemStack* a, ItemStack* b) {
	if (!sameItem(a, b)) return false;

	int aq = a->getQuantity();
	int bq = b->getQuantity();
	
	if (aq + bq > MAX_QUANTITY) return false;
	a->quantity += b->quantity;
	delete b;
	return true;
}
char* ItemStack::getName() {
	char* n = getItemName(id);
	int j = 0;
	while (n[j] != '\0') j++;
	j++;

	char* name = new char[j];
	for (int k = 0; k < j; k++) name[k] = n[k];

	char a = getQuantity() / 10 + 48;
	char b = getQuantity() % 10 + 48;

	name[1] = a;
	name[2] = b;

	delete n;
	return name;
}
char* ItemStack::getItemName(ItemID id) {
	switch (id) {
	case MANGO: return " .. Mango\0";
	case STICK: return " .. Stick\0";
	default: return " .. NONE\0";
	}
}