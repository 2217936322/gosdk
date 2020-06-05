#pragma once

// D3D9
#include <d3d9.h>
#include <d3dx9.h>
#include <dwmapi.h>

/// <summary>
/// Watch out, CMake users!
/// Anyway, if you're using CMake you might aswell
/// just consider writing your prerequisite includes
///  within one pcx file and not have to bother about
/// these ever again. Pragma commenting is VS
/// solutioning system specific.
/// </summary>
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "dwmapi.lib" )