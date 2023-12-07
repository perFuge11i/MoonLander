#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include "AABB.hpp"
#include "GJKcomputations.hpp"
#include "PhysicsEngine.hpp"
#include "Spaceship.hpp"
#include "Landscape.hpp"
#include "UI.hpp"
#include <cmath>

//Testcases er inspirert fra Chat-gpt og endret etter behov

// Test for AABB class
TEST_CASE("AABB position and size are set correctly", "[AABB]") {
    AABB box;
    box.setPosition(10, 20);
    box.setSize(30, 40);

    REQUIRE(box.getEdges() == std::vector<float>{25, -5, 40, 0});
}

// Test for GJKengine class
TEST_CASE("GJKengine vector operations", "[GJKengine]") {
    GJKengine gjk;

    SECTION("Vector addition") {
        REQUIRE(gjk.vectorAddition({1, 2}, {3, 4}) == std::vector<float>{4, 6});
    }

    SECTION("Vector subtraction") {
        REQUIRE(gjk.vectorSubtraction({3, 4}, {1, 2}) == std::vector<float>{2, 2});
    }

    SECTION("Dot product") {
        REQUIRE(gjk.dotProduct({1, 2}, {3, 4}) == Catch::Approx(11));
    }

    SECTION("Cross product") {
        std::vector<float> v1 = {1, 2, 3};
        std::vector<float> v2 = {4, 5, 6};
        auto result = gjk.crossProduct(v1, v2);

        REQUIRE(result[0] == Catch::Approx(-3));
        REQUIRE(result[1] == Catch::Approx(6));
        REQUIRE(result[2] == Catch::Approx(-3));
    }

    SECTION("Support function") {
        std::vector<std::vector<float>> vertices = {{1, 1}, {2, 2}, {3, 3}};
        std::vector<float> direction = {1, 1};
        std::vector<float> center = {0, 0};
        auto supportPoint = gjk.supportFunction(direction, vertices, center);

        REQUIRE(supportPoint == std::vector<float>{3, 3});
    }

    SECTION("Passed Origo") {
        std::vector<float> point = {1, 1};
        std::vector<float> direction = {1, 1};

        REQUIRE(gjk.passedOrigo(point, direction) == true);

        point = {-1, -1};
        REQUIRE(gjk.passedOrigo(point, direction) == false);
    }
}

// Test for PhysicsEngine class
TEST_CASE("PhysicsEngine movement calculation", "[PhysicsEngine]") {
    PhysicsEngine physics(0, 0);

    SECTION("Calculate next movement") {
        physics.calculateForce(M_PI_2);
        auto movement = physics.calculateNextMovement(1.0f);
        REQUIRE(movement[0] == Catch::Approx(0).margin(0.01));
        REQUIRE(movement[1] < 0); // Should be moving downwards due to gravity
    }

    SECTION("Collision detection") {
        Spaceship ship(50, 50);
        Landscape landscape(0, 0);
        landscape.addLine(10, 0); // Adding a flat line

        // Test for no collision when spaceship and landscape line are apart
        std::vector<float> linePosition = landscape.getLines().back().position;
        std::vector<float> movement = {linePosition[0]-ship.getPosition()[0],linePosition[1]-ship.getPosition()[1]};
        REQUIRE_FALSE(physics.AABBcollision(ship.getShip(), landscape.getLines().back()));

        ship.move(movement); // Position the ship near the line

        // Test for collision when spaceship and landscape line are close
        REQUIRE(physics.AABBcollision(ship.getShip(), landscape.getLines().back()));
    }
}

// Test for UI class
TEST_CASE("UI command registration", "[UI]") {
    UI ui;
    ui.onKeyPressed(threepp::KeyEvent(threepp::Key::UP, true, false));

    REQUIRE(ui.searchCommands("FORWARD") == true);
}


