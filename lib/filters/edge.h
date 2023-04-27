#pragma once

#include "matrix_filter.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(size_t threshold);

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;

private:
    uint8_t threshold_;
};
