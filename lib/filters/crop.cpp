#include "crop.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

void Crop::Apply(Image& image) const {
    if (image.GetHeight() > height_) {
        image.SetHeight(height_);
    }
    if (image.GetWidth() > width_) {
        image.SetWidth(width_);
    }
}

Image Crop::ConstApply(const Image& image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
