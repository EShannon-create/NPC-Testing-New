#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include "model/Person.h"
#include "raylib.h"
#include "resource_dir.h"

void InitializeEntityTextures();
void UnloadEntityTextures();
void DrawEntities(int, int, int, int, Person**, int);

#endif