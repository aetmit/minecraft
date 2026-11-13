#pragma once

#include <glm/glm.hpp>

#include <cstdint>

namespace engine {

/// @class Color
/// @brief Color
///
/// Color class stores color in RGBA form, two forms are
/// available for passing and extracting color information:
/// RGBA or HEX.
///
/// The data in color consists of four components:
/// - R (Red channel)
/// - G (Green channel)
/// - B (Blue channel)
/// - A (Alpha or Transparency channel)
class Color {
public:
    // Class members

    std::uint8_t r{};  //!< Red channel value.
    std::uint8_t g{};  //!< Green channel value.
    std::uint8_t b{};  //!< Blue channel value.
    std::uint8_t a{};  //!< Alpha channel value.

    // Constructors

    /// @brief Default constructor.
    Color() = default;

    /// @brief Color constructor using RGBA.
    ///
    /// @param red Red channel value.
    /// @param green Green channel value.
    /// @param blue Blue channel value.
    /// @param alpha Alpha channel value.
    constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) :
        r(red),
        g(green),
        b(blue),
        a(alpha)
    {
    }

    /// @brief Color constructor using HEX.
    ///
    /// @param color HEX color value.
    constexpr Color(std::uint32_t color) :
        r(static_cast<std::uint8_t>((color & 0xff'00'00'00) >> 24)),
        g(static_cast<std::uint8_t>((color & 0x00'ff'00'00) >> 16)),
        b(static_cast<std::uint8_t>((color & 0x00'00'ff'00) >> 8)),
        a(static_cast<std::uint8_t>((color & 0x00'00'00'ff) >> 0))
    {
    }

    /// @brief Set a new color at once.
    ///
    /// @param red Red channel value.
    /// @param green Green channel value.
    /// @param blue Blue channel value.
    /// @param alpha Alpha channel value.
    void set(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);

    /// @brief Set a new color at once
    ///
    /// @param color HEX color value.
    void set(std::uint32_t color);

    /// @brief Retrieve the color as a 32-bit unsigned integer.
    ///
    /// @return Color in 32-bit unsigned integer form.
    [[nodiscard]]
    std::uint32_t toInt() const;

    /// @brief Normalize color within the range of `0.0, 1.0`.
    ///
    /// @return Color normalized within the range of `0.0, 1.0`.
    [[nodiscard]]
    glm::vec4 normalize() const;

    /// @brief Invert color.
    ///
    /// @return Inverted color.
    [[nodiscard]]
    Color invert() const;

    /// @brief Constrast color compared to `*this`.
    ///
    /// @return Either black or white that has the most contrast compared to `*this`.
    [[nodiscard]]
    Color contrast() const;

    // Preset colors.
    static const Color Black;   //!< Predefined black color
    static const Color Silver;  //!< Predefined silver color
    static const Color Gray;    //!< Predefined gray color
    static const Color White;   //!< Predefined white color
    static const Color Maroon;  //!< Predefined maroon color
    static const Color Red;     //!< Predefined red color
    static const Color Purple;  //!< Predefined purple color
    static const Color Fuchsia; //!< Predefined fuchsia color
    static const Color Green;   //!< Predefined green color
    static const Color Lime;    //!< Predefined lime color
    static const Color Olive;   //!< Predefined olive color
    static const Color Yellow;  //!< Predefined yellow color
    static const Color Navy;    //!< Predefined navy color
    static const Color Blue;    //!< Predefined blue color
    static const Color Teal;    //!< Predefined teal color
    static const Color Aqua;    //!< Predefined Aqua color
};

// Preset colors

inline constexpr Color Color::Black(0, 0, 0);
inline constexpr Color Color::Silver(192, 192, 192);
inline constexpr Color Color::Gray(128, 128, 128);
inline constexpr Color Color::White(255, 255, 255);
inline constexpr Color Color::Maroon(128, 0, 0);
inline constexpr Color Color::Red(255, 0, 0);
inline constexpr Color Color::Purple(128, 0, 128);
inline constexpr Color Color::Fuchsia(255, 0, 255);
inline constexpr Color Color::Green(0, 255, 0);
inline constexpr Color Color::Lime(0, 220, 0);
inline constexpr Color Color::Olive(128, 128, 0);
inline constexpr Color Color::Yellow(255, 255, 0);
inline constexpr Color Color::Navy(0, 0, 128);
inline constexpr Color Color::Blue(0, 0, 255);
inline constexpr Color Color::Teal(0, 128, 128);
inline constexpr Color Color::Aqua(0, 255, 255);

// Operators

/// @relates Color
/// @brief Equality
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return `true` if `left` is equal to `right`.
bool operator==(const Color left, const Color right);

/// @relates Color
/// @brief Inequality
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return `true` if `left` is not equal to `right`.
bool operator!=(const Color left, const Color right);

/// @relates Color
/// @brief Addition
///
/// Color channel value will be clamped to 255 if the
/// addition causes overflow in the color channel.
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Member-wise addition of both colors.
Color operator+(Color left, Color right);

/// @relates Color
/// @brief Subtraction
///
/// Color channel value will be clamped to 0 if the
/// subtraction causes underflow in the color channel.
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Member-wise subtraction of both colors.
Color operator-(Color left, Color right);

/// @relates Color
/// @brief Multiplication
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Memeber-wise multiplication of both colors.
Color operator*(Color left, Color right);

/// @relates Color
/// @brief Addition assignment
///
/// Color channel value will be clamped to 255 if the
/// addition causes overflow in the color channel.
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Reference to `left`.
Color& operator+=(Color& left, Color right);

/// @relates Color
/// @brief Subtraction assignment
///
/// Color channel value will be clamped to 0 if the
/// subtraction causes underflow in the color channel.
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Reference to `left`.
Color& operator-=(Color& left, Color right);

/// @relates Color
/// @brief Multiplication assignment
///
/// @param left Left operand.
/// @param right Right operand.
///
/// @return Reference to `left`.
Color& operator*=(Color& left, Color right);

/// @relates Color
/// @brief Prefix increment
///
/// Color channel value will be clamped to 255 if the
/// increment overflows the color channel.
///
/// @param color Color to increase.
///
/// @return Reference to `color`.
Color& operator++(Color& color);

/// @relates Color
/// @brief Postfix increment
///
/// Color channel value will be clamped to 255 if the
/// increment overflows the color channel.
///
/// @param color Color to increase.
///
/// @return Unmodified `color` value.
Color operator++(Color& color, int);

/// @relates Color
/// @brief Prefix decrement
///
/// Color channel value will be clamped to 0 if the
/// decrement underflows the color channel.
///
/// @param color Color to decrease.
///
/// @return Reference to `color`.
Color& operator--(Color& color);

/// @relates Color
/// @brief Postfix decrement
///
/// Color channel value will be clamped to 0 if the
/// decrement underflows the color channel.
///
/// @param color Color to decrease.
///
/// @return Unmodified `color` value.
Color operator--(Color& color, int);

}  // namespace engine
