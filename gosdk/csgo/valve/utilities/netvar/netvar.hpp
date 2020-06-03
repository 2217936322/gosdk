#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace CS {
  class CNetvar {
  public:
    std::unordered_map<std::string, std::uintptr_t> Offsets;

    /// <summary>
    /// Handler
    /// </summary>
    void Init( );
  };

  inline CNetvar g_Netvar{ };
}; // namespace CS::Utils

/* Handlers */
// clang-format off
#define netvar_additive(t, func, name, off)\
	t &func()\
	{\
		static auto offset = CS::g_Netvar.Offsets[(STR(name))];\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset + off);\
	}

#define netvar(t, func, name)\
	t &func()\
	{\
		static auto offset = CS::g_Netvar.Offsets[(STR(name))];\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset);\
	}

#define offset(t, func, offset)\
	t &func()\
	{\
		return *reinterpret_cast<t*>(std::uintptr_t(this) + offset);\
	}

#define poffset(t, func, offset)\
	t func()\
	{\
		return reinterpret_cast<t>(std::uintptr_t(this) + offset);\
	}
// clang-format on