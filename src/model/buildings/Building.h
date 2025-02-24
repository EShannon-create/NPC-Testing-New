#ifndef BUILDING_H
#define BUILDING_H

#include "raylib.h"

class Building {
public:
	Building();
	~Building();
	void construct(float);
	bool isComplete();
	virtual int getTextureIndex() = 0;
	virtual char getID() = 0;
	virtual bool canSleep();
protected:
	virtual float buildingEffort() = 0;
private:
	float completion;
};

#endif