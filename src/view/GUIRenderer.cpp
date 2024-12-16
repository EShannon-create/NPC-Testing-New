#include "GUIRenderer.h"

void DrawGUI(Person* player) {
	if (player == nullptr) return;

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

	float healthbar = player->healthBar();
	float hungerbar = player->hungerBar();
	float staminabar = player->staminaBar();

	float x = GetScreenWidth() / 10;
	float y = GetScreenHeight() * 8 / 10;
	float width = GetScreenWidth() / 5;
	float height = GetScreenWidth() / 40;

	DrawRectangle(x, y, width * staminabar, height, GREEN);
	DrawRectangleLinesEx(Rectangle{x,y,width,height}, 2, WHITE);

	y -= GetScreenHeight() / 20;

	DrawRectangle(x, y, width * hungerbar, height, ORANGE);
	DrawRectangleLinesEx(Rectangle{ x,y,width,height }, 2, WHITE);

	y -= GetScreenHeight() / 20;

	DrawRectangle(x, y, width * healthbar, height, RED);
	DrawRectangleLinesEx(Rectangle{ x,y,width,height }, 2, WHITE);
}