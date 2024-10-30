#ifndef NOISE_H
#define NOISE_H
#endif

class Perlin {
public:
	float sample(float, float);
	Perlin(int);
	~Perlin();
private:
	int* shuffle;
};

#pragma once