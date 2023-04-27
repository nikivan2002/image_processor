#pragma once

#include <vector>

#include "color.h"

class Image {
public:
    Image(const std::vector<std::vector<Color>>& pixels, size_t height, size_t width);
    size_t GetHeight() const;
    void SetHeight(size_t height);
    size_t GetWidth() const;
    void SetWidth(size_t width);
    Color GetPixel(size_t y, size_t x) const;
    void SetPixel(size_t y, size_t x, Color c);

private:
    std::vector<std::vector<Color>> pixels_;
    size_t height_;
    size_t width_;
};
