#pragma once

#include "../interfaces/i_client_unknown.hpp"
#include "../utilities/netvar/global.hpp"

namespace CS::Classes {
  enum EMovetypes : short {
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
  };

  enum EEntityFlags : long { /* avoid truncation */
                             FL_ONGROUND = ( 1 << 0 ),
                             FL_DUCKING = ( 1 << 1 ),
                             FL_WATERJUMP = ( 1 << 2 ),
                             FL_ONTRAIN = ( 1 << 3 ),
                             FL_INRAIN = ( 1 << 4 ),
                             FL_FROZEN = ( 1 << 5 ),
                             FL_ATCONTROLS = ( 1 << 6 ),
                             FL_CLIENT = ( 1 << 7 ),
                             FL_FAKECLIENT = ( 1 << 8 ),
                             FL_INWATER = ( 1 << 9 ),
                             FL_FLY = ( 1 << 10 ),
                             FL_SWIM = ( 1 << 11 ),
                             FL_CONVEYOR = ( 1 << 12 ),
                             FL_NPC = ( 1 << 13 ),
                             FL_GODMODE = ( 1 << 14 ),
                             FL_NOTARGET = ( 1 << 15 ),
                             FL_AIMTARGET = ( 1 << 16 ),
                             FL_PARTIALGROUND = ( 1 << 17 ),
                             FL_STATICPROP = ( 1 << 18 ),
                             FL_GRAPHED = ( 1 << 19 ),
                             FL_GRENADE = ( 1 << 20 ),
                             FL_STEPMOVEMENT = ( 1 << 21 ),
                             FL_DONTTOUCH = ( 1 << 22 ),
                             FL_BASEVELOCITY = ( 1 << 23 ),
                             FL_WORLDBRUSH = ( 1 << 24 ),
                             FL_OBJECT = ( 1 << 25 ),
                             FL_KILLME = ( 1 << 26 ),
                             FL_ONFIRE = ( 1 << 27 ),
                             FL_DISSOLVING = ( 1 << 28 ),
                             FL_TRANSRAGDOLL = ( 1 << 29 ),
                             FL_UNBLOCKABLE_BY_PLAYER = ( 1 << 30 )
  };

  class CCSPlayer : public CS::Interfaces::CClientUnknown {
  public:
    netvar( int, m_iHealth, "DT_BasePlayer->m_iHealth" );
    netvar( std::uint8_t, m_uiLifeState, "DT_BasePlayer->m_lifeState" );
    netvar( int, m_iArmor, "DT_CSPlayer->m_ArmorValue" );
    netvar( bool, m_bHasHelmet, "DT_CSPlayer->m_bHasHelmet" );
    netvar( Utils::Easing::BitFlag, m_Flags, "DT_BasePlayer->m_fFlags" );
    netvar( bool, m_bImmune, "DT_CSPlayer->m_bGunGameImmunity" );
    netvar( bool, m_bScoped, "DT_CSPlayer->m_bIsScoped" );
    netvar( float, m_fFlashDuration, "DT_CSPlayer->m_flFlashDuration" );
    netvar( float, m_fFlashAlpha, "DT_CSPlayer->m_flFlashMaxAlpha" );
    netvar( float, m_fCrouchAmount, "DT_BasePlayer->m_flDuckAmount" );
    netvar( Utils::Math::Vector, m_ViewPunch, "DT_BasePlayer->m_viewPunchAngle" );
    netvar( Utils::Math::Vector, m_AimPunch, "DT_BasePlayer->m_aimPunchAngle" );
    netvar( Utils::Math::Vector, m_Velocity, "DT_LocalPlayerExclusive->m_vecVelocity[0]" );
    netvar_additive( EMovetypes, m_Movetype, "DT_BaseEntity->m_nRenderMode", 1 );
    netvar( Utils::Math::Vector, m_Origin, "DT_BaseEntity->m_vecOrigin" );

    constexpr CS::Classes::CClientNetworkable * m_ClientRenderable( ) {
      if ( this ) {
        return reinterpret_cast<CS::Classes::CClientNetworkable *>( reinterpret_cast<std::uintptr_t>( this ) + 0x8 );
      }
    }

    constexpr bool m_bIsAlive( ) {
      if ( !this )
        return false;

      return this->m_iHealth( ) > 0;
    }
  };
} // namespace CS::Classes
