#pragma once

#include "matrix3x4.hpp"
#include "vector2d.hpp"
#include "vector3d.hpp"

namespace Helpers::Math {
  inline constexpr static double M_PI = 3.14159265358979323846;
  inline constexpr static float M_RADPI = 57.295779513082f;
  inline constexpr static float M_PI_F = static_cast<float>( M_PI );
  inline constexpr float RAD2DEG( const float x ) { return x * ( 180.f / M_PI_F ); }
  inline constexpr float DEG2RAD( const float x ) { return x * ( M_PI_F / 180.f ); }

  inline void TransformVector( Utils::Math::Vector & a, const Utils::Math::Matrix3x4 & b, Utils::Math::Vector & out ) {
    out.m_X = a.m_Dot( b.m_Values[ 0 ] ) + b.m_Values[ 0 ][ 3 ];
    out.m_Y = a.m_Dot( b.m_Values[ 1 ] ) + b.m_Values[ 1 ][ 3 ];
    out.m_Z = a.m_Dot( b.m_Values[ 2 ] ) + b.m_Values[ 2 ][ 3 ];
  }
} // namespace Helpers::Math