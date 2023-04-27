#include "color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {
}

Color::Color(const UnboundedColor &c) {
    red = (c.red < 0.) ? 0 : (c.red > FULL_UNBOUNDED_COLOR) ? FULL_COLOR : static_cast<uint8_t>(c.red);
    green = (c.green < 0.) ? 0 : (c.green > FULL_UNBOUNDED_COLOR) ? FULL_COLOR : static_cast<uint8_t>(c.green);
    blue = (c.blue < 0.) ? 0 : (c.blue > FULL_UNBOUNDED_COLOR) ? FULL_COLOR : static_cast<uint8_t>(c.blue);
}

bool Color::operator==(const Color &other) const {
    return red == other.red && green == other.green && blue == other.blue;
}

bool Color::operator!=(const Color &other) const {
    return !(*this == other);
}

UnboundedColor::UnboundedColor(float red, float green, float blue) : red(red), green(green), blue(blue) {
}

UnboundedColor::UnboundedColor(const Color &c) {
    red = static_cast<float>(c.red);
    green = static_cast<float>(c.green);
    blue = static_cast<float>(c.blue);
}

bool UnboundedColor::operator==(const UnboundedColor &other) const {
    return red == other.red && green == other.green && blue == other.blue;
}

bool UnboundedColor::operator!=(const UnboundedColor &other) const {
    return !(*this == other);
}
