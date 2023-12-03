#ifndef MOONLANDER_LUNARLANDERGAME_HPP
#define MOONLANDER_LUNARLANDERGAME_HPP

//linje 26: innspill fra chatGPT

#include "MoonScene.hpp"
#include "Spaceship.hpp"
#include "Landscape.hpp"
#include "UI.hpp"
#include "PhysicsEngine.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "threepp/threepp.hpp"


class LunarLanderGame {
private:
    MoonScene scene;
    Spaceship lunarLander;
    Landscape lunarSurface;
    UI keyInputs;
    PhysicsEngine rocketPhysics;

    bool collision = false;
    float landscapeLength = 0;
    std::vector<float> landscapeBorder = {0,0};
    std::vector<std::vector<float>> surfaceLines = {{5, 0},{3, M_PI_2 - M_PI_4/4},{5, M_PI_2 - M_PI_4/8},
                                                    {3, M_PI_2},{2, 0},{5, M_PI_2 - M_PI_4/4},
                                                    {4, M_PI_4},{2, M_PI_2 - M_PI_4/4},{2, M_PI_2 - M_PI_4/8},
                                                    {3, M_PI/3},{2, 0},{7, M_PI_2 - M_PI_4/4},
                                                    {2, M_PI/6},{3, -M_PI_4},{5, M_PI_2 - M_PI_4/4},
                                                    {2, M_PI/6},{2, M_PI_2 - M_PI_4/8},{2, M_PI_4 + M_PI_4/4},
                                                    {2, M_PI_4},{2, 0},{2, -(M_PI_2 - M_PI_4/4)},
                                                    {2, 0},{2, -(M_PI_2 - M_PI_4/4)},{1, 0},
                                                    {5, -(M_PI_2 - M_PI_4/8)},{5, -(M_PI_2 - M_PI_4/4)},{2, -M_PI_2},
                                                    {3, -(M_PI_2 - M_PI_4/6)},{3, -(M_PI_2 - M_PI_4)},{3, -(M_PI_2 - M_PI_4/8)},
                                                    {2, -(M_PI_2 - M_PI_4/3)},{2, -(M_PI_4 - M_PI_4/4)},{2, 0},
                                                    {2, M_PI_4},{3, M_PI_2 - M_PI_4/2},{2, M_PI_4 + M_PI/12},
                                                    {2, M_PI_4 + M_PI_4/8},{1, M_PI_2 - M_PI_4/2},{2, M_PI_4 + M_PI_4/8},
                                                    {1, M_PI_2 - M_PI_4/2},{2, M_PI/6},{3, M_PI_2 - M_PI_4/2},
                                                    {2, M_PI/6},{2, M_PI_2 - M_PI_4},{2, 0},
                                                    {2, -M_PI/12},{2, -(M_PI_4 + M_PI_4/8)},{1, -(M_PI_2 - M_PI_4/8)},
                                                    {2, -(M_PI_2 - M_PI_4/2)},{1, -(M_PI_2 - M_PI_4/8)},{2, -(M_PI_2 - M_PI_4/2)},
                                                    {1, -(M_PI_2 - M_PI_4/8)},{2, -(M_PI_2 - M_PI_4/2)},{2, 0},
                                                    {3, M_PI_2 - M_PI_4/4},{1, M_PI_4},{1, -M_PI/6},
                                                    {2, -(M_PI_4 + M_PI_4/4)},{3, -(M_PI_2 - M_PI_4/6)},{3, -M_PI/6},
                                                    {5, -(M_PI_2 - M_PI_4/6)},{5, -(M_PI_2 - M_PI_4/4)},{1, -M_PI_2},
                                                    {2, -(M_PI_4 - M_PI_4/4)},{3, 0},{5, M_PI_4},
                                                    {2, M_PI_4 + M_PI_4/3},{2, M_PI_4},{2, M_PI_4 + M_PI_4/3},
                                                    {2, M_PI_4 - M_PI_4/4},{5, M_PI_2 - M_PI_4/6},{2, M_PI_4 - M_PI_4/4}};
public:

    LunarLanderGame() : lunarSurface(0, 40), rocketPhysics(10, 0), lunarLander(30, 120), scene(150) {
        for (const auto line: surfaceLines) {
            lunarSurface.addLine(line[0], line[1]);
        }
        landscapeLength = lunarSurface.getLength();

        for (const auto line: lunarSurface.getLines()) {
            scene.addObject(line.mesh);
        }
        scene.addObject(lunarLander.getShip().mesh);
    }

    void update(const float dt) {
        std::vector<float> movement;
        bool isClose = false;

        if (keyInputs.searchCommands("RESET")) {
            lunarLander.reset();
            rocketPhysics.reset();
            collision = false;
        }

        if (!collision) {
            for (const auto line: lunarSurface.getLines()) {
                if (rocketPhysics.AABBcollision(lunarLander.getShip(), line)) {
                    isClose = true;
                    if (rocketPhysics.GJKcollision(lunarLander.getShip(), line)) {
                        collision = true;
                    }
                }
            }
            if (isClose) {
                scene.zoomIn();
            } else {
                scene.zoomOut();
            }

            if (keyInputs.searchCommands("LEFT")) {
                lunarLander.rotate(1, dt);
            }
            if (keyInputs.searchCommands("RIGHT")) {
                lunarLander.rotate(-1, dt);
            }
            if (keyInputs.searchCommands("FORWARD")) {
                rocketPhysics.calculateForce(lunarLander.getRotation());
            }

            movement = rocketPhysics.calculateNextMovement(dt);
            lunarLander.move(movement);
            scene.setCameraPosition(lunarLander.getPosition());
        }

        //If the spaceship is closer than one 'landscape' instance away from the border to the right
        if (lunarLander.getPosition()[0] > landscapeBorder[1]-(landscapeLength+20)) {
            //Add a new 'landscape' instance at the right border
            lunarSurface.newStartingPoint(landscapeBorder[1], 40);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                scene.addObject(lunarSurface.getLines().back().mesh);
            }
            //update right boundary
            landscapeBorder[1] += landscapeLength;
            //If the spaceship is closer than one 'landscape' instance away from the border to the left
        } else if (lunarLander.getPosition()[0] < landscapeBorder[0]+(landscapeLength+20)) {
            //Add a new 'landscape' instance at the left border
            lunarSurface.newStartingPoint(landscapeBorder[0]-landscapeLength, 40);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                scene.addObject(lunarSurface.getLines().back().mesh);
            }
            //update left border
            landscapeBorder[0] -= landscapeLength;
        }

    }

    MoonScene &getScene() {
        return scene;
    }

    threepp::OrthographicCamera &getCamera() {
        return scene.camera();
    }

    UI &getUI() {
        return keyInputs;
    }
};

#endif //MOONLANDER_LUNARLANDERGAME_HPP
