#ifndef HOUSE_H
#define HOUSE_H

#include "Building.h"

class House : public Building {
public:
	House();
	~House();
	int getTextureIndex();
	char getID();
private:

};

#endif