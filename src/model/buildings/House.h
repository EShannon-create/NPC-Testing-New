#ifndef HOUSE_H
#define HOUSE_H

#include "Building.h"

class House : public Building {
public:
	House();
	~House();
	int getTextureIndex() override;
	char getID() override;
	bool canSleep();
protected:
	float buildingEffort() override;
private:

};

#endif