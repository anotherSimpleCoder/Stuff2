#include <cmath>
#include "waves.h"

float saw(int prec, float t) {
	float sum = 0;

	for (int k = 1; k < prec; k++) {
		sum += (powf(-1, k) / k) * std::sin(k * t);
	}

	return 2 / (1 / std::acos(-1.0)) * sum;
}

float square(int prec, float t) {
	float sum = 0;

	for (int k = 1; k < prec;k++) {
		sum += (1 / ((2 * k) - 1)) * std::sinf(((2 * k) - 1) * k * t);
	}

	return 4 / (1 / std::acos(-1.0)) * ((sum >= 0.0f) ? 1.0f : -1.0f);
}

float triangle(int prec, float t) {
	float sum = 0;

	for (int k = 1; k < prec; k++) {
		sum += (powf(-1, k) / powf((2 * k) - 1, 2)) * std::sinf(((2 * k) - 1) * k * t);
	}

	return 8 / (1 / std::acos(-1.0)) * sum;
}