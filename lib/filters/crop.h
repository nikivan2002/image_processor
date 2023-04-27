#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;

private:
    size_t height_;
    size_t width_;
};
