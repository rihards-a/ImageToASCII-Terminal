#include "header.h"
#include <cmath>

// returns the amount of pixels a single ASCII character will represent on the CLI
int* ResolutionResolver(double x, double y, const int MaxCLIImgSize[]) {
	int* res = new int[2];
	res[0] = std::ceil(x / MaxCLIImgSize[0]);
	res[1] = std::ceil(y / MaxCLIImgSize[1]);
	return res;
}

// returns the best matching symbol for the input brightness level
int CorrespondingSymbol(double brightness) {
	int i = 0;
	while (i < ascii_brightness.length() - 1) {
		if (std::abs(brightness - brightness_table[i]) < std::abs(brightness - brightness_table[i + 1])) return i;
		++i;
	}
	return i;
}
