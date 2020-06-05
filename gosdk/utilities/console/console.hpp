#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

namespace Utils {
  static HWND ConsoleHandle{ };

  class CConsole {
  public:
    /* Handlers */
    inline void RunConsole( const LPCSTR & name, const std::string & init_message ) {
      ConsoleHandle = GetConsoleWindow( );

      AllocConsole( );
      freopen_s( reinterpret_cast<FILE **>( stdin ), "CONIN$", "r", stdin );
      freopen_s( reinterpret_cast<FILE **>( stdout ), "CONOUT$", "w", stdout );

      constexpr static RECT rect = { 100, 100, 600, 600 };
      MoveWindow( ConsoleHandle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE );

      static LONG_PTR style = GetWindowLongPtr( ConsoleHandle, GWL_STYLE );
      SetWindowLong( ConsoleHandle, GWL_STYLE, style & ~WS_SIZEBOX & ~WS_SYSMENU );

      SetConsoleTitle( name );
      std::cout << init_message << std::endl;
    }

    inline void ReleaseConsole( ) {
      ConsoleHandle = GetConsoleWindow( );

      fclose( stdin );
      fclose( stdout );

      FreeConsole( );
      PostMessageW( ConsoleHandle, WM_CLOSE, 0, 0 );
      Beep( 10, 1000 );
    }

    template <typename T> void Log( T ref ) {
      std::cout << "[gosdk] - ";
      std::cout << ref << std::endl;
    }
  };

  inline CConsole g_Console{ };
} // namespace Utils
