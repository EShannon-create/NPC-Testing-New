#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#define MAX_QUANTITY 64

enum ItemID {
	MANGO, STICK
};

class ItemStack {
public:
	ItemStack(ItemID);
	ItemStack(ItemID, int);
	~ItemStack();
	int getQuantity();
	char* getName();
	static bool combine(ItemStack*, ItemStack*);
	static bool sameItem(ItemStack*, ItemStack*);
private:
	int quantity;
	ItemID id;
	const static char* getItemName(ItemID);
};

#endif