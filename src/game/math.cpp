#pragma once

#include <utility>
#include <math.h>

#define PI 3.14159274101257324219

class Math {
public:
    static float degToRadian(float deg) {
        return deg * PI / 180;
    }

    static float radianToDeg(float radian) {
        return radian * 180 / PI;
    }

    static std::pair<float, float> cartesianToPolar(float x, float y) {
        float h = hypot(x, y);
        float rad = atan2(y, x);
        float deg = Math::radianToDeg(rad);
        if(deg < 0) {
            deg += 360;
        }

        return {h, deg};
    };

    static std::pair<float, float> polarToCartesian(float length, float degree) {
        float x = cos(Math::degToRadian(degree)) * length;
        float y = sin(Math::degToRadian(degree)) * length;
        return {x, y};
    }
};