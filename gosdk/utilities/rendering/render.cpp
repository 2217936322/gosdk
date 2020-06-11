#include "render.hpp"
#include "../../csgo/valve/global.hpp"

// Narrowing conversation on templates - TODO: fix
#pragma warning( disable : 4838 )

namespace Utils {
#pragma region Utils
  // Not Finished
  bool CRender::CUtils::bScreenTransform( Utils::Math::Vector & screen, Utils::Math::Vector & origin ) noexcept {
    static std::uintptr_t ViewMatrix{ };

    if ( !ViewMatrix )
      ViewMatrix = *reinterpret_cast<std::uintptr_t *>(
                       Utils::g_Memory.FindPattern( "client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9" ) + 0x3 ) +
                   0xB0;

    const Utils::Math::VMatrix & WorldMatrix = *reinterpret_cast<Utils::Math::VMatrix *>( ViewMatrix );

    screen.m_X = WorldMatrix.m_Mtx[ 0 ][ 0 ] * origin.m_X + WorldMatrix.m_Mtx[ 0 ][ 1 ] * origin.m_Y +
                 WorldMatrix.m_Mtx[ 0 ][ 2 ] * origin.m_Z + WorldMatrix.m_Mtx[ 0 ][ 3 ];
    screen.m_Y = WorldMatrix.m_Mtx[ 1 ][ 0 ] * origin.m_X + WorldMatrix.m_Mtx[ 1 ][ 1 ] * origin.m_Y +
                 WorldMatrix.m_Mtx[ 1 ][ 2 ] * origin.m_Z + WorldMatrix.m_Mtx[ 1 ][ 3 ];
    screen.m_Z = 0;

    const auto w = WorldMatrix.m_Mtx[ 3 ][ 0 ] * origin.m_X + WorldMatrix.m_Mtx[ 3 ][ 1 ] * origin.m_Y +
                   WorldMatrix.m_Mtx[ 3 ][ 2 ] * origin.m_Z + WorldMatrix.m_Mtx[ 3 ][ 3 ];

    if ( w < 0.001f ) {
      screen.m_X *= 100000;
      screen.m_Y *= 100000;

      return false;
    }

    screen.m_X *= 1.f / w;
    screen.m_Y *= 1.f / w;

    return true;
  }

  bool CRender::CUtils::bWorldToScreen( Utils::Math::Vector & origin, Utils::Math::Vector & screen ) noexcept {
    if ( !bScreenTransform( screen, origin ) )
      return false;

    const auto [ width, height ] = CS::g_Interfaces.g_pSurface->GetScreenSize( );

    screen.m_X = ( width / 2 ) + ( screen.m_X * width ) / 2;
    screen.m_Y = ( height / 2 ) - ( screen.m_Y * height ) / 2;

    return true;
  }
#pragma endregion Utilities made for rendering functions

#pragma region Surface
  unsigned CRender::CSurface::Verdana{ NULL };
  unsigned CRender::CSurface::ESP{ NULL };

  void CRender::CSurface::RenderBox( const int x,
                                     const int y,
                                     const int w,
                                     const int h,
                                     Utils::Color color,
                                     const bool is_additive ) noexcept {
    CS::g_Interfaces.g_pSurface->SetDrawColor( color );
    CS::g_Interfaces.g_pSurface->DrawFilledRect( x, y, is_additive ? x + w : w, is_additive ? y + h : h );
  }

  void CRender::CSurface::RenderBoxOutline( const int x,
                                            const int y,
                                            const int w,
                                            const int h,
                                            Utils::Color color,
                                            const bool is_additive ) noexcept {
    CS::g_Interfaces.g_pSurface->SetDrawColor( color );
    CS::g_Interfaces.g_pSurface->DrawOutlinedRect( x, y, is_additive ? x + w : w, is_additive ? y + h : h );
  }

  void CRender::CSurface::RenderCircle( const int x, const int y, const int radius, Utils::Color color ) noexcept {
    CS::g_Interfaces.g_pSurface->SetDrawColor( color );
    CS::g_Interfaces.g_pSurface->DrawFilledCircle( x, y, radius );
  }

  void CRender::CSurface::RenderCircleOutline( const int x,
                                               const int y,
                                               const int radius,
                                               const int segments,
                                               Utils::Color color ) noexcept {
    CS::g_Interfaces.g_pSurface->SetDrawColor( color );
    CS::g_Interfaces.g_pSurface->DrawOutlinedCircle( x, y, radius, segments );
  }

  void CRender::CSurface::RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept {
    CS::g_Interfaces.g_pSurface->SetDrawColor( color );
    CS::g_Interfaces.g_pSurface->DrawLine( x, y, x1, y1 );
  }

  void CRender::CSurface::RenderText( const int x,
                                      const int y,
                                      unsigned font,
                                      Utils::Color color,
                                      const std::wstring_view text ) noexcept {
    CS::g_Interfaces.g_pSurface->SetTextPosition( x, y );
    CS::g_Interfaces.g_pSurface->SetTextFont( font );
    CS::g_Interfaces.g_pSurface->SetTextColor( color );
    CS::g_Interfaces.g_pSurface->PrintText( text );
  }

