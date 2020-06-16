#pragma once

#include "../../../utilities/global.hpp"
#include "../utilities/c_utl.hpp"

namespace CS::Classes {
  class CConvar;

  class CConvar {
  public:
    constexpr auto GetFloat( ) noexcept { return Utils::g_Memory.CallVirtualMethod<float>( this, 12 ); }
    constexpr auto GetInt( ) noexcept { return Utils::g_Memory.CallVirtualMethod<int>( this, 13 ); }
    constexpr auto SetValue( const char * value ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, const char *>( this, 14, value );
    }
    constexpr auto SetValue( float value ) noexcept { Utils::g_Memory.CallVirtualMethod<void, float>( this, 15, value ); }
    constexpr auto SetValue( int value ) noexcept { Utils::g_Memory.CallVirtualMethod<void, int>( this, 16, value ); }

#pragma region Class
  private:
    char Pad[ 0x4 ];

  public:
    CConvar * m_Next;
    __int32 m_iIsRegistered;
    char * m_cName;
    char * m_cHelpString;
    __int32 m_iFlags;

  private:
    char Pad2[ 0x4 ];

  public:
    CConvar * m_Parent;
    char * m_cDefaultValue;
    char * m_cString;
    __int32 m_iStringLength;
    float m_fFloatValue;
    __int32 m_iNumericalValue;
    __int32 m_iHasMin;
    float m_fMin;
    __int32 m_iHasMax;
    float m_fMax;

    using ChangeCallback_t = void ( * )( CConvar * var, const char * cOldValue, float fOldValue );
    CUtlVector<ChangeCallback_t> m_Callbacks;
#pragma endregion Various
  };
} // namespace CS::Classes