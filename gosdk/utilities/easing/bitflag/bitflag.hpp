#pragma once

#include <inttypes.h>

namespace Utils::Easing {
  struct BitFlag {
    uintptr_t u_pFlags{ };

    constexpr BitFlag( ) = default;

    constexpr BitFlag( const uintptr_t flags ) : u_pFlags( flags ) {}

    ~BitFlag( ) = default;

    /// <summary>
    /// Function made to return pointer to BitFlag object and cast it to a specific datatype
    /// </summary>
    /// <returns>Function casted to automatically deducted type or specified type</returns>
    template <typename T> constexpr T pThis( ) noexcept { return reinterpret_cast<T>( *this ); }

    inline constexpr bool bCheckFlag( const uintptr_t flag ) noexcept { return u_pFlags & flag; }

    inline constexpr void AddFlag( const uintptr_t flag ) noexcept { u_pFlags |= flag; }

    inline constexpr void RemoveFlag( const uintptr_t flag ) noexcept { u_pFlags &= ~flag; }

    inline constexpr bool bIsEmpty( ) noexcept { return !u_pFlags; }
  };
} // namespace Utils::Easing
