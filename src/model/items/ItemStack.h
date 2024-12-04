#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#define MAX_QUANTITY 64

enum ItemID {
	MANGO, STICK
};

class ItemStack {
public:
	ItemStack(ItemID);
	~ItemStack();
	int getQuantity();
	char* getName();
	static bool combine(ItemStack*, ItemStack*);
	static bool sameItem(ItemStack*, ItemStack*);
	static ItemStack* create(ItemID, int);
private:
	int quantity;
	ItemID id;
	const static char* getItemName(ItemID);
	ItemStack(ItemID, int);
};

#endif