#include "Mine.h"

#define MINE_AREA 5
#define MINING_AMOUNT 0.0025
#define AMOUNT_PER_ORE 0.002

Mine::Mine(Tile*** area) {
	tiles = area;
}
Mine::~Mine() {
	for (int i = 0; i < MINE_AREA; i++) delete tiles[i];
	delete tiles;
}
bool Mine::mine(ItemContainer* ic) {
	float minerals[] = { 0.f,0.f,0.f,0.f,0.f };
	for (int i = 0; i < MINE_AREA; i++) for (int j = 0; j < MINE_AREA; j++) {
		for (int mineral = 0; mineral < 5; mineral++) {
			minerals[mineral] += tiles[i][j]->mine(mineral,MINING_AMOUNT);
		}
	}
	bool tr = false;
	for (int mineral = 0; mineral < 5; mineral++) {
		int quantity = (int)(minerals[mineral] / AMOUNT_PER_ORE);
		if (quantity < 1) continue;
		ItemID id;
		switch (mineral) {
		case 0: id = COAL; break;
		case 1: id = IRON_ORE; break;
		case 2: id = COPPER_ORE; break;
		case 3: id = TIN_ORE; break;
		case 4: id = GOLD_ORE; break;
		default: continue;
		}
		ItemStack* item = ItemStack::create(id, quantity);
		if (!ic->add(item)) return tr;
		else tr = true;
	}
	return tr;
}
int Mine::getTextureIndex() {
	if (isComplete()) return 4;
	return 0;
}
char Mine::getID() {
	return 'M';
}