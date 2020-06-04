#include "interfaces.hpp"

namespace CS {
  void CInterfaces::RunInterfaces( ) noexcept {
    g_pClient = reinterpret_cast<Interfaces::IBaseClientDLL *>(
        Utils::g_Memory.ScanInterface( STR( "client.dll" ), STR( "VClient018" ) ) );

    if ( !g_pClient )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pClient | client.dll | VClient018" ) );

    g_pClientMode = **reinterpret_cast<Interfaces::IClientMode ***>( ( *reinterpret_cast<uintptr_t **>( g_pClient ) )[ 10 ] + 5 );

    if ( !g_pClientMode )
      Utils::g_Console.Log<std::string_view>(
          STR( "failed @ g_pClientMode | check source for more information..." ) ); // ohh yeahh ohh yeahh ohh yeaaaaahhh

    g_pGlobalVars =
        **reinterpret_cast<Interfaces::IGlobalVars ***>( ( *reinterpret_cast<uintptr_t **>( g_pClient ) )[ 11 ] + 10 );

    if ( !g_pGlobalVars )
      Utils::g_Console.Log<std::string_view>(
          STR( "failed @ g_pGlobalVars | check source for more information..." ) ); // ohh yeahh ohh yeahh ohh yeaaaaahhh x2

    g_pEntityList = reinterpret_cast<Interfaces::IEntityList *>(
        Utils::g_Memory.ScanInterface( STR( "client.dll" ), STR( "VClientEntityList003" ) ) );

    if ( !g_pEntityList )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pEntityList | client.dll | VClientEntityList003" ) );

    g_pEngineClient = reinterpret_cast<Interfaces::IEngineClient *>(
        Utils::g_Memory.ScanInterface( STR( "engine.dll" ), STR( "VEngineClient014" ) ) );

    if ( !g_pEngineClient )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pEngineClient | engine.dll | VEngineClient014" ) );

    g_pDebugOverlay = reinterpret_cast<Interfaces::IDebugOverlay *>(
        Utils::g_Memory.ScanInterface( STR( "engine.dll" ), STR( "VDebugOverlay004" ) ) );

    if ( !g_pDebugOverlay )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pDebugOverlay | engine.dll | VDebugOverlay004" ) );

    g_pConsole = reinterpret_cast<Interfaces::IConsole *>(
        Utils::g_Memory.ScanInterface( STR( "vstdlib.dll" ), STR( "VEngineCvar007" ) ) );

    if ( !g_pConsole )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pConsole | vstdlib.dll | VEngineCvar007" ) );

    g_pSurface = reinterpret_cast<Interfaces::ISurface *>(
        Utils::g_Memory.ScanInterface( STR( "vguimatsurface.dll" ), STR( "VGUI_Surface031" ) ) );

    if ( !g_pSurface )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pSurface | vguimatsurface.dll | VGUI_Surface031" ) );

    g_pDevice = **reinterpret_cast<IDirect3DDevice9 ***>(
        Utils::g_Memory.FindPattern( STR( "shaderapidx9.dll" ), STR( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 1 );

    if ( !g_pDevice )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pDevice | shaderapidx9.dll | A1 ? ? ? ? 50 8B 08 FF 51 0C" ) );

    g_pInputSystem = reinterpret_cast<Interfaces::IInputSystem *>(
        Utils::g_Memory.ScanInterface( STR( "inputsystem.dll" ), STR( "InputSystemVersion001" ) ) );

    if ( !g_pInputSystem )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pInputSystem | inputsystem.dll | InputSystemVersion001" ) );

    g_pPanel =
        reinterpret_cast<Interfaces::IPanel *>( Utils::g_Memory.ScanInterface( STR( "vgui2.dll" ), STR( "VGUI_Panel009" ) ) );

    if ( !g_pPanel )
      Utils::g_Console.Log<std::string_view>( STR( "failed @ g_pPanel | vgui2.dll | VGUI_Panel009" ) );
  }

  void CInterfaces::ReleaseInterfaces( ) noexcept {
    g_pConsole = nullptr;
    g_pSurface = nullptr;
    g_pDevice = nullptr;
    g_pInputSystem = nullptr;
    g_pPanel = nullptr;
    g_pClient = nullptr;
    g_pClientMode = nullptr;
    g_pEntityList = nullptr;
    g_pEngineClient = nullptr;
    g_pGlobalVars = nullptr;
    g_pDebugOverlay = nullptr;
  }
} // namespace CS
