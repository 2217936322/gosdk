#pragma once

#include "../../../utilities/global.hpp"
#include "../../valve/global.hpp"

namespace CS::Features {
  class CESP {
  private:
    // thanks to poliacs for the calculations from UnknownCheats, was a time saver.

    /// <summary>
    /// Function used to calculate bounds for entities
    /// </summary>
    /// <param name="Player">Entity that will be used in the origin/sizes calculation</param>
    /// <param name="Box">Rectangle class used to ease calculations</param>
    /// <returns></returns>
    bool BoundingBox( CS::Classes::CCSPlayer * Player, CS::Classes::Box & Box ) noexcept {
      const Utils::Math::Vector2 flb{ }, brt{ }, blb{ }, frt{ }, frb{ }, brb{ }, blt{ }, flt{ }, out{ };

      const Utils::Math::Vector Origin = Player->m_Origin( );
      const Utils::Math::Vector Mins = Player->GetCollideable( )->OBBMins( ) + Origin;
      const Utils::Math::Vector Maxs = Player->GetCollideable( )->OBBMaxs( ) + Origin;

      Utils::Math::Vector points[] = {
        Utils::Math::Vector( Mins.m_X, Mins.m_Y, Mins.m_Z ), Utils::Math::Vector( Mins.m_X, Maxs.m_Y, Mins.m_Z ),
        Utils::Math::Vector( Maxs.m_X, Maxs.m_Y, Mins.m_Z ), Utils::Math::Vector( Maxs.m_X, Mins.m_Y, Mins.m_Z ),
        Utils::Math::Vector( Maxs.m_X, Maxs.m_Y, Maxs.m_Z ), Utils::Math::Vector( Mins.m_X, Maxs.m_Y, Maxs.m_Z ),
        Utils::Math::Vector( Mins.m_X, Mins.m_Y, Maxs.m_Z ), Utils::Math::Vector( Maxs.m_X, Mins.m_Y, Maxs.m_Z )
      };

      // vector constructors wouldn't work so I had to do this, will be fixed later
      Utils::Math::Vector rgPostWTSVec[] = {
        Utils::Math::Vector( blb.m_X, blb.m_Y, 0.f ), Utils::Math::Vector( brb.m_X, brb.m_Y, 0.f ),
        Utils::Math::Vector( frb.m_X, frb.m_Y, 0.f ), Utils::Math::Vector( flb.m_X, flb.m_Y, 0.f ),
        Utils::Math::Vector( frt.m_X, frt.m_Y, 0.f ), Utils::Math::Vector( brt.m_X, brt.m_Y, 0.f ),
        Utils::Math::Vector( blt.m_X, blt.m_Y, 0.f ), Utils::Math::Vector( flt.m_X, flt.m_Y, 0.f )
      };

      for ( auto i = 0; i <= 7; ++i )
        if ( CS::g_Interfaces.g_pDebugOverlay->WorldToScreen( points[ i ], rgPostWTSVec[ i ] ) )
          return false;

      auto left = rgPostWTSVec[ 3 ].m_X, right = rgPostWTSVec[ 3 ].m_X, top = rgPostWTSVec[ 3 ].m_Y,
           bottom = rgPostWTSVec[ 3 ].m_Y;

      for ( auto i = 0; i <= 7; i++ ) {
        if ( top > rgPostWTSVec[ i ].m_Y )
          top = rgPostWTSVec[ i ].m_Y;

        if ( bottom < rgPostWTSVec[ i ].m_Y )
          bottom = rgPostWTSVec[ i ].m_Y;

        if ( left > rgPostWTSVec[ i ].m_X )
          left = rgPostWTSVec[ i ].m_X;

        if ( right < rgPostWTSVec[ i ].m_X )
          right = rgPostWTSVec[ i ].m_X;
      }

      Box.m_iX = left;
      Box.m_iY = top;
      Box.m_iW = right - left;
      Box.m_iH = bottom - top;

      return true;
    }

