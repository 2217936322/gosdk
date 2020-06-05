#pragma once

#include "../../../utilities/global.hpp"
#include "../classes/convar.hpp"

/* Indexes */
enum EConsoleIndexes : short { FindVar_index = 15 };

namespace CS::Interfaces {
  class IConsole {
  public:
    constexpr auto FindVar( const char * name ) noexcept {
      return Utils::g_Memory.CallVirtualMethod<CS::Classes::CConvar *, const char *>(
          this, EConsoleIndexes::FindVar_index, name );
    }
  };
} // namespace CS::Interfaces