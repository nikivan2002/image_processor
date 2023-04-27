#pragma once

#include "filter.h"

class Negative : public Filter {
public:
    Negative();

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;
};
