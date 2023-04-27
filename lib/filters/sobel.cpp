#include "sobel.h"

const std::vector<std::vector<float>> SOBEL_Y_MATRIX = {{1., 2., 1.}, {0., 0., 0.}, {-1., -2., -1.}};
const std::vector<std::vector<float>> SOBEL_X_MATRIX = {{1., 0., -1.}, {2., 0., -2.}, {1., 0., -1.}};

SobelFilterY::SobelFilterY() : MatrixFilter(SOBEL_Y_MATRIX) {
}

SobelFilterX::SobelFilterX() : MatrixFilter(SOBEL_X_MATRIX) {
}
