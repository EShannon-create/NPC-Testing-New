#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#define MAX_QUANTITY 64

enum ItemID {
	MANGO, STICK, WATERMELON_SEED, WATERMELON_SLICE
};

class ItemStack {
public:
	ItemStack(ItemID);
	~ItemStack();
	int getQuantity();
	char* getName();
	int getCalories();
	bool isFood();
	static bool combine(ItemStack*, ItemStack*);
	static bool sameItem(ItemStack*, ItemStack*);
	static ItemStack* create(ItemID, int);
	ItemStack* split(int);
	bool decrease(int);
	ItemID getID();
private:
	int quantity;
	ItemID id;
	const static char* getItemName(ItemID);
	static int getCalories(ItemID);
	ItemStack(ItemID, int);
};

#endif