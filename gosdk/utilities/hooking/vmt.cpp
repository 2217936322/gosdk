#include "vmt.hpp"

namespace Utils {
  CVMT::CVMT( ) = default;

  bool CVMT::bInit( void * base ) {
    if ( !base )
      return false;

    VMTBase = static_cast<std::uintptr_t **>( base );

    if ( !VMTBase )
      return false;

    OriginalVMT = *VMTBase;

    if ( !OriginalVMT )
      return false;

    VirtualProtect( VMTBase, sizeof( std::uintptr_t ), PAGE_READWRITE, &OldProtection );

    TableLength = GetVTLength( OriginalVMT );

    if ( !TableLength )
      return false;

    ReplaceVMT = std::make_unique<std::uintptr_t[]>( TableLength + 1 );

    if ( !ReplaceVMT )
      return false;

    std::memset( ReplaceVMT.get( ), 0, TableLength * sizeof( std::uintptr_t ) + sizeof( std::uintptr_t ) );
    std::memcpy( &ReplaceVMT[ 1 ], OriginalVMT, TableLength * sizeof( std::uintptr_t ) );
    std::memcpy( ReplaceVMT.get( ), &OriginalVMT[ -1 ], sizeof( std::uintptr_t ) );

    *VMTBase = &ReplaceVMT[ 1 ];

    return true;
  }

  bool CVMT::bHookFunction( const std::uint16_t index, void * function ) {
    if ( !ReplaceVMT || index < 0 || index > TableLength )
      return false;

    ReplaceVMT[ index + 1 ] = reinterpret_cast<std::uintptr_t>( function );

    return true;
  }

  bool CVMT::bUnhookFunction( const std::uint16_t index ) {
    if ( !OriginalVMT || !ReplaceVMT || index < 0 || index > TableLength )
      return false;

    ReplaceVMT[ index + 1 ] = OriginalVMT[ index ];

    return true;
  }

  bool CVMT::bUnhook( ) {
    if ( !OriginalVMT )
      return false;

    VirtualProtect( VMTBase, sizeof( std::uintptr_t ), PAGE_READWRITE, &OldProtection );
    *VMTBase = OriginalVMT;

    OriginalVMT = nullptr;

    return true;
  }

  std::uintptr_t CVMT::GetVTLength( std::uintptr_t * table ) {
    std::uintptr_t length = std::uintptr_t{ };

    // walk through every function until it is no longer valid
    for ( length = 0; table[ length ]; length++ )
      if ( IS_INTRESOURCE( table[ length ] ) )
        break;

    return length;
  }
}; // namespace Utils
