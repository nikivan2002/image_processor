#include "image.h"

Image::Image(const std::vector<std::vector<Color>>& pixels, size_t height, size_t width)
    : pixels_(pixels), height_(height), width_(width) {
}

size_t Image::GetHeight() const {
    return height_;
}
void Image::SetHeight(size_t height) {
    pixels_.resize(height);
    for (size_t i = height_; i < height_; ++i) {
        pixels_[i].resize(width_);
    }
    height_ = height;
}
size_t Image::GetWidth() const {
    return width_;
}
void Image::SetWidth(size_t width) {
    for (size_t i = 0; i < height_; ++i) {
        pixels_[i].resize(width);
    }
    width_ = width;
}
Color Image::GetPixel(size_t y, size_t x) const {
    return pixels_[y][x];
}
void Image::SetPixel(size_t y, size_t x, Color c) {
    pixels_[y][x] = c;
}
