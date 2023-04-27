#pragma once

#include "filter.h"

class SeamCarving : public Filter {
public:
    SeamCarving(size_t height, size_t width);

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;

private:
    std::vector<std::vector<float>> EdgeMatrix(const Image& image) const;

    void CarveHor(Image& image) const;

    void CarveVert(Image& image) const;

    size_t height_;
    size_t width_;
};
