#pragma once

#include "filter.h"

const float RED_SHARE = .299;
const float GREEN_SHARE = .587;
const float BLUE_SHARE = .114;

class GrayScale : public Filter {
public:
    GrayScale();

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;
};
