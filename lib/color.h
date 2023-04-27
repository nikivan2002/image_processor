#pragma once

#include <cstdint>

static const uint8_t FULL_COLOR = 255;
static const float FULL_UNBOUNDED_COLOR = 255.;

class UnboundedColor;

class Color {
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    explicit Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

    explicit Color(const UnboundedColor& c);

    bool operator==(const Color& other) const;

    bool operator!=(const Color& other) const;
};

class UnboundedColor {
public:
    float red{0.};
    float green{0.};
    float blue{0.};

    explicit UnboundedColor(float red = 0., float green = 0., float blue = 0.);

    explicit UnboundedColor(const Color& c);

    bool operator==(const UnboundedColor& other) const;

    bool operator!=(const UnboundedColor& other) const;
};