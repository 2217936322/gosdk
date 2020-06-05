#pragma once

#include <cmath>
#include <inttypes.h>

// credits: csgo_modest
namespace Utils::Math {
  template <typename T> struct Vector2D {
    T m_X, m_Y;
    Vector2D( ) = default;

    Vector2D( T xy ) : m_X( xy ), m_Y( xy ){ };
    Vector2D( T x, T y ) : m_X( x ), m_Y( y ){ };
    Vector2D( T x, T y, T z ) : m_X( x ), m_Y( y ){ };

    inline constexpr T m_Length( ) { return std::sqrt( m_X * m_X + m_Y * m_Y ); }

    inline constexpr bool m_bIsZero( ) { return m_X == 0 && m_Y == 0; }

    inline Vector2D & operator=( const Vector2D & in ) {
      m_X = in.m_X;
      m_Y = in.m_Y;

      return *this;
    }

    inline bool operator!=( const Vector2D & in ) { return ( m_X != in.m_X || m_Y != in.m_Y ); }

    inline bool operator==( const Vector2D & in ) { return ( m_X == in.m_X && m_Y == in.m_Y ); }

    inline constexpr Vector2D operator+( Vector2D in ) { return Vector2D( m_X + in.m_X, m_Y + in.m_Y ); }

    inline constexpr Vector2D operator+( T in ) { return Vector2D( m_X + in, m_Y + in ); }

    inline Vector2D & operator+=( Vector2D in ) {
      m_X += in.m_X;
      m_Y += in.m_Y;

      return *this;
    }

    inline Vector2D & operator+=( T in ) {
      m_X += in;
      m_Y += in;

      return *this;
    }

    inline constexpr Vector2D operator-( Vector2D in ) { return Vector2D( m_X - in.m_X, m_Y - in.m_Y ); }

    inline constexpr Vector2D operator-( T in ) { return Vector2D( m_X - in, m_Y - in ); }

    inline Vector2D & operator-=( Vector2D in ) {
      m_X -= in.m_X;
      m_Y -= in.m_Y;

      return *this;
    }

    inline Vector2D & operator-=( T in ) {
      m_X -= in;
      m_Y -= in;

      return *this;
    }

    inline constexpr Vector2D operator*( Vector2D in ) { return Vector2D( m_X * in.m_X, m_Y * in.m_Y ); }

    inline constexpr Vector2D operator*( T in ) { return Vector2D( m_X * in, m_Y * in ); }

    inline Vector2D & operator*=( Vector2D in ) {
      m_X *= in.m_X;
      m_Y *= in.m_Y;

      return *this;
    }

    inline Vector2D & operator*=( T in ) {
      m_X *= in;
      m_Y *= in;

      return *this;
    }

    inline constexpr Vector2D operator/( Vector2D in ) { return Vector2D( m_X / in.m_X, m_Y / in.m_Y ); }

    inline constexpr Vector2D operator/( T in ) { return Vector2D( m_X / in, m_Y / in ); }

    inline Vector2D & operator/=( Vector2D in ) {
      m_X /= in.m_X;
      m_Y /= in.m_Y;

      return *this;
    }

    inline Vector2D & operator/=( T in ) {
      m_X /= in;
      m_Y /= in;

      return *this;
    }
  };
  using Vector2 = Vector2D<float>;
} // namespace Utils::Math