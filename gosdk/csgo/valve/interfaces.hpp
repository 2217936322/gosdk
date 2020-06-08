#pragma once

#include "../../dependencies/global.hpp"
#include "../../utilities/global.hpp"
#include "interfaces/global.hpp"

namespace CS {
  class CInterfaces {
  public:
    Interfaces::IConsole * g_pConsole{ };
    Interfaces::ISurface * g_pSurface{ };
    Interfaces::IInputSystem * g_pInputSystem{ };
    Interfaces::IPanel * g_pPanel{ };
    Interfaces::IBaseClientDLL * g_pClient{ };
    Interfaces::IClientMode * g_pClientMode{ };
    Interfaces::IEntityList * g_pEntityList{ };
    Interfaces::IEngineClient * g_pEngineClient{ };
    Interfaces::IGlobalVars * g_pGlobalVars{ };
    Interfaces::IDebugOverlay * g_pDebugOverlay{ };
    IDirect3DDevice9 * g_pDevice{ };

    void RunInterfaces( ) noexcept;
    void ReleaseInterfaces( ) noexcept;
  };

  inline CInterfaces g_Interfaces;
} // namespace CS