#pragma once

// MATH
constexpr static double M_PI = 3.14159265358979323846;
constexpr static float M_RADPI = 57.295779513082f;
constexpr static float M_PI_F = static_cast<float>( M_PI );
constexpr float RAD2DEG( const float x ) { return x * ( 180.f / M_PI_F ); }
constexpr float DEG2RAD( const float x ) { return x * ( M_PI_F / 180.f ); }

// MATH INCLUDES
#include "vector2d.hpp"
#include "vector3d.hpp"
