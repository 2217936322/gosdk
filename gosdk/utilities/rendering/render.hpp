#pragma once

#include "../color/color.hpp"
#include <string_view>

#include "../d3d.hpp"

namespace Utils {
  class CRender {
  public:
    class CSurface {
    public:
      enum EFontFlags {
        FONTFLAG_NONE,
        FONTFLAG_ITALIC = 0x001,
        FONTFLAG_UNDERLINE = 0x002,
        FONTFLAG_STRIKEOUT = 0x004,
        FONTFLAG_SYMBOL = 0x008,
        FONTFLAG_ANTIALIAS = 0x010,
        FONTFLAG_GAUSSIANBLUR = 0x020,
        FONTFLAG_ROTARY = 0x040,
        FONTFLAG_DROPSHADOW = 0x080,
        FONTFLAG_ADDITIVE = 0x100,
        FONTFLAG_OUTLINE = 0x200,
        FONTFLAG_CUSTOM = 0x400,
        FONTFLAG_BITMAP = 0x800
      };

      unsigned Verdana{ };
      unsigned ESP{ };

      void RenderBox( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
      void RenderBoxOutline( const int x, const int y, const int w, const int h, Utils::Color color, bool is_additive ) noexcept;
      void RenderCircle( const int x, const int y, const int radius, Utils::Color color ) noexcept;
      void RenderCircleOutline( const int x, const int y, const int radius, const int segments, Utils::Color color ) noexcept;
      void RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept;
      void RenderText( const int x, const int y, unsigned font, Utils::Color color, const std::wstring_view text ) noexcept;

      void RunRender( ) noexcept;
      void ReleaseRender( ) noexcept;
    } Surface;

    class CD3D {
    private:
      template <typename T> struct SVertex {
        T m_X, m_Y, m_Z, m_RHW;
        D3DCOLOR m_Color;
      };

    public:
      void CreateFontExA( ID3DXFont *& font, const std::wstring_view & family, const int size, const int weight ) noexcept;
      ID3DXFont * Tahoma{ };

      void RenderBox( const int x, const int y, const int w, const int h, Utils::Color color ) noexcept;
      void RenderBoxOutline( const int x, const int y, const int w, const int h, Utils::Color color ) noexcept;
      void RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept;
      void RenderText( const int x,
                       const int y,
                       ID3DXFont *& font,
                       bool drop_shadow,
                       Utils::Color color,
                       const std::wstring_view & text ) noexcept;

      void RunDeviceStates( ) noexcept;

      void RunRender( ) noexcept;
      void ReleaseRender( ) noexcept;

    } D3D;
  };

  inline CRender g_Render{ };
} // namespace Utils