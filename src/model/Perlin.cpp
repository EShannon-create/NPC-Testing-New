#include <math.h>
#include <random>
#include "Perlin.h"

float lerp(float, float, float);
float fade(float);
float grad(int, float, float);

Perlin::Perlin(int seed) {
	srand(seed);
	shuffle = new int[512];
	for (int i = 0; i < 256; i++) {
		shuffle[i] = i;
	}
	for (int i = 0; i < 256; i++) {
		int r = rand() % 256;
		int s = shuffle[i];
		shuffle[i] = shuffle[r];
		shuffle[i + 256] = shuffle[r];
		shuffle[r] = s;
		shuffle[r + 256] = s;
	}
}

Perlin::~Perlin() {
	delete[] shuffle;
}

float Perlin::sample(float x, float y) {
	float nx = fmodf(x, 1);
	float ny = fmodf(y, 1);
	int ix = (int)x & 255;
	int iy = (int)y & 255;
	float u = fade(nx);
	float v = fade(ny);

	int aa = shuffle[shuffle[ix] + iy];
	int ab = shuffle[shuffle[ix + 1] + iy];
	int ba = shuffle[shuffle[ix] + iy + 1];
	int bb = shuffle[shuffle[ix + 1] + iy + 1];

	float x1 = lerp(grad(aa, nx, ny), grad(ab, nx - 1, ny), u);
	float x2 = lerp(grad(ba, nx, ny - 1), grad(bb, nx - 1, ny - 1), u);

	return lerp(x1, x2, v);
}
float lerp(float a, float b, float x) {
	return a + x * (b - a);
}
float fade(float val) {
	return val * val * val * (val * (val * 6 - 15) + 10);
}
float grad(int hash, float x, float y) {
	switch (hash & 7) {
	case 0: return x + y;
	case 1: return x - y;
	case 2: return -x + y;
	case 3: return -x - y;
	case 4: return x;
	case 5: return y;
	case 6: return -x;
	case 7: return -y;
	}
}