#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "game/misc/math.hpp"

using Catch::Matchers::WithinAbs;

TEST_CASE("Math::degToRadian") {
    REQUIRE_THAT(Math::degToRadian(0.0f),   WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(Math::degToRadian(90.0f),  WithinAbs(1.5708f, 0.001f));
    REQUIRE_THAT(Math::degToRadian(180.0f), WithinAbs(3.1416f, 0.001f));
    REQUIRE_THAT(Math::degToRadian(360.0f), WithinAbs(6.2832f, 0.001f));
}

TEST_CASE("Math::radianToDeg") {
    REQUIRE_THAT(Math::radianToDeg(0.0f),    WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(Math::radianToDeg(1.5708f), WithinAbs(90.0f, 0.001f));
    REQUIRE_THAT(Math::radianToDeg(3.1416f), WithinAbs(180.0f, 0.001f));
}

// Screen space: x+ = right, y+ = down (top-left origin)
// Compass convention: 0° = up, 90° = right, 180° = down, 270° = left
TEST_CASE("Math::cartesianToPolar") {
    SECTION("up -> 0 degrees") {
        auto [length, deg] = Math::cartesianToPolar(0.0f, -1.0f);
        REQUIRE_THAT(length, WithinAbs(1.0f, 0.001f));
        REQUIRE_THAT(deg,    WithinAbs(0.0f, 0.001f));
    }

    SECTION("right -> 90 degrees") {
        auto [length, deg] = Math::cartesianToPolar(1.0f, 0.0f);
        REQUIRE_THAT(length, WithinAbs(1.0f, 0.001f));
        REQUIRE_THAT(deg,    WithinAbs(90.0f, 0.001f));
    }

    SECTION("down -> 180 degrees") {
        auto [length, deg] = Math::cartesianToPolar(0.0f, 1.0f);
        REQUIRE_THAT(length, WithinAbs(1.0f, 0.001f));
        REQUIRE_THAT(deg,    WithinAbs(180.0f, 0.001f));
    }

    SECTION("left -> 270 degrees") {
        auto [length, deg] = Math::cartesianToPolar(-1.0f, 0.0f);
        REQUIRE_THAT(length, WithinAbs(1.0f, 0.001f));
        REQUIRE_THAT(deg,    WithinAbs(270.0f, 0.001f));
    }

    SECTION("degrees is between 0 - 360") {
        for(auto x = -1.0f ; x < 1.0f; x += 0.1f ) {
            for(auto y = -1.0f ; y < 1.0f; y += 0.1f ) {
                auto [length, deg] = Math::cartesianToPolar(x, y);
                REQUIRE(deg >= 0.0f);
                REQUIRE(deg < 360.0f);
            }   
        }
    }
}

TEST_CASE("Math::polarToCartesian") {
    SECTION("0 degrees -> vector up") {
        auto [x, y] = Math::polarToCartesian(1.0f, 0.0f);
        REQUIRE_THAT(x, WithinAbs(0.0f, 0.001f));
        REQUIRE_THAT(y, WithinAbs(-1.0f, 0.001f));
    }

    SECTION("90 degrees -> vector right") {
        auto [x, y] = Math::polarToCartesian(1.0f, 90.0f);
        REQUIRE_THAT(x, WithinAbs(1.0f, 0.001f));
        REQUIRE_THAT(y, WithinAbs(0.0f, 0.001f));
    }

    SECTION("180 degrees -> vector down") {
        auto [x, y] = Math::polarToCartesian(1.0f, 180.0f);
        REQUIRE_THAT(x, WithinAbs(0.0f, 0.001f));
        REQUIRE_THAT(y, WithinAbs(1.0f, 0.001f));
    }

    SECTION("270 degrees -> vector right") {
        auto [x, y] = Math::polarToCartesian(1.0f, 270.0f);
        REQUIRE_THAT(x, WithinAbs(-1.0f, 0.001f));
        REQUIRE_THAT(y, WithinAbs(0.0f, 0.001f));
    }
}
