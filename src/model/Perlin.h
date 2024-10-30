#ifndef NOISE_H
#define NOISE_H

class Perlin {
public:
	float sample(float, float);
	Perlin(int);
	~Perlin();
private:
	int* shuffle;
};

#endif
#pragma once