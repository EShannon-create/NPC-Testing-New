#include "GUIRenderer.h"

void DrawGUI(Person* player) {
	Inventory* inventory = player->getInventory();

	int s = inventory->getSelectionIndex();

	for (int i = 0; i < inventory->getSize(); i++) {
		ItemStack* item = inventory->get(i);
		if (item == nullptr) {
			if(s == i) DrawText("*", GetScreenWidth() / 5 * 4, 25 + i * 25, 20, WHITE);
			else DrawText("-", GetScreenWidth() / 5 * 4, 25+i*25, 20, WHITE);
			continue;
		}

		char* txt = item->getName();
		if (s == i) txt[0] = '*';
		else txt[0] = '-';

		DrawText(txt, GetScreenWidth() / 5 * 4, 25+i*25, 20, WHITE);
		delete txt;
	}
}