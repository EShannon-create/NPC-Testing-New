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
	if (a == nullptr || b == nullptr) return false;
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
	const char* n = getItemName(id);
	int j = 0;
	while (n[j] != '\0') j++;
	j++;

	char* name = new char[j];
	for (int k = 0; k < j; k++) name[k] = n[k];

	if (j <= 3) return name;

	char a = getQuantity() / 10 + 48;
	char b = getQuantity() % 10 + 48;

	name[1] = a;
	name[2] = b;

	return name;
}
const char* ItemStack::getItemName(ItemID id) {
	switch (id) {
	case MANGO: return " .. Mango\0";
	case STICK: return " .. Stick\0";
	case WATERMELON_SEED: return " .. Watermelon Seed\0";
	case WATERMELON_SLICE: return " .. Watermelon Slice\0";
	case COAL: return " .. Coal\0";
	case IRON_ORE: return " .. Iron Ore\0";
	case GOLD_ORE: return " .. Gold Ore\0";
	case TIN_ORE: return " .. Tin Ore\0";
	case COPPER_ORE: return " .. Copper Ore\0";
	default: return " .. NONE\0";
	}
}
ItemStack* ItemStack::create(ItemID id, int quantity) {
	if (quantity <= 0) return nullptr;
	if (quantity > MAX_QUANTITY) return nullptr;
	return new ItemStack(id, quantity);
}
bool ItemStack::isFood() {
	return getCalories() > 0;
}
int ItemStack::getCalories() {
	return getCalories(id);
}
int ItemStack::getCalories(ItemID id) {
	switch (id) {
	case MANGO: return 80;
	case WATERMELON_SLICE: return 200;
	default: return 0;
	}
}
ItemStack* ItemStack::split(int quantity) {
	if (!decrease(quantity)) return nullptr;
	return create(id, quantity);
}
bool ItemStack::decrease(int quantity) {
	if (quantity >= getQuantity()) return false;

	this->quantity -= quantity;
	return true;
}
ItemID ItemStack::getID() {
	return id;
}