#pragma once

#include "../../../utilities/global.hpp"

/* Indexes */
enum ESurfaceIndexes : short {
  SetDrawColor_index = 15,
  DrawFilledRect_index = 16,
  DrawOutlinedRect_index = 18,
  DrawLine_index = 19,
  SetTextFont_index = 23,
  SetTextColor_index = 25,
  SetTextPosition_index = 26,
  PrintText_index = 28,
  GetScreenSize_index = 44,
  UnlockCursor_index = 66,
  CreateFontExA_index = 71,
  SetFontGlyphSet_index = 72,
  GetTextSize_index = 79,
  DrawOutlinedCircle_index = 103
};

namespace CS::Interfaces {
  class ISurface {
  public:
    /* Namings with ExA are due to WINAPI overriding names */

    constexpr auto SetDrawColor( int r, int g, int b, int a = 255 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>( this, ESurfaceIndexes::SetDrawColor_index, r, g, b, a );
    }

    const auto SetDrawColor( Utils::Color color ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>(
          this, ESurfaceIndexes::SetDrawColor_index, color.m_uRed, color.m_uGreen, color.m_uBlue, color.m_uAlpha );
    }

    template <typename T> constexpr auto DrawFilledRect( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>( this, ESurfaceIndexes::DrawFilledRect_index, x0, y0, x1, y1 );
    }

    template <typename T> constexpr auto DrawOutlinedRect( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>(
          this, ESurfaceIndexes::DrawOutlinedRect_index, x0, y0, x1, y1 );
    }

    template <typename T> constexpr auto DrawLine( T x0, T y0, T x1, T y1 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>( this, ESurfaceIndexes::DrawLine_index, x0, y0, x1, y1 );
    }

    constexpr auto SetTextFont( unsigned font ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, unsigned>( this, ESurfaceIndexes::SetTextFont_index, font );
    }

    constexpr auto SetTextColor( int r, int g, int b, int a = 255 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>( this, ESurfaceIndexes::SetTextColor_index, r, g, b, a );
    }

    const auto SetTextColor( Utils::Color color ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>(
          this, ESurfaceIndexes::SetTextColor_index, color.m_uRed, color.m_uGreen, color.m_uBlue, color.m_uAlpha );
    }

    template <typename T> constexpr auto SetTextPosition( T x, T y ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int>( this, ESurfaceIndexes::SetTextPosition_index, x, y );
    }

    constexpr auto PrintText( const std::wstring_view text, int drawType = 0 ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, const wchar_t *, int, int>(
          this, ESurfaceIndexes::PrintText_index, text.data( ), text.length( ), drawType );
    }

    constexpr auto GetScreenSize( ) noexcept {
      int width{ }, height{ };
      Utils::g_Memory.CallVirtualMethod<void, int &, int &>( this, ESurfaceIndexes::GetScreenSize_index, width, height );
      return std::make_pair( width, height );
    }

    constexpr auto UnlockCursor( ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void>( this, ESurfaceIndexes::UnlockCursor_index );
    }

    constexpr auto CreateFontExA( ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<unsigned>( this, ESurfaceIndexes::CreateFontExA_index );
    }

    constexpr auto SetFontGlyphSet( unsigned font,
                                    const char * font_name,
                                    int tall,
                                    int weight,
                                    int blur,
                                    int scanlines,
                                    int flags,
                                    int range_min = 0,
                                    int range_max = 0 ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<bool, unsigned, const char *, int, int, int, int, int, int, int>(
          this,
          ESurfaceIndexes::SetFontGlyphSet_index,
          font,
          font_name,
          tall,
          weight,
          blur,
          scanlines,
          flags,
          range_min,
          range_max );
    }

    constexpr auto GetTextSize( unsigned font, const wchar_t * text ) noexcept {
      int width{ }, height{ };
      Utils::g_Memory.CallVirtualMethod<void, unsigned, const wchar_t *, int &, int &>(
          this, ESurfaceIndexes::GetTextSize_index, font, text, width, height );
      return std::make_pair( width, height );
    }

    template <typename T> constexpr auto DrawOutlinedCircle( T x, T y, int r, int seg ) noexcept {
      Utils::g_Memory.CallVirtualMethod<void, int, int, int, int>(
          this, ESurfaceIndexes::DrawOutlinedCircle_index, x, y, r, seg );
    }

    template <typename T> constexpr auto DrawFilledCircle( T x, T y, int r ) noexcept {
      for ( int i = 0; i <= r; i++ ) {
        DrawOutlinedCircle( x, y, i, i );
      }
    }
  };
} // namespace CS::Interfaces