    /// <summary>
    /// Function that draws bounds made by BoundingBox
    /// </summary>
    /// <param name="Box">Rectangle class used to ease calculations</param>
    /// <param name="ColorMain">Color used for the middle rectangle</param>
    /// <param name="ColorOutline">Color used for the outer and inner rectangle</param>
    /// <returns></returns>
    void DrawBox( CS::Classes::Box & Box, Utils::Color ColorMain, Utils::Color ColorOutline ) noexcept {
      Utils::g_Render.Surface.RenderBoxOutline( Box.m_iX, Box.m_iY, Box.m_iRight( ), Box.m_iBottom( ), ColorMain, false );

      Utils::g_Render.Surface.RenderBoxOutline(
          Box.m_iX - 1, Box.m_iY - 1, Box.m_iRight( ) + 1, Box.m_iBottom( ) + 1, ColorOutline, false );
      Utils::g_Render.Surface.RenderBoxOutline(
          Box.m_iX + 1, Box.m_iY + 1, Box.m_iRight( ) - 1, Box.m_iBottom( ) - 1, ColorOutline, false );
    }

    /// <summary>
    /// Function that draws entity names
    /// </summary>
    /// <param name="Box">Rectangle class used to ease calculations</param>
    /// <param name="Info">EngineClient structure that handles entity information</param>
    /// <param name="Color">Text color</param>
    void DrawName( CS::Classes::Box & Box, CS::Interfaces::PlayerInfo_t Info, Utils::Color Color ) {
      /* Cool way to get around this from Osiris */
      if ( wchar_t Name[ 128 ] /* According to the struct */; MultiByteToWideChar( CP_UTF8, 0, Info.m_Name, -1, Name, 128 ) ) {
        const auto [ width, height ] = CS::g_Interfaces.g_pSurface->GetTextSize( Utils::g_Render.Surface.ESP, Name );
        Utils::g_Render.Surface.RenderText(
            Box.m_iX + ( Box.m_iW / 2 ) - ( width / 2 ), Box.m_iY - 14, Utils::g_Render.Surface.ESP, Color, Name );
      }
    }

    /// <summary>
    /// Function that draws snap lines from the center of the screen to the entity's origin
    /// </summary>
    /// <param name="EntityOrigin">Vector pointing to an entity's origin</param>
    /// <param name="Color">Snapline color</param>
    /// <returns></returns>
    void DrawLine( Utils::Math::Vector & EntityOrigin, Utils::Color Color ) noexcept {
      Utils::Math::Vector PostWTSVec{ };
      CS::g_Interfaces.g_pDebugOverlay->WorldToScreen( EntityOrigin, PostWTSVec );

      auto [ width, height ] = CS::g_Interfaces.g_pSurface->GetScreenSize( );

      Utils::g_Render.Surface.RenderLine( width / 2, height / 2, PostWTSVec.m_X, PostWTSVec.m_Y, Color );
    }

  public:
    /// <summary>
    /// Function that handles entities which will be used for rendering
    /// </summary>
    void RunEsp( ) noexcept {
      /// <summary>
      /// Loops through all valid entities (Ignores world models)
      /// </summary>
      for ( int i = 1; i <= CS::g_Interfaces.g_pGlobalVars->MaxClients; i++ ) {
        auto Player = CS::g_Interfaces.g_pEntityList->GetEntity( i );

        if ( !Player || !Player->m_bIsAlive( ) || Player == Utils::g_Context.g_pLocal )
          continue;
        if ( !CS::g_Interfaces.g_pEngineClient->IsInGame( ) || !CS::g_Interfaces.g_pEngineClient->IsConnected( ) )
          continue;

        CS::Classes::Box Box;
        CS::Interfaces::PlayerInfo_t Info;

        if ( !BoundingBox( Player, Box ) )
          continue;

        CS::g_Interfaces.g_pEngineClient->GetPlayerInfo( Player->m_ClientRenderable( )->EntIndex( ), &Info );

        const int Alpha = Player->m_ClientRenderable( )->IsDormant( ) ? 100 : 255;

        DrawBox( Box, Utils::Color( 255, 255, 255, Alpha ), Utils::Color( 0, 0, 0, Alpha ) );
        DrawLine( Player->m_Origin( ), Utils::Color( 255, 255, 255, Alpha ) );
        DrawName( Box, Info, Utils::Color( 255, 255, 255, Alpha ) );
      }
    }
  };

  inline CESP g_Esp{ };
} // namespace CS::Features
