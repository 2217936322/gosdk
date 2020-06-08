#pragma once

#include <cmath>
#include <inttypes.h>

// credits: csgo_modest
namespace Utils::Math {
  template <typename T> struct Vector3 {
    T m_X, m_Y, m_Z;

    Vector3( ) = default;

    Vector3( T xyz ) : m_X( xyz ), m_Y( xyz ), m_Z( xyz ){ };
    Vector3( T x, T y ) : m_X( x ), m_Y( y ), m_Z( 0 ){ };
    Vector3( T x, T y, T z ) : m_X( x ), m_Y( y ), m_Z( z ){ };

    inline constexpr T m_Length( ) { return std::sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z ); }

    inline constexpr T m_Length2D( ) {
      T root = 0.0f;

      T sqst = m_X * m_X + m_Y * m_Y;

      __asm
      {
				sqrtss xmm0, sqst
				movss root, xmm0
      }

      return root;
    }

    inline constexpr Vector3 m_Normalize( ) {
      Vector3 out{ };
      T l = m_Length( );

      if ( l != 0 ) {
        out.m_X = m_X / l;
        out.m_Y = m_Y / l;
        out.m_Z = m_Z / l;
      } else
        out.m_X = out.m_Y = 0.0f;
      out.m_Z = 1.0f;

      return out;
    }

    inline constexpr T m_SelfDot( ) { return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z ); }

    inline constexpr T m_Dot( const Vector3 & in ) { return ( m_X * in.m_X + m_Y * in.m_Y + m_Z * in.m_Z ); }

    inline constexpr T m_Dot( const float * other ) const {
      return this->m_X * other[ 0 ] + this->m_Y * other[ 1 ] + this->m_Z * other[ 2 ];
    }

    inline Vector3 & operator=( const Vector3 & in ) {
      m_X = in.m_X;
      m_Y = in.m_Y;
      m_Z = in.m_Z;

      return *this;
    }

    inline bool operator!=( const Vector3 & in ) { return ( m_X != in.m_X || m_Y != in.m_Y || m_Z != in.m_Z ); }

    inline bool operator==( const Vector3 & in ) { return ( m_X == in.m_X && m_Y == in.m_Y && m_Z == in.m_Z ); }

    inline constexpr Vector3 operator+( Vector3 in ) { return Vector3( m_X + in.m_X, m_Y + in.m_Y, m_Z + in.m_Z ); }

    inline constexpr Vector3 operator+( T in ) { return Vector3( m_X + in, m_Y + in, m_Z + in ); }

    inline Vector3 & operator+=( Vector3 in ) {
      m_X += in.m_X;
      m_Y += in.m_Y;
      m_Z += in.m_Z;

      return *this;
    }

    inline Vector3 & operator+=( T in ) {
      m_X += in;
      m_Y += in;
      m_Z += in;

      return *this;
    }

    inline constexpr Vector3 operator-( Vector3 in ) { return Vector3( m_X - in.m_X, m_Y - in.m_Y, m_Z - in.m_Z ); }

    inline constexpr Vector3 operator-( T in ) { return Vector3( m_X - in, m_Y - in, m_Z - in ); }

    inline Vector3 & operator-=( Vector3 in ) {
      m_X -= in.m_X;
      m_Y -= in.m_Y;
      m_Z -= in.m_Z;

      return *this;
    }

    inline Vector3 & operator-=( T in ) {
      m_X -= in;
      m_Y -= in;
      m_Z -= in;

      return *this;
    }

    inline constexpr Vector3 operator*( Vector3 in ) { return Vector3( m_X * in.m_X, m_Y * in.m_Y, m_Z * in.m_Z ); }

    inline constexpr Vector3 operator*( T in ) { return Vector3( m_X * in, m_Y * in, m_Z * in ); }

    inline Vector3 & operator*=( Vector3 in ) {
      m_X *= in.m_X;
      m_Y *= in.m_Y;
      m_Z *= in.m_Z;

      return *this;
    }

    inline Vector3 & operator*=( T in ) {
      m_X *= in;
      m_Y *= in;
      m_Z *= in;

      return *this;
    }

    inline constexpr Vector3 operator/( Vector3 in ) { return Vector3( m_X / in.m_X, m_Y / in.m_Y, m_Z / in.m_Z ); }

    inline constexpr Vector3 operator/( T in ) { return Vector3( m_X / in, m_Y / in, m_Z / in ); }

    inline Vector3 & operator/=( Vector3 in ) {
      m_X /= in.m_X;
      m_Y /= in.m_Y;
      m_Z /= in.m_Z;

      return *this;
    }

    inline Vector3 & operator/=( T in ) {
      m_X /= in;
      m_Y /= in;
      m_Z /= in;

      return *this;
    }
  };
  using Vector = Vector3<float>;
} // namespace Utils::Math