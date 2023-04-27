#include "hues.h"

Hues::Hues() {
}

void Hues::Apply(Image& image) const {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            UnboundedColor c = UnboundedColor(image.GetPixel(i, j));
            if (c.red == c.green && c.green == c.blue) {
                image.SetPixel(i, j, Color(0, 0, 0));
            } else {
                float offset = std::min(std::min(c.red, c.green), c.blue);
                c.red -= offset;
                c.green -= offset;
                c.blue -= offset;
                if (c.red >= c.green && c.red >= c.blue) {
                    c.green *= (FULL_UNBOUNDED_COLOR / c.red);
                    c.blue *= (FULL_UNBOUNDED_COLOR / c.red);
                    c.red = FULL_UNBOUNDED_COLOR;
                } else if (c.green >= c.blue) {
                    c.red *= (FULL_UNBOUNDED_COLOR / c.green);
                    c.blue *= (FULL_UNBOUNDED_COLOR / c.green);
                    c.green = FULL_UNBOUNDED_COLOR;
                } else {
                    c.red *= (FULL_UNBOUNDED_COLOR / c.blue);
                    c.green *= (FULL_UNBOUNDED_COLOR / c.blue);
                    c.blue = FULL_UNBOUNDED_COLOR;
                }
                image.SetPixel(i, j, Color(c));
            }
        }
    }
}

Image Hues::ConstApply(const Image& image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
