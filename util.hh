#pragma once
#include <math.h>

inline float dbCo(float g) {
    return powf(10.0f, g*0.05f);
}