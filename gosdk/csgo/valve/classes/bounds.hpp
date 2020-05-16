#pragma once

#include "../../../utilities/math/global.hpp"

// inb4 UC screams at me
#pragma warning( disable : 4244 )

namespace CS::Classes {
  class Box {
  public:
    int x, y, w, h;

    Box( ) = default;
    ~Box( ) = default;

    Box( int x, int y, int w, int h ) : x( x ), y( y ), w( w ), h( h ) {}
    Box( const Utils::Math::Vector2 & tl, const Utils::Math::Vector2 & br )
        : x( tl.x ), y( tl.y ), w( br.x - tl.x ), h( tl.y - br.y ) {}

    Box( const Box & ) = default;
    Box & operator=( const Box & ) = default;

    Box( Box && ) = default;
    Box & operator=( Box && ) = default;

    int m_iRight( ) const { return x + w; }

    int m_iBottom( ) const { return y + h; }

    bool m_bIsInBounds( const Utils::Math::Vector2 & pt ) const {
      if ( this->x > pt.x )
        return false;
      if ( this->y > pt.y )
        return false;
      if ( this->m_iRight( ) < pt.x )
        return false;
      if ( this->m_iBottom( ) < pt.y )
        return false;

      return true;
    }
  };
} // namespace CS::Classes