  void CRender::CSurface::RunRender( ) noexcept {
    /* Namings with ExA are due to WINAPI overriding names */
    Verdana = CS::g_Interfaces.g_pSurface->CreateFontExA( );
    ESP = CS::g_Interfaces.g_pSurface->CreateFontExA( );

    ( [ & ]( ) {
      CS::g_Interfaces.g_pSurface->SetFontGlyphSet(
          g_Render.Surface.Verdana, "Verdana", 13, 600, 0, 0, EFontFlags::FONTFLAG_OUTLINE );
      CS::g_Interfaces.g_pSurface->SetFontGlyphSet( g_Render.Surface.ESP, "Tahoma", 13, 200, 0, 0, EFontFlags::FONTFLAG_OUTLINE );
    } )( );
  }

  void CRender::CSurface::ReleaseRender( ) noexcept { Verdana = NULL; }
#pragma endregion Functions related to the ISurface render engine

#pragma region D3D
  ID3DXFont * CRender::CD3D::Tahoma{ nullptr };
  ID3DXFont * CRender::CD3D::ESP{ nullptr };

  void
  CRender::CD3D::CreateFontExA( ID3DXFont *& font, const std::wstring_view & family, const int size, const int weight ) noexcept {
    if ( !font )
      D3DXCreateFontW( CS::g_Interfaces.g_pDevice,
                       size,
                       0,
                       weight,
                       1,
                       false,
                       ANSI_CHARSET,
                       OUT_DEFAULT_PRECIS,
                       CLEARTYPE_NATURAL_QUALITY,
                       DEFAULT_PITCH,
                       family.data( ),
                       &font );
  }

  void CRender::CD3D::RenderBox( const int x,
                                 const int y,
                                 const int w,
                                 const int h,
                                 Utils::Color color,
                                 const bool is_additive ) noexcept {
    D3DCOLOR dwColor = D3DCOLOR_RGBA( color.m_uRed, color.m_uGreen, color.m_uBlue, color.m_uAlpha );

    const SVertex<float> Vertices[ 4 ] = {
      { x, is_additive ? y + h : h, 0.f, 1.f, dwColor },
      { x, y, 0.f, 1.f, dwColor },
      { is_additive ? x + w : w, is_additive ? y + h : h, 0.f, 1.f, dwColor },
      { is_additive ? x + w : w, y, 0.f, 1.f, dwColor },
    };

    CS::g_Interfaces.g_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
    CS::g_Interfaces.g_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, Vertices, sizeof( SVertex<float> ) );
  }

  void CRender::CD3D::RenderBoxOutline( const int x,
                                        const int y,
                                        const int w,
                                        const int h,
                                        Utils::Color color,
                                        const bool is_additive ) noexcept {
    RenderLine( x, y, is_additive ? x + w : w, y, color );
    RenderLine( x, y, x, is_additive ? y + h : h, color );
    RenderLine( x, is_additive ? y + h : h, is_additive ? x + w : w, is_additive ? y + h : h, color );
    RenderLine( is_additive ? x + w : w, y, is_additive ? x + w : w, is_additive ? y + h : h, color );
  }

  void CRender::CD3D::RenderLine( const int x, const int y, const int x1, const int y1, Utils::Color color ) noexcept {
    D3DCOLOR dwColor = D3DCOLOR_RGBA( color.m_uRed, color.m_uGreen, color.m_uBlue, color.m_uAlpha );

    const SVertex<float> Vertices[ 2 ] = { { x - 0.5f, y - 0.5f, 0.0f, 1.0f, dwColor },
                                           { x1 - 0.5f, y1 - 0.5f, 0.0f, 1.0f, dwColor } };

    CS::g_Interfaces.g_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

    CS::g_Interfaces.g_pDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, &Vertices, sizeof( SVertex<float> ) );
  }

  void CRender::CD3D::RenderText( const int x,
                                  const int y,
                                  ID3DXFont *& font,
                                  bool drop_shadow,
                                  Utils::Color color,
                                  const std::wstring_view & text ) noexcept {
    if ( drop_shadow ) {
      D3DCOLOR dwColorDark = D3DCOLOR_RGBA( 0, 0, 0, 255 );

      RECT RectFontSizeBack = { x + 1, y + 1 };

      font->DrawTextW( nullptr, text.data( ), text.length( ), &RectFontSizeBack, DT_LEFT | DT_NOCLIP, dwColorDark );
    }

    D3DCOLOR dwColor = D3DCOLOR_RGBA( color.m_uRed, color.m_uGreen, color.m_uBlue, color.m_uAlpha );

    RECT RectFontSize = { x, y };

    font->DrawTextW( nullptr, text.data( ), text.length( ), &RectFontSize, DT_LEFT | DT_NOCLIP, dwColor );
  }

  /// <summary>
  /// These are some device states I use for rendering quality.
  /// </summary>
  void CRender::CD3D::RunDeviceStates( ) noexcept {
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, TRUE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );

    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );

    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, TRUE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE );
    CS::g_Interfaces.g_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE,
                                                D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE |
                                                    D3DCOLORWRITEENABLE_ALPHA );
  }

  void CRender::CD3D::RunRender( ) noexcept {
    CreateFontExA( Tahoma, L"Tahoma", 32, 500 );
    CreateFontExA( ESP, L"Verdana", 12, 500 );
  }

  void CRender::CD3D::ReleaseRender( ) noexcept {
    Tahoma = nullptr;
    ESP = nullptr;
  }
#pragma endregion Functions related to the D3D render engine
} // namespace Utils
