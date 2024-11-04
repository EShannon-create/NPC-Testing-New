#ifndef TILE_H
#define TILE_H

class Tile {
public:
	Tile(float, float);
	~Tile();
	bool isLand();
	bool isWater();
	float getWildGrowth();
	void updateGrowth(Tile*, Tile*, Tile*, Tile*, int);
	int fertilityGrade();
	int growthGrade();
	void setWildGrowth(float);
private:
	float height;
	float fertility;
	float wildGrowth;
};

#endif
