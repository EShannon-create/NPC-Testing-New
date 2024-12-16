#ifndef WORLD_H
#define WORLD_H

#include "Tile.h"
#include "Octave.h"

class World {
public:
	World(int,int);
	~World();
	Tile* getTile(int, int);
	void updateTiles(int,float);
	void updateClock(float);
	char* getTime();
	float getSunAngle();
	void analyze();
private:
	Tile** map;
	int width;
	int height;
	int updateIndex;
	double currentTime;
	int date;
	int month;
	int year;
	float calculateDropOff(float, float);
};

#endif
#pragma once
