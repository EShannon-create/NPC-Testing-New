#include "Octave.h"


Octave::Octave(int seed, float scale) : scale(scale){
	perlins = new Perlin * [DEPTH];
	for (int i = 0; i < DEPTH; i++) {
		perlins[i] = new Perlin(seed + i);
	}
}
Octave::~Octave() {
	for (int i = 0; i < DEPTH; i++) {
		delete perlins[i];
	}
	delete[] perlins;
}
float Octave::sample(float x, float y) {
	float sum = 0;
	int by = 1;
	for (int i = 0; i < DEPTH; i++) {
		by *= 2;
		sum += perlins[i]->sample(x*by/scale, y*by/scale) / by;
	}
	return sum;
}