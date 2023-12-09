#ifndef MOONLANDER_LUNARLANDERGAME_HPP
#define MOONLANDER_LUNARLANDERGAME_HPP

//linje 82: innspill fra chatGPT (definere parametre for constructors)
//linje 97-100: Random number generation fra chatGPT
//linje ???-???: Sleep function from chatGPT
#include "MoonScene.hpp"
#include "Spaceship.hpp"
#include "Landscape.hpp"
#include "UI.hpp"
#include "PhysicsEngine.hpp"
#include "HUD.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

class LunarLanderGame {
private:
    MoonScene scene;
    Spaceship lunarLander;
    Landscape lunarSurface;
    UI keyInputs;
    PhysicsEngine rocketPhysics;
    HUD HUD;

    float time = 0;
    float score = 0;
    //float altitude = 0;
    std::vector<int> multiplierRange = {0,0};
    int numberOfx2multipliers = 0;
    int numberOfx4multipliers = 0;
    int numberOfx5multipliers = 0;
    std::vector<float> x2Level = {0, 0};
    std::vector<float> x4Level = {0, 0};
    std::vector<float> x5Level = {0, 0};

    bool collision = false;
    float landscapeLength = 0;
    std::vector<float> landscapeBorder = {0,0};
    std::vector<std::vector<float>> surfaceLines = {{5, 0},{3, M_PI_2 - M_PI_4/4},{5, M_PI_2 - M_PI_4/8},
                                                    {3, M_PI_2},{2, 0},{5, M_PI_2 - M_PI_4/4},
                                                    {4, M_PI_4},{2, M_PI_2 - M_PI_4/4},{2, M_PI_2 - M_PI_4/8},
                                                    {3, M_PI/3},{2, 0},{7, M_PI_2 - M_PI_4/4},
                                                    {2, M_PI/6},{2, -M_PI_4},{2, 0},{2, M_PI_4},{5, M_PI_2 - M_PI_4/4},
                                                    {2, M_PI/6},{1.5, M_PI_2 - M_PI_4/8},{2, M_PI_4 + M_PI_4/4},
                                                    {2, M_PI_4},{2, 0},{2, -(M_PI_2 - M_PI_4/4)},
                                                    {1.5, 0},{2, -(M_PI_2 - M_PI_4/4)},{1, 0},
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
                                                    {5, -(M_PI_2 - M_PI_4/6)},{5, -(M_PI_2 - M_PI_4/4)},{3, -M_PI_2},
                                                    {3, -(M_PI_2 - M_PI_4)},{3, -(M_PI_2 - M_PI_4/8)},{2, -(M_PI_2 - M_PI_4/3)},
                                                    {2, -(M_PI_4 - M_PI_4/4)},{3, 0},{5, M_PI_4},
                                                    {2, M_PI_4 + M_PI_4/3},{2, M_PI_4},{1, M_PI_4 + M_PI_4/3},
                                                    {2, M_PI/6},{4, (M_PI_2 - M_PI_4/6)},{3, (M_PI_2 - M_PI_4/5)},
                                                    {1.5, M_PI/6},{2, M_PI_4 + M_PI_4/4},{2, (M_PI_4 + M_PI_4/3)},
                                                    {3, M_PI_4 + M_PI_4/2},{2, M_PI_4 + M_PI_2/3},{2, M_PI_4},
                                                    {1.5, M_PI_4 + M_PI_4/2},{1, M_PI_4 + M_PI_2/3},
                                                    {1.5, M_PI/3},{1,0},{1,M_PI_4},
                                                    {2, M_PI/3},{2,M_PI_4},{6, M_PI_4 + M_PI/5},
                                                    {3,M_PI_2},{2, M_PI_4 + 2*M_PI/9},{3, M_PI_4 + M_PI_2/3},
                                                    {1, M_PI_2/3},{1, M_PI_4 + M_PI/6},{1.5, M_PI/3},
                                                    {1,0},{1.5, -(M_PI_4 + M_PI/6)},
                                                    {1.5,0},{1.5, -(M_PI_4 + M_PI/6)},{0.5,0},
                                                    {1, -M_PI_2/3},{1,-M_PI/3},{2, -(M_PI_4 + M_PI/6)},
                                                    {2, -M_PI_2/3},{3, -(M_PI_4 + M_PI/6)},{1, -M_PI_2/8},
                                                    {1.5, -M_PI_2/2},{1, -(M_PI_4 + M_PI/6)},{1.5,-M_PI/3},
                                                    {1, -(M_PI_4 + M_PI/6)},{1.5,-M_PI/3},{1.5,0},
                                                    {4,-(M_PI_2 - M_PI_2/24)},{4, -(M_PI_4 + M_PI/6)},{1,-M_PI_2},
                                                    {1,0},{1, -(M_PI_4 + M_PI/7)},{1.5,-M_PI/3},
                                                    {3, -(M_PI_4 + M_PI/5)},{1.5, -(M_PI_4 + M_PI/8)},{2,-(M_PI/3 - M_PI_4/4)},
                                                    {4,-(M_PI_2 - M_PI_2/24)},{4, -(M_PI_4 + M_PI/6)},{1,-M_PI_2},
                                                    {1, -(M_PI_4 + M_PI/7)},{1.5,-(M_PI/3-M_PI_4/4)},{1,0},
                                                    {2, -(M_PI_4 + M_PI/6)},{1, -(M_PI_4 + M_PI_4/6)},{3,-(M_PI/3 - M_PI_4/4)},
                                                    {5,0},{4,M_PI_2 - M_PI_2/12},{3, M_PI_4 + M_PI/8},
                                                    {2, M_PI_4 + M_PI/6},{0.5,M_PI_4/6},{2, M_PI_4 + M_PI/6},
                                                    {1,M_PI/3 - M_PI_4/3},{2, M_PI_4 + M_PI/8},{1,M_PI/3 - M_PI_4},
                                                    {1,M_PI/3 - M_PI_4/3},{1.5,0},{1, -(M_PI_4 + M_PI/6)},
                                                    {4, -(M_PI_4 + M_PI/7)},{1,-(M_PI_2 - M_PI_2/8)},{1,-(M_PI_4+M_PI_4/6)},
                                                    {1,-(M_PI_4-M_PI_4/4)},{1,-(M_PI_4+M_PI_4/6)},{4,-(M_PI_2 - M_PI_2/8)},
                                                    {2,-(M_PI_4+M_PI_4/6)},{2,0},{2,-M_PI_4/6},
                                                    {2,-(M_PI_4-M_PI_4/2)}};
public:

    LunarLanderGame() : lunarSurface(0, 20), rocketPhysics(10, 0), lunarLander(75, 120), scene(150) {
        for (const auto line: surfaceLines) {
            lunarSurface.addLine(line[0], line[1]);
        }
        landscapeLength = lunarSurface.getLength();
        landscapeBorder[1] += landscapeLength;

        multiplierRange = {0, static_cast<int>(lunarSurface.getLines().size())-1};
        numberOfx2multipliers = 2;
        numberOfx4multipliers = 3;
        numberOfx5multipliers = 1;
        x2Level = {0, 0.16};
        x4Level = {x2Level[1], 0.83};
        x5Level = {x4Level[1], 1.};


        lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
        lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
        lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);

        for (const auto line: lunarSurface.getLines()) {
            scene.addToScene(line.mesh);
        }
        scene.addToScene(lunarLander.getShip().mesh);
        scene.addToScene(HUD.getHUD());
        HUD.setElement("Fuel", lunarLander.getFuel());
        HUD.setElement("Score", score);
    }

    void update(const float dt) {
        std::vector<float> movement;
        bool isClose = false;
        time += dt;
        HUD.setTime(time);

        if (keyInputs.searchCommands("RESET")) {
            newRound();
        }

        if (!collision) {
            for (const auto line: lunarSurface.getLines()) {
                if (rocketPhysics.AABBcollision(lunarLander.getShip(), line)) {
                    isClose = true;
                    if (rocketPhysics.GJKcollision(lunarLander.getShip(), line)) {
                        collision = true;
                        if (rocketPhysics.isSoftLanding(lunarLander.getShip().angle, line.angle)) {
                            score += 50*line.multiplier;
                            HUD.setElement("Score", score);
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        } else {
                            crashAnimation();
                        }
                        newRound();
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
                lunarLander.useFuel();
                HUD.setElement("Fuel", lunarLander.getFuel());
            }

            movement = rocketPhysics.calculateNextMovement(dt);
            lunarLander.move(movement);

            scene.setCameraPosition(lunarLander.getPosition());
            HUD.setPosition(scene.getCameraPosition());
            HUD.setScale(scene.getCameraScale());

            /*if (static_cast<int>(time*100)%20 < 1) {
                HUD.setElement("Altitude", lunarLander.getPosition()[1]-lunarSurface.closestHeightBelow(lunarLander.getPosition()[0])-2);
                HUD.setElement("Horizontal Speed", static_cast<int>(movement[0] * 100));
                HUD.setElement("Vertical Speed", static_cast<int>(movement[1] * 100));
            }*/
        }

        //If the spaceship is closer than one 'landscape' instance away from the border to the right
        if (lunarLander.getPosition()[0] > landscapeBorder[1]-(landscapeLength+20)) {
            //Add a new 'landscape' instance at the right border
            lunarSurface.newStartingPoint(landscapeBorder[1], 20);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                scene.addToScene(lunarSurface.getLines().back().mesh);
            }
            //Add multipliers to new landscape
            multiplierRange = {static_cast<int>(lunarSurface.getLines().size())-static_cast<int>(surfaceLines.size())-1,
                               static_cast<int>(lunarSurface.getLines().size())-1};
            lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
            lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
            lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);
            //update right boundary
            landscapeBorder[1] += landscapeLength;
            //If the spaceship is closer than one 'landscape' instance away from the border to the left
        } else if (lunarLander.getPosition()[0] < landscapeBorder[0]+(landscapeLength+20)) {
            //Add a new 'landscape' instance at the left border
            lunarSurface.newStartingPoint(landscapeBorder[0]-landscapeLength, 20);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                scene.addToScene(lunarSurface.getLines().back().mesh);
            }
            //Add multipliers to new landscape
            multiplierRange = {static_cast<int>(lunarSurface.getLines().size())-static_cast<int>(surfaceLines.size())-1,
                               static_cast<int>(lunarSurface.getLines().size())-1};
            lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
            lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
            lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);
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

    void newRound() {
        lunarSurface.reset();
        rocketPhysics.reset();
        scene.reset();
        lunarLander.crash();
        collision = false;
        landscapeBorder = {0, 0};

        for (const auto line: surfaceLines) {
            lunarSurface.addLine(line[0], line[1]);
        }
        landscapeLength = lunarSurface.getLength();
        landscapeBorder[1] += landscapeLength;

        multiplierRange = {0, static_cast<int>(lunarSurface.getLines().size()) - 1};
        lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
        lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
        lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);

        for (const auto line: lunarSurface.getLines()) {
            scene.addToScene(line.mesh);
        }
        scene.addToScene(lunarLander.getShip().mesh);
        scene.addToScene(HUD.getHUD());
        HUD.setElement("Fuel", lunarLander.getFuel());
        HUD.setElement("Score", score);
    }

    void newGame() {
        newRound();
        time = 0;
        score = 0;
        lunarLander.getShip().fuel = 1000;
    }
    void crashAnimation() {
        scene.removeFromScene(lunarLander.getShip().mesh);
        scene.addToScene(lunarLander.getExplosion());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));std::this_thread::sleep_for(std::chrono::milliseconds(500));
        scene.addToScene(lunarLander.getShip().mesh);
    }
};

#endif //MOONLANDER_LUNARLANDERGAME_HPP
