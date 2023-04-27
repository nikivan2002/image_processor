#include "edge.h"
#include "gs.h"

const std::vector<std::vector<float>> EDGE_MATRIX = {{0., -1., 0.}, {-1., 4., -1.}, {0., -1., 0.}};

EdgeDetection::EdgeDetection(size_t threshold) : MatrixFilter(EDGE_MATRIX), threshold_(threshold) {
}

void EdgeDetection::Apply(Image &image) const {
    GrayScale().Apply(image);
    MatrixFilter::Apply(image);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            if (image.GetPixel(y, x).red >= threshold_) {
                image.SetPixel(y, x, Color(FULL_COLOR, FULL_COLOR, FULL_COLOR));
            } else {
                image.SetPixel(y, x, Color(0, 0, 0));
            }
        }
    }
}

Image EdgeDetection::ConstApply(const Image &image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
