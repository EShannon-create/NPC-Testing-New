#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#define MAX_QUANTITY 64

#include "model/crops/Crop.h"

enum ItemID {
	MANGO, STICK, WHEAT_SEED
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
	//Crop* getCrop();
private:
	int quantity;
	ItemID id;
	const static char* getItemName(ItemID);
	static int getCalories(ItemID);
	//static Crop* getCrop(ItemID);
	ItemStack(ItemID, int);
};

#endif