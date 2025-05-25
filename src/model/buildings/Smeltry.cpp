#include "Smeltry.h"
#include <stdio.h>

Recipe** recipeslist = nullptr;
int recipeTotal = 5;
Smeltry::Smeltry() : Crafter::Crafter(recipeTotal,Smeltry::recipes()) {

}
Smeltry::~Smeltry() {

}

Recipe** Smeltry::recipes() {
	printf("Called recipes\n");
	if (!recipeslist) {
		recipeslist = new Recipe*[recipeTotal];

		ItemID* b = new ItemID[2];
		int* bq = new int[2];
		b[0] = COPPER_ORE; bq[0] = 4;
		b[1] = TIN_ORE; bq[1] = 1;

		recipeslist[0] = new Recipe(COPPER_ORE,5,COPPER_INGOT,1,"-Copper Ore > Ingot");
		recipeslist[1] = new Recipe(TIN_ORE, 5, TIN_INGOT, 1, "-Tin Ore > Ingot");
		recipeslist[2] = new Recipe(2, b, bq, BRONZE_INGOT, 1, "-Bronze Ingot");
		recipeslist[3] = new Recipe(IRON_ORE, 5, IRON_INGOT, 1, "-Iron Ore > Ingot");
		recipeslist[4] = new Recipe(GOLD_ORE, 5, GOLD_INGOT, 1, "-Gold Ore > Ingot");
		for (int i = 0; i < recipeTotal; i++) {
			printf("%d. %s\n", i + 1, recipeslist[i]->name);
		}
	}
	return recipeslist;
}
int Smeltry::getTextureIndex() {
	return 7;
}
char Smeltry::getID() {
	return 'O';
}
float Smeltry::buildingEffort() {
	return 1.0f;
}