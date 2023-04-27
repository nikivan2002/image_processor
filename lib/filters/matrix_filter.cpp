#include "matrix_filter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<float>> matrix) : matrix_(matrix) {
}

std::vector<std::vector<UnboundedColor>> MatrixFilter::ApplyMatrix(const Image& image) const {
    std::vector<std::vector<UnboundedColor>> unbounded_pixels(image.GetHeight(),
                                                              std::vector<UnboundedColor>(image.GetWidth()));
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            for (size_t dy = 0; dy < 3; ++dy) {
                for (size_t dx = 0; dx < 3; ++dx) {
                    size_t true_y = (y + dy < 1) ? 1 : (y + dy > image.GetHeight()) ? image.GetHeight() : y + dy;
                    size_t true_x = (x + dx < 1) ? 1 : (x + dx > image.GetWidth()) ? image.GetWidth() : x + dx;
                    UnboundedColor c(image.GetPixel(true_y - 1, true_x - 1));
                    unbounded_pixels[y][x].red += matrix_[dy][dx] * c.red;
                    unbounded_pixels[y][x].green += matrix_[dy][dx] * c.green;
                    unbounded_pixels[y][x].blue += matrix_[dy][dx] * c.blue;
                }
            }
        }
    }
    return unbounded_pixels;
}

Image MatrixFilter::ConstApply(const Image& image) const {
    std::vector<std::vector<UnboundedColor>> unbounded_pixels(ApplyMatrix(image));
    std::vector<std::vector<Color>> pixels;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        pixels.emplace_back();
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            pixels[y].push_back(Color(unbounded_pixels[y][x]));
        }
    }
    return Image(pixels, image.GetHeight(), image.GetWidth());
}

void MatrixFilter::Apply(Image& image) const {
    image = MatrixFilter::ConstApply(image);
}