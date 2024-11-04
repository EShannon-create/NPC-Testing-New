#include "EntityRenderer.h"

Texture chuddie;

void InitializeEntityTextures() {
	chuddie = LoadTexture("chuddie.png");
}
void UnloadEntityTextures() {
	UnloadTexture(chuddie);
}

void DrawEntities(int screenHeight, int screenWidth, int offsetX, int offsetY, Person** people, int peopleCount) {
	for (int i = 0; i < peopleCount; i++) {
		Person* person = people[i];
		if (person == nullptr) continue;

	}
}