#ifndef OCTAVE_H
#define OCTAVE_H

#include "Perlin.h"

#define DEPTH 8

class Octave {
public:
	Octave(int,float);
	~Octave();
	float sample(float, float);
private:
	Perlin** perlins;
	float scale;
};

#endif