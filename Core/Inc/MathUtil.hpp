#pragma once

#include "main.h"
//#include "arm_math.h"

#define M_MIN(a, b) ((a) < (b) ? (a) : (b))
#define M_MAX(a, b) ((a) > (b) ? (a) : (b))

#define M_ABS(x) ((x) < 0 ? -(x) : (x))
#define M_ABS_GREATER_THAN(x, bound) ( ((x) > (bound)) || ((x) < -(bound)) )

#define M_CLAMP(x, min, max) (M_MIN((max), M_MAX((min), (x))))