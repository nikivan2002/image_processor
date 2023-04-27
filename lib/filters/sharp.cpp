#include "sharp.h"

const std::vector<std::vector<float>> SHARP_MATRIX = {{0., -1., 0.}, {-1., 5., -1.}, {0., -1., 0.}};

Sharpening::Sharpening() : MatrixFilter(SHARP_MATRIX) {
}
