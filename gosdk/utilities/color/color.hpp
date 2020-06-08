#pragma once

#include <array>
#include <inttypes.h>

namespace Utils {
  class Color {
  public:
    std::uint8_t m_uRed, m_uGreen, m_uBlue, m_uAlpha;

    constexpr Color( ) noexcept : m_uRed( 0 ), m_uGreen( 0 ), m_uBlue( 0 ), m_uAlpha( 0 ) {}

    constexpr Color( const int r, const int g, const int b, const int a ) noexcept
        : m_uRed( r ), m_uGreen( g ), m_uBlue( b ), m_uAlpha( a ) {}

    constexpr Color( const int r, const int g, const int b ) noexcept
        : m_uRed( r ), m_uGreen( g ), m_uBlue( b ), m_uAlpha( 255 ) {}
  };
} // namespace Utils
