#include "hook.hpp"
#include "../../config/config.hpp"
#include "../../csgo/global.hpp"
#include <algorithm>
#include <intrin.h>

namespace Utils {
  bool __stdcall CHooking::bSvCheats( ) noexcept { return true; }

  bool __stdcall CHooking::bGrenadePreview( ) noexcept { return true; }

  void __fastcall CHooking::LockCursor( ) noexcept {
    static auto Original = g_Hooking.SurfaceHook.GetOriginalFunction<LockCursor_t>( EFuncIndexes::LockCursor_index );

    if ( GetAsyncKeyState( VK_INSERT ) ) {
      CS::g_Interfaces.g_pSurface->UnlockCursor( );
      return;
    }

    if ( Original )
      return Original( CS::g_Interfaces.g_pSurface );
  }

  void __stdcall CHooking::PaintTraverse( unsigned int Panel, bool ForceRepaint, bool AllowForce ) noexcept {
    static auto Original = g_Hooking.PanelHook.GetOriginalFunction<PaintTraverse_t>( EFuncIndexes::PaintTraverse_index );

    if ( CS::g_Interfaces.g_pPanel->GetName( Panel ) == "MatSystemTopPanel" ) {
    }

    if ( Original )
      Original( CS::g_Interfaces.g_pPanel, Panel, ForceRepaint, AllowForce );
  }

  bool __fastcall CHooking::bCreateMove( void * ecx,
                                         void * edx,
                                         int InputSampleFrameTime,
                                         CS::Classes::CUserCmd * Cmd ) noexcept {
    if ( !InputSampleFrameTime || !Cmd || !Cmd->m_iCommandNumber )
      return false;

    Utils::g_Context.g_pCmd = Cmd;
    Utils::g_Context.g_pLocal = CS::g_Interfaces.g_pEntityList->GetEntity( CS::g_Interfaces.g_pEngineClient->GetLocalPlayer( ) );

    CS::Features::g_Movement.BunnyHop( );
    CS::Features::g_Movement.NoDuckDelay( );

    Cmd->m_fForwardMove = std::clamp( Cmd->m_fForwardMove, -450.0f, 450.0f );
    Cmd->m_fSideMove = std::clamp( Cmd->m_fSideMove, -450.0f, 450.0f );
    Cmd->m_fUpMove = std::clamp( Cmd->m_fUpMove, -320.0f, 320.0f );

    Cmd->m_ViewAngles.m_X = std::clamp( Cmd->m_ViewAngles.m_X, -89.0f, 89.0f );
    Cmd->m_ViewAngles.m_Y = std::clamp( Cmd->m_ViewAngles.m_Y, -180.0f, 180.0f );
    Cmd->m_ViewAngles.m_Z = 0.0f;

    return false;
  }

  LRESULT WINAPI CHooking::lipWinProc( HWND WindowHandle, UINT Message, WPARAM WindowParams, LPARAM lpParams ) noexcept {
    if ( Message == WM_KEYUP ) {
      switch ( WindowParams ) {
        case VK_INSERT:
          Utils::g_Console.Log<std::string_view>( "Hit" );
          /* There you can handle stuff such as input disabling / enabling, although that can
             also be done in places like LockCursor. This is to help with stuff like menu frameworks
             such as ImGui. This also only handles events if they're done within the window the DLL is injected in. */
          break;
      }
    }

    if ( GetAsyncKeyState( VK_INSERT ) ) {
      return true;
    }

    return CallWindowProcW( g_Hooking.pWindowOriginal, WindowHandle, Message, WindowParams, lpParams );
  }

  bool CHooking::Initialized = false;

  long WINAPI CHooking::liPresent( IDirect3DDevice9 * Device,
                                   RECT * SourceRect,
                                   RECT * DestinationRect,
                                   HWND DestinationWindowOverride,
                                   RGNDATA * DirtyRegion ) noexcept {
    if ( !g_Hooking.Initialized )
      g_Hooking.Initialized = true;
    else
      ( [ & ]( ) {
        Utils::g_Render.D3D.RunDeviceStates( );
        Utils::g_Render.D3D.RunRender( );

        CS::Features::g_Esp.RunEsp( );
      } )( );

    return g_Hooking.OriginalPresent( Device, SourceRect, DestinationRect, DestinationWindowOverride, DirtyRegion );
  }

  long WINAPI CHooking::liReset( IDirect3DDevice9 * Device, D3DPRESENT_PARAMETERS * PresentParams ) noexcept {
    if ( !Initialized )
      g_Hooking.OriginalReset( Device, PresentParams );

    long hr = g_Hooking.OriginalReset( Device, PresentParams );

    if ( hr )
      ( [ & ]( ) { Utils::g_Render.D3D.RunRender( ); } )( );

    return hr;
  }

  void CHooking::RunHooks( ) noexcept {
    CheatsHook.bInit( CS::g_Interfaces.g_pConsole->FindVar( "sv_cheats" ) );
    CheatsHook.bHookFunction( EFuncIndexes::GetInt_index, bSvCheats );

    GrenadePreviewHook.bInit( CS::g_Interfaces.g_pConsole->FindVar( "cl_grenade_preview" ) );
    GrenadePreviewHook.bHookFunction( EFuncIndexes::GetInt_index, bGrenadePreview );

    ClientModeHook.bInit( CS::g_Interfaces.g_pClientMode );
    ClientModeHook.bHookFunction( EFuncIndexes::CreateMove_index, bCreateMove );

    SurfaceHook.bInit( CS::g_Interfaces.g_pSurface );
    SurfaceHook.bHookFunction( EFuncIndexes::LockCursor_index, LockCursor );

    PanelHook.bInit( CS::g_Interfaces.g_pPanel );
    PanelHook.bHookFunction( EFuncIndexes::PaintTraverse_index, PaintTraverse );

    /* May not be visually appleasing to have all of those
       things laying around here, but it is done so to not
       have to worry about the order of how things are called.
       I tried other methods, more visually pleasing, and that didn't work.
       Well, I guess that sucks. */
    upPresentAddress = Utils::g_Memory.FindPattern( "gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB" ) + 0x2;
    upResetAddress = Utils::g_Memory.FindPattern( "gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18" ) + 0x2;

    OriginalPresent = **reinterpret_cast<Present_t **>( upPresentAddress );
    OriginalReset = **reinterpret_cast<Reset_t **>( upResetAddress );

    **reinterpret_cast<void ***>( upPresentAddress ) = reinterpret_cast<void *>( &liPresent );
    **reinterpret_cast<void ***>( upResetAddress ) = reinterpret_cast<void *>( &liReset );

    pWindow = FindWindowW( L"Valve001", nullptr );
    pWindowOriginal = reinterpret_cast<WNDPROC>( SetWindowLongW( pWindow, GWL_WNDPROC, reinterpret_cast<LONG>( lipWinProc ) ) );
  }

  void CHooking::ReleaseHooks( ) noexcept {
    CheatsHook.bUnhook( );
    GrenadePreviewHook.bUnhook( );
    ClientModeHook.bUnhook( );
    SurfaceHook.bUnhook( );
    PanelHook.bUnhook( );

    upPresentAddress = nullptr;
    upResetAddress = nullptr;
    OriginalPresent = nullptr;
    OriginalReset = nullptr;
    pWindow = nullptr;
    pWindowOriginal = nullptr;
  }
} // namespace Utils
