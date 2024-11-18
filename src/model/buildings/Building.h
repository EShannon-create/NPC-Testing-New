#ifndef BUILDING_H
#define BUILDING_H

#include "raylib.h"

class Building {
public:
	Building();
	~Building();
	void construct(float);
	bool isComplete();
	virtual int getTextureIndex();
	virtual char getID();
private:
	float completion;
};

#endif