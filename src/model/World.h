#ifndef WORLD_H
#define WORLD_H

#include "Tile.h"
#include "Perlin.h"

class World {
public:
	World(int,int);
	~World();
	Tile* getTile(int, int);
	void updateTiles(int);
private:
	Tile** map;
	int width;
	int height;
	int updateIndex;
};

#endif
#pragma once
