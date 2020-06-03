#pragma once

#include "../../csgo/valve/classes/user_cmd.hpp"
#include "../../dependencies/global.hpp"
#include "../../utilities/global.hpp"
#include "vmt.hpp"

namespace Utils {
  class CHooking {
  public:
    /// <summary>
    /// Indexes
    /// </summary>
    enum EFuncIndexes : short { GetInt_index = 13, CreateMove_index = 24, PaintTraverse_index = 41, LockCursor_index = 67 };

    /// <summary>
    /// Declarations
    /// </summary>
    Utils::CVMT CheatsHook;
    Utils::CVMT GrenadePreviewHook;
    Utils::CVMT ClientModeHook;
    Utils::CVMT SurfaceHook;
    Utils::CVMT PanelHook;
    /// <summary>
    /// These don't require originals because we want them to stay true at all times
    /// </summary>

    static bool __stdcall bSvCheats( ) noexcept;
    static bool __stdcall bGrenadePreview( ) noexcept;

    /// <summary>
    /// Note - You could instead use decltype within the
    /// GetOriginal function, but, after my testing
    /// Results from that were inaccurate and caused
    /// Rather weird issues. I advice you pass typedefinitions
    /// To not runinto issues in the future.
    /// </summary>
    static void __fastcall LockCursor( ) noexcept;
    using LockCursor_t = void( __thiscall * )( void * );

    static void __stdcall PaintTraverse( unsigned int Panel, bool ForceRepaint, bool AllowForce ) noexcept;
    using PaintTraverse_t = void( __thiscall * )( void *, unsigned int, bool, bool );

    static bool __fastcall bCreateMove( void * ecx, void * edx, int InputSampleFrameTime, CS::Classes::CUserCmd * Cmd ) noexcept;
    using CreateMove_t = bool( __stdcall * )( float, void * );

    /// <summary>
    /// Rendering Devices
    /// </summary>
    /* Since these very methods obtain their original
       from memory addresses, I have declared the original
       function initializations in there. Don't scream, pls. */

    static long WINAPI liPresent( IDirect3DDevice9 * Device,
                                  RECT * SourceRect,
                                  RECT * DestinationRect,
                                  HWND DestinationWindowOverride,
                                  RGNDATA * DirtyRegion ) noexcept;
    using Present_t = long( WINAPI * )( IDirect3DDevice9 *, RECT *, RECT *, HWND, RGNDATA * );
    Present_t OriginalPresent{ };
    std::uint8_t * upPresentAddress{ };

    static long WINAPI liReset( IDirect3DDevice9 * Device, D3DPRESENT_PARAMETERS * PresentParams ) noexcept;
    using Reset_t = long( WINAPI * )( IDirect3DDevice9 *, D3DPRESENT_PARAMETERS * );
    Reset_t OriginalReset{ };
    uint8_t * upResetAddress{ };

    /// <summary>
    /// Events
    /// </summary>
    static LRESULT WINAPI lipWinProc( HWND WindowHandle, UINT Message, WPARAM WindowParams, LPARAM lpParams ) noexcept;
    HWND pWindow;
    WNDPROC pWindowOriginal;

    /// <summary>
    /// Handlers
    /// </summary>
    void RunHooks( ) noexcept;
    void ReleaseHooks( ) noexcept;
  };

  inline CHooking g_Hooking;
} // namespace Utils