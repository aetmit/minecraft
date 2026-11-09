#include <core/color.hpp>

#include <glm/glm.hpp>

#include <cstdint>

namespace engine {

Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha)
{}

Color::Color(std::uint32_t color) :
    r(static_cast<std::uint8_t>((color & 0xff'00'00'00) >> 24)),
    g(static_cast<std::uint8_t>((color & 0x00'ff'00'00) >> 16)),
    b(static_cast<std::uint8_t>((color & 0x00'00'ff'00) >> 8)),
    a(static_cast<std::uint8_t>((color & 0x00'00'00'ff) >> 0))
{}

void Color::set(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Color::set(std::uint32_t color) {
    r = static_cast<std::uint8_t>((color & 0xff'00'00'00) >> 24);
    g = static_cast<std::uint8_t>((color & 0x00'ff'00'00) >> 16);
    b = static_cast<std::uint8_t>((color & 0x00'00'ff'00) >> 8);
    a = static_cast<std::uint8_t>((color & 0x00'00'00'ff) >> 0);
}

std::uint32_t Color::toInt() const {
    return static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | a);
}

glm::vec4 Color::normalize() const {
    return glm::vec4{
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        static_cast<float>(a) / 255.0f
    };
}

Color Color::invert() const {
    return {
        static_cast<std::uint8_t>(255u - r),
        static_cast<std::uint8_t>(255u - g),
        static_cast<std::uint8_t>(255u - b),
        static_cast<std::uint8_t>(255u - a)
    };
}

Color Color::contrast() const {
    // Data range always smaller or equal to 255.
    std::uint8_t luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    if (luminance > 150)
        return {0, 0, 0, a};
    else
        return {255, 255, 255, a};
}

// Preset colors

inline const Color Color::Black(0, 0, 0);
inline const Color Color::Silver(192, 192, 192);
inline const Color Color::Gray(128, 128, 128);
inline const Color Color::White(255, 255, 255);
inline const Color Color::Maroon(128, 0, 0);
inline const Color Color::Red(255, 0, 0);
inline const Color Color::Purple(128, 0, 128);
inline const Color Color::Fuchsia(255, 0, 255);
inline const Color Color::Green(0, 255, 0);
inline const Color Color::Lime(0, 220, 0);
inline const Color Color::Olive(128, 128, 0);
inline const Color Color::Yellow(255, 255, 0);
inline const Color Color::Navy(0, 0, 128);
inline const Color Color::Blue(0, 0, 255);
inline const Color Color::Teal(0, 128, 128);
inline const Color Color::Aqua(0, 255, 255);


// Color

// Color operations

bool operator==(Color left, Color right) {
    return (
        left.r == right.r
        && left.g == right.g
        && left.b == right.b
        && left.a == right.a
    );
}

bool operator!=(Color left, Color right) {
    return !(left == right);
}

Color operator+(Color left, Color right) {

    // Helper function for clamping overflown color value
    const auto addWrapped = [](std::uint8_t lhs, std::uint8_t rhs) {
        const std::uint16_t result = std::uint16_t{lhs} + std::uint16_t{rhs};
        return static_cast<std::uint8_t>(result < 255 ? result : 255);
    };
    return {
        addWrapped(left.r, right.r),
        addWrapped(left.g, right.g),
        addWrapped(left.b, right.b),
        addWrapped(left.a, right.a)
    };
}

Color operator-(Color left, Color right) {

    // Helper function for clamping underflown color value
    const auto subWrapped = [](std::uint8_t lhs, std::uint8_t rhs) {
        const std::int16_t result = std::int16_t{lhs} - std::int16_t{rhs};
        return static_cast<std::uint8_t>(result > 0 ? result : 0);
    };
    return {
        subWrapped(left.r, right.r),
        subWrapped(left.g, right.g),
        subWrapped(left.b, right.b),
        subWrapped(left.a, right.a)
    };
}

Color operator*(Color left, Color right) {
    const auto mulScaled = [](std::uint8_t lhs, std::uint8_t rhs) {
        const std::uint16_t result = std::uint16_t{lhs} * std::uint16_t{rhs};
        return static_cast<std::uint8_t>(result / 255u);
    };
    return {
        mulScaled(left.r, right.r),
        mulScaled(left.g, right.g),
        mulScaled(left.b, right.b),
        mulScaled(left.a, right.a)
    };
}

Color& operator+=(Color& left, Color right) {
    return left = left + right;
}

Color& operator-=(Color& left, Color right) {
    return left = left - right;
}

Color& operator*=(Color& left, Color right) {
    return left = left * right;
}

Color& operator++(Color& color) {
    return color = color + 1;
}

Color operator++(Color& color, int) {
    auto temp = color;
    ++color;
    return temp;
}

Color& operator--(Color& color) {
    return color = color - 1;
}

Color operator--(Color& color, int) {
    auto temp = color;
    --color;
    return temp;
}

}  // namespace engine
