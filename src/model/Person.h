#ifndef CHUDDIE_PERSON_H
#define CHUDDIE_PERSON_H

class Person {
public:
	Person();
	Person(int, int);
	~Person();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int getX();
	int getY();
private:
	int x;
	int y;
};

#endif
