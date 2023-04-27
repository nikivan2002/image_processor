#include "neg.h"

Negative::Negative() {
}

void Negative::Apply(Image& image) const {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color c = image.GetPixel(i, j);
            image.SetPixel(i, j, Color(FULL_COLOR - c.red, FULL_COLOR - c.green, FULL_COLOR - c.blue));
        }
    }
}

Image Negative::ConstApply(const Image& image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
