#pragma once

#include "filter.h"

class Hues : public Filter {
public:
    Hues();

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;
};
