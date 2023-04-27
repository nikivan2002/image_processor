#pragma once

#include "filter.h"

class MatrixFilter : public Filter {
public:
    explicit MatrixFilter(const std::vector<std::vector<float>> matrix);

    std::vector<std::vector<UnboundedColor>> ApplyMatrix(const Image& image) const;

    void Apply(Image& image) const override;

    Image ConstApply(const Image& image) const override;

protected:
    const std::vector<std::vector<float>> matrix_;
};
