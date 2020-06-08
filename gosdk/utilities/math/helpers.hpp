#pragma once

#include "matrix3x4.hpp"
#include "vector2d.hpp"
#include "vector3d.hpp"

namespace Helpers::Math {
  inline void TransformVector( Utils::Math::Vector & a, const Utils::Math::Matrix3x4 & b, Utils::Math::Vector & out ) {
    out.m_X = a.m_Dot( b.m_Values[ 0 ] ) + b.m_Values[ 0 ][ 3 ];
    out.m_Y = a.m_Dot( b.m_Values[ 1 ] ) + b.m_Values[ 1 ][ 3 ];
    out.m_Z = a.m_Dot( b.m_Values[ 2 ] ) + b.m_Values[ 2 ][ 3 ];
  }
} // namespace Helpers::Math