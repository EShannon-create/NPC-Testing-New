#ifndef BUILDING_H
#define BUILDING_H

class Building {
public:
	Building();
	~Building();
	void construct(float);
	bool isComplete();
private:
	float completion;
};

#endif