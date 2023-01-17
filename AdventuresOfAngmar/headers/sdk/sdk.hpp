#pragma once

#define GEN_COMBINE(x, y, z, i) x ## y ## z ## i
#define COMBINE(x, y, z, i) GEN_COMBINE(x, y, z, i)
#define PAD(bytes) private: char COMBINE( __pad_, __COUNTER__, _, __LINE__ ) [bytes]; public:

#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))

#define RAD2DEG(x) ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD(x) ( (float)(x) * (float)(M_PI_F / 180.f) )

#include <Windows.h>

#include <thread>
#include <cmath>
#include <cstdint>

#include "Vector3.hpp"
#include "Offsets.hpp"

#include "ClientScreen.hpp"
#include "ClientCamera.hpp"
#include "ClientEntity.hpp"
#include "HealthPtr.hpp"
#include "MousePtr.hpp"
#include "TargetPtr.hpp"
#include "PlayerGeometry.hpp"