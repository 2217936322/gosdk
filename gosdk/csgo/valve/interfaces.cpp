#include "interfaces.hpp"

namespace CS {
  void CInterfaces::RunInterfaces( ) noexcept {
    g_pClient = reinterpret_cast<Interfaces::IBaseClientDLL *>( Utils::g_Memory.ScanInterface( "client.dll", "VClient018" ) );

    if ( !g_pClient )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pClient | client.dll | VClient018" );

    g_pClientMode = **reinterpret_cast<Interfaces::IClientMode ***>( ( *reinterpret_cast<uintptr_t **>( g_pClient ) )[ 10 ] + 0x5 );

    if ( !g_pClientMode )
      Utils::g_Console.Log<std::string_view>(
          "failed @ g_pClientMode | check source for more information..." ); // ohh yeahh ohh yeahh ohh yeaaaaahhh

    g_pGlobalVars =
        **reinterpret_cast<Interfaces::IGlobalVars ***>( ( *reinterpret_cast<uintptr_t **>( g_pClient ) )[ 11 ] + 0xA // 10 );

    if ( !g_pGlobalVars )
      Utils::g_Console.Log<std::string_view>(
          "failed @ g_pGlobalVars | check source for more information..." ); // ohh yeahh ohh yeahh ohh yeaaaaahhh x2

    g_pEntityList =
        reinterpret_cast<Interfaces::IEntityList *>( Utils::g_Memory.ScanInterface( "client.dll", "VClientEntityList003" ) );

    if ( !g_pEntityList )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pEntityList | client.dll | VClientEntityList003" );

    g_pEngineClient =
        reinterpret_cast<Interfaces::IEngineClient *>( Utils::g_Memory.ScanInterface( "engine.dll", "VEngineClient014" ) );

    if ( !g_pEngineClient )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pEngineClient | engine.dll | VEngineClient014" );

    g_pDebugOverlay =
        reinterpret_cast<Interfaces::IDebugOverlay *>( Utils::g_Memory.ScanInterface( "engine.dll", "VDebugOverlay004" ) );

    if ( !g_pDebugOverlay )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pDebugOverlay | engine.dll | VDebugOverlay004" );

    g_pConsole = reinterpret_cast<Interfaces::IConsole *>( Utils::g_Memory.ScanInterface( "vstdlib.dll", "VEngineCvar007" ) );

    if ( !g_pConsole )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pConsole | vstdlib.dll | VEngineCvar007" );

    g_pSurface =
        reinterpret_cast<Interfaces::ISurface *>( Utils::g_Memory.ScanInterface( "vguimatsurface.dll", "VGUI_Surface031" ) );

    if ( !g_pSurface )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pSurface | vguimatsurface.dll | VGUI_Surface031" );

    g_pDevice = **reinterpret_cast<IDirect3DDevice9 ***>(
        Utils::g_Memory.FindPattern( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 0x1 );

    if ( !g_pDevice )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pDevice | shaderapidx9.dll | A1 ? ? ? ? 50 8B 08 FF 51 0C" );

    g_pInputSystem = reinterpret_cast<Interfaces::IInputSystem *>(
        Utils::g_Memory.ScanInterface( "inputsystem.dll", "InputSystemVersion001" ) );

    if ( !g_pInputSystem )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pInputSystem | inputsystem.dll | InputSystemVersion001" );

    g_pPanel = reinterpret_cast<Interfaces::IPanel *>( Utils::g_Memory.ScanInterface( "vgui2.dll", "VGUI_Panel009" ) );

    if ( !g_pPanel )
      Utils::g_Console.Log<std::string_view>( "failed @ g_pPanel | vgui2.dll | VGUI_Panel009" );
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
