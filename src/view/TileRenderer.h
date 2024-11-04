#ifndef TILERENDERER_H
#define TILERENDERER_H

#include "raylib.h"
#include "resource_dir.h"
#include "model/World.h"

void InitializeTextures();
void UninitializeTextures();
void DrawTiles(int,int,int,int,World*);
void DrawEntities(int, int, int, int, Person**, int);

#endif
#pragma once
