#ifndef MOONLANDER_LUNARLANDERGAME_HPP
#define MOONLANDER_LUNARLANDERGAME_HPP

//linje 82: innspill fra chatGPT (definere parametre for constructors)
//linje 97-100: Random number generation fra chatGPT
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
    GameScene moonScene;
    Spaceship lunarLander;
    Surface lunarSurface;
    UI keyInputs;
    PhysicsEngine rocketPhysics;
    HUD HUD;

    float time = 0;
    float timer1 = 0;
    float timer2 = 0;
    int score = 0;

    std::vector<int> multiplierRange = {0,0};
    int numberOfx2multipliers = 0;
    int numberOfx4multipliers = 0;
    int numberOfx5multipliers = 0;
    std::vector<float> x2Level = {0, 0};
    std::vector<float> x4Level = {0, 0};
    std::vector<float> x5Level = {0, 0};

    bool crash = false;
    bool landing = false;
    bool collision = false;
    bool isClose = false;

    float surfaceLength = 0;
    std::vector<float> surfaceBorder = {0,0};
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

    LunarLanderGame() : lunarSurface(0, 20), rocketPhysics(10, 0), lunarLander(75, 120), moonScene(150), HUD() {
        for (const auto line: surfaceLines) {
            lunarSurface.addLine(line[0], line[1]);
        }
        surfaceLength = lunarSurface.getLength();
        surfaceBorder[1] += surfaceLength;

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
            moonScene.addToScene(line.mesh);
        }
        moonScene.addToScene(lunarLander.getShip().mesh);
        moonScene.addToScene(HUD.getHUD());
        HUD.setElement("Fuel", lunarLander.getFuel());
        HUD.setElement("Score", score);
    }

    void update(const float dt) {
        time += dt;

        if (crash == true) {
            if (time < timer1 + 2) {
                if (moonScene.isInScene(lunarLander.getShip().mesh)) {
                    moonScene.removeFromScene(lunarLander.getShip().mesh);
                }
                if (!moonScene.isInScene(lunarLander.getExplosion())) {
                    moonScene.addToScene(lunarLander.getExplosion());
                }
                if (!moonScene.isInScene(HUD.getCenterText())) {
                    HUD.setCenterText("RETARD", 1);
                    moonScene.addToScene(HUD.getCenterText());
                }

                return;
            } else {
                newRound();
            }
        }
        if (!moonScene.isInScene(lunarLander.getShip().mesh)) {
            moonScene.addToScene(lunarLander.getShip().mesh);
        }

        std::string scoreText = std::to_string(score);
        if (landing == true) {
            if (time < timer1 + 2) {
                if (!moonScene.isInScene(HUD.getCenterText())) {
                    std::string scoreText = std::to_string(static_cast<int>(score));
                    HUD.setCenterText("Ya got "+scoreText+" points", 1);
                    moonScene.addToScene(HUD.getCenterText());
                }
                return;
            } else {
                newRound();
            }
        }
        timer1 = time;
        if (moonScene.isInScene(HUD.getCenterText())) {
            moonScene.removeFromScene((HUD.getCenterText()));
        }


        if (lunarLander.getFuel() <= 0) {
           if (time < timer2 + 3) {
               if (!moonScene.isInScene(HUD.getCenterText())) {
                   HUD.setCenterText("Game OVer", 6);
                   moonScene.addToScene(HUD.getCenterText());
                   return;
               }
           } else {
               newGame();
           }
        } else if (lunarLander.getFuel() < 200) {
            if (time < timer2 + 0.5) {
                if (!moonScene.isInScene(HUD.getCenterText())) {
                    HUD.setCenterText("Low on fuel!", 4);
                    moonScene.addToScene(HUD.getCenterText());
                }
            } else if (time < timer2 + 1) {
                if (moonScene.isInScene(HUD.getCenterText())) {
                    moonScene.removeFromScene(HUD.getCenterText());
                }
            } else {
                timer2 = time;
            }
        } else {
            timer2 = time;
        }
        std::vector<float> movement;
        isClose = false;
        crash = false;
        landing = false;
        HUD.setTime(time);

        if (keyInputs.searchCommands("RESET")) {
            newGame();
        }

        for (const auto line: lunarSurface.getLines()) {
            if (rocketPhysics.AABBcollision(lunarLander.getShip(), line)) {
                isClose = true;
                if (rocketPhysics.GJKcollision(lunarLander.getShip(), line)) {
                    collision = true;
                    if (rocketPhysics.isSoftLanding(lunarLander.getShip().angle, line.angle)) {
                        score += 50*line.multiplier;
                        HUD.setElement("Score", score);
                        landing = true;
                    } else {
                        crash = true;
                    }
                    return;
                }
            }
        }
        if (!collision) {
            if (isClose) {
                moonScene.zoomIn();
            } else {
                moonScene.zoomOut();
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

            moonScene.setCameraPosition(lunarLander.getPosition());
            HUD.setPosition(moonScene.getCameraPosition());
            HUD.setScale(moonScene.getCameraScale());

            if (static_cast<int>(time*100)%20 < 1) {
                HUD.setElement("Altitude", lunarLander.getPosition()[1]-lunarSurface.closestHeightBelow(lunarLander.getPosition()[0])-2);
            }
        }

        //If the spaceship is closer than one 'landscape' instance away from the border to the right
        if (lunarLander.getPosition()[0] > surfaceBorder[1]-(surfaceLength+20)) {
            //Add a new 'landscape' instance at the right border
            lunarSurface.newStartingPoint(surfaceBorder[1], 20);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                moonScene.addToScene(lunarSurface.getLines().back().mesh);
            }
            //Add multipliers to new landscape
            multiplierRange = {static_cast<int>(lunarSurface.getLines().size())-static_cast<int>(surfaceLines.size())-1,
                               static_cast<int>(lunarSurface.getLines().size())-1};
            lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
            lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
            lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);
            //update right boundary
            surfaceBorder[1] += surfaceLength;
            //If the spaceship is closer than one 'landscape' instance away from the border to the left
        } else if (lunarLander.getPosition()[0] < surfaceBorder[0]+(surfaceLength+20)) {
            //Add a new 'landscape' instance at the left border
            lunarSurface.newStartingPoint(surfaceBorder[0]-surfaceLength, 20);
            for (const auto line: surfaceLines) {
                lunarSurface.addLine(line[0], line[1]);
                moonScene.addToScene(lunarSurface.getLines().back().mesh);
            }
            //Add multipliers to new landscape
            multiplierRange = {static_cast<int>(lunarSurface.getLines().size())-static_cast<int>(surfaceLines.size())-1,
                               static_cast<int>(lunarSurface.getLines().size())-1};
            lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
            lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
            lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);
            //update left border
            surfaceBorder[0] -= surfaceLength;
        }
    }

    GameScene &getScene() {
        return moonScene;
    }

    threepp::OrthographicCamera &getCamera() {
        return moonScene.camera();
    }

    UI &getUI() {
        return keyInputs;
    }

    void newRound() {
        lunarSurface.reset();
        rocketPhysics.reset();
        moonScene.reset();
        lunarLander.crash();
        collision = false;
        surfaceBorder = {0, 0};

        for (const auto line: surfaceLines) {
            lunarSurface.addLine(line[0], line[1]);
        }
        surfaceLength = lunarSurface.getLength();
        surfaceBorder[1] += surfaceLength;

        multiplierRange = {0, static_cast<int>(lunarSurface.getLines().size()) - 1};
        lunarSurface.setMultiplier(2, numberOfx2multipliers, x2Level, multiplierRange);
        lunarSurface.setMultiplier(4, numberOfx4multipliers, x4Level, multiplierRange);
        lunarSurface.setMultiplier(5, numberOfx5multipliers, x5Level, multiplierRange);

        for (const auto line: lunarSurface.getLines()) {
            moonScene.addToScene(line.mesh);
        }
        moonScene.addToScene(lunarLander.getShip().mesh);
        moonScene.addToScene(HUD.getHUD());
        HUD.setElement("Fuel", lunarLander.getFuel());
        HUD.setElement("Score", score);
    }

    void newGame() {
        time = 0;
        score = 0;
        lunarLander.getShip().fuel = 1000;
        newRound();
    }
    void crashAnimation() {
        moonScene.removeFromScene(lunarLander.getShip().mesh);
        //moonScene.addToScene(lunarLander.getExplosion());
        //moonScene.addToScene(lunarLander.getShip().mesh);
    }
};

#endif //MOONLANDER_LUNARLANDERGAME_HPP
