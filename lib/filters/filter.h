#pragma once

#include "../image.h"

class Filter {
public:
    virtual void Apply(Image& image) const = 0;

    virtual Image ConstApply(const Image& image) const = 0;

    virtual ~Filter(){};
};
