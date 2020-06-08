#pragma once

#include "vector3d.hpp"
#include <algorithm>

namespace Utils::Math {
  struct Matrix3x4 {
    float m_Values[ 3 ][ 4 ];

    Matrix3x4( ) {
      m_Values[ 0 ][ 0 ] = 0.0f;
      m_Values[ 0 ][ 1 ] = 0.0f;
      m_Values[ 0 ][ 2 ] = 0.0f;
      m_Values[ 0 ][ 3 ] = 0.0f;
      m_Values[ 1 ][ 0 ] = 0.0f;
      m_Values[ 1 ][ 1 ] = 0.0f;
      m_Values[ 1 ][ 2 ] = 0.0f;
      m_Values[ 1 ][ 3 ] = 0.0f;
      m_Values[ 2 ][ 0 ] = 0.0f;
      m_Values[ 2 ][ 1 ] = 0.0f;
      m_Values[ 2 ][ 2 ] = 0.0f;
      m_Values[ 2 ][ 3 ] = 0.0f;
    }

    Matrix3x4( float m00,
               float m01,
               float m02,
               float m03,
               float m10,
               float m11,
               float m12,
               float m13,
               float m20,
               float m21,
               float m22,
               float m23 ) {
      m_Values[ 0 ][ 0 ] = m00;
      m_Values[ 0 ][ 1 ] = m01;
      m_Values[ 0 ][ 2 ] = m02;
      m_Values[ 0 ][ 3 ] = m03;
      m_Values[ 1 ][ 0 ] = m10;
      m_Values[ 1 ][ 1 ] = m11;
      m_Values[ 1 ][ 2 ] = m12;
      m_Values[ 1 ][ 3 ] = m13;
      m_Values[ 2 ][ 0 ] = m20;
      m_Values[ 2 ][ 1 ] = m21;
      m_Values[ 2 ][ 2 ] = m22;
      m_Values[ 2 ][ 3 ] = m23;
    }

    void m_Initialize( const Utils::Math::Vector & x,
                       const Utils::Math::Vector & y,
                       const Utils::Math::Vector & z,
                       const Utils::Math::Vector & origin ) {
      m_Values[ 0 ][ 0 ] = x.m_X;
      m_Values[ 0 ][ 1 ] = y.m_X;
      m_Values[ 0 ][ 2 ] = z.m_X;
      m_Values[ 0 ][ 3 ] = origin.m_X;
      m_Values[ 1 ][ 0 ] = x.m_Y;
      m_Values[ 1 ][ 1 ] = y.m_Y;
      m_Values[ 1 ][ 2 ] = z.m_Y;
      m_Values[ 1 ][ 3 ] = origin.m_Y;
      m_Values[ 2 ][ 0 ] = x.m_Z;
      m_Values[ 2 ][ 1 ] = y.m_Z;
      m_Values[ 2 ][ 2 ] = z.m_Z;
      m_Values[ 2 ][ 3 ] = origin.m_Z;
    }

    Matrix3x4( const Utils::Math::Vector & x,
               const Utils::Math::Vector & y,
               const Utils::Math::Vector & z,
               const Utils::Math::Vector & origin ) {
      m_Initialize( x, y, z, origin );
    }

    inline void m_SetOrigin( Utils::Math::Vector const & p ) {
      m_Values[ 0 ][ 3 ] = p.m_X;
      m_Values[ 1 ][ 3 ] = p.m_Y;
      m_Values[ 2 ][ 3 ] = p.m_Z;
    }

    inline void m_Invalidate( ) {
      for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
          m_Values[ i ][ j ] = std::numeric_limits<float>::infinity( );
        }
      }
    }

    Utils::Math::Vector m_GetXAxis( ) const { return m_At( 0 ); }

    Utils::Math::Vector m_GetYAxis( ) const { return m_At( 1 ); }

    Utils::Math::Vector m_GetZAxis( ) const { return m_At( 2 ); }

    Utils::Math::Vector m_Origin( ) const { return m_At( 3 ); }

    Utils::Math::Vector m_At( int i ) const {
      return Utils::Math::Vector{ m_Values[ 0 ][ i ], m_Values[ 1 ][ i ], m_Values[ 2 ][ i ] };
    }

    const float * operator[]( int i ) const { return m_Values[ i ]; }

    const float * m_Base( ) const { return &m_Values[ 0 ][ 0 ]; }

    const bool operator==( Matrix3x4 matrix ) const {
      return m_Values[ 0 ][ 0 ] == matrix[ 0 ][ 0 ] && m_Values[ 0 ][ 1 ] == matrix[ 0 ][ 1 ] &&
             m_Values[ 0 ][ 2 ] == matrix[ 0 ][ 2 ] && m_Values[ 0 ][ 3 ] == matrix[ 0 ][ 3 ] &&
             m_Values[ 1 ][ 0 ] == matrix[ 1 ][ 0 ] && m_Values[ 1 ][ 1 ] == matrix[ 1 ][ 1 ] &&
             m_Values[ 1 ][ 2 ] == matrix[ 1 ][ 2 ] && m_Values[ 1 ][ 3 ] == matrix[ 1 ][ 3 ] &&
             m_Values[ 2 ][ 0 ] == matrix[ 2 ][ 0 ] && m_Values[ 2 ][ 1 ] == matrix[ 2 ][ 1 ] &&
             m_Values[ 2 ][ 2 ] == matrix[ 2 ][ 2 ] && m_Values[ 2 ][ 3 ] == matrix[ 2 ][ 3 ];
    }
  };

  struct VMatrix {
    VMatrix( );
    VMatrix( float m00,
             float m01,
             float m02,
             float m03,
             float m10,
             float m11,
             float m12,
             float m13,
             float m20,
             float m21,
             float m22,
             float m23,
             float m30,
             float m31,
             float m32,
             float m33 );

    void m_Initialize( float m00,
                       float m01,
                       float m02,
                       float m03,
                       float m10,
                       float m11,
                       float m12,
                       float m13,
                       float m20,
                       float m21,
                       float m22,
                       float m23,
                       float m30,
                       float m31,
                       float m32,
                       float m33 );

    inline float * operator[]( int i ) { return m_Mtx[ i ]; }

    inline const float * operator[]( int i ) const { return m_Mtx[ i ]; }

    inline const float * m_Base( ) const { return &m_Mtx[ 0 ][ 0 ]; }

  public:
    float m_Mtx[ 4 ][ 4 ];
  };
} // namespace Utils::Math