#include "gs.h"

GrayScale::GrayScale() {
}

void GrayScale::Apply(Image& image) const {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            UnboundedColor c(image.GetPixel(i, j));
            float gray_value = RED_SHARE * c.red + GREEN_SHARE * c.green + BLUE_SHARE * c.blue;
            image.SetPixel(i, j, Color(UnboundedColor(gray_value, gray_value, gray_value)));
        }
    }
}

Image GrayScale::ConstApply(const Image& image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
