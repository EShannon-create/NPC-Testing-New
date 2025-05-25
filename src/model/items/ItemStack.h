#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#define MAX_QUANTITY 64

enum ItemID {
	MANGO, STICK, WATERMELON_SEED, WATERMELON_SLICE, COAL,
	IRON_ORE, GOLD_ORE, TIN_ORE, COPPER_ORE,
	IRON_INGOT,GOLD_INGOT,TIN_INGOT,COPPER_INGOT,BRONZE_INGOT
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
	const static char* getItemName(ItemID);
private:
	int quantity;
	ItemID id;
	static int getCalories(ItemID);
	ItemStack(ItemID, int);
};

#endif