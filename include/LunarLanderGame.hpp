#ifndef MOONLANDER_LUNARLANDERGAME_HPP
#define MOONLANDER_LUNARLANDERGAME_HPP

//linje 14: innspill fra chatGPT

#include "MoonScene.hpp"
#include "Spaceship.hpp"
#include "Landscape.hpp"
#include "UI.hpp"
#include "PhysicsEngine.hpp"
#include <iostream>
#include <string>
#include <cmath>

class LunarLanderGame {
private:
    MoonScene scene;
    Spaceship lunarLander;
    Landscape lunarSurface;
    UI keyInputs;
    PhysicsEngine rocektPhysics;
public:

    LunarLanderGame() : lunarSurface(0, 160), rocektPhysics(10, 0) {
        lunarSurface.addLine(5, 0);
        lunarSurface.addLine(3, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(5, M_PI_2 - M_PI_4/8);
        lunarSurface.addLine(3, M_PI_2);
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(5, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(4, M_PI_4);
        lunarSurface.addLine(2, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(2, M_PI_2 - M_PI_4/8);
        lunarSurface.addLine(3, M_PI/3);
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(7, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(2, M_PI/6);
        lunarSurface.addLine(3, -M_PI_4);
        lunarSurface.addLine(3, 0);
        lunarSurface.addLine(2, M_PI_4);
        lunarSurface.addLine(3, M_PI_2 - M_PI_4/8);
        lunarSurface.addLine(5, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(2, M_PI/6);
        lunarSurface.addLine(2, M_PI_2 - M_PI_4/8);
        lunarSurface.addLine(2, M_PI_4 + M_PI_4/4);
        lunarSurface.addLine(2, M_PI_4);
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/4));
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/4));
        lunarSurface.addLine(1, 0);
        lunarSurface.addLine(5, -(M_PI_2 - M_PI_4/8));
        lunarSurface.addLine(5, -(M_PI_2 - M_PI_4/4));
        lunarSurface.addLine(2, -M_PI_2);
        lunarSurface.addLine(3, -(M_PI_2 - M_PI_4/6));
        lunarSurface.addLine(3, -(M_PI_2 - M_PI_4));
        lunarSurface.addLine(3, -(M_PI_2 - M_PI_4/8));
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/3));
        lunarSurface.addLine(2, -(M_PI_4 - M_PI_4/4));
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(2, M_PI_4);
        lunarSurface.addLine(3, M_PI_2 - M_PI_4/2);
        lunarSurface.addLine(2, M_PI_4 + M_PI/12);
        lunarSurface.addLine(2, M_PI_4 + M_PI_4/8);
        lunarSurface.addLine(1, M_PI_2 - M_PI_4/2);
        lunarSurface.addLine(2, M_PI_4 + M_PI_4/8);
        lunarSurface.addLine(1, M_PI_2 - M_PI_4/2);
        lunarSurface.addLine(2, M_PI/6);
        lunarSurface.addLine(3, M_PI_2 - M_PI_4/2);
        lunarSurface.addLine(2, M_PI/6);
        lunarSurface.addLine(2, M_PI_2 - M_PI_4);
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(2, -M_PI/12);
        lunarSurface.addLine(2, -(M_PI_4 + M_PI_4/8));
        lunarSurface.addLine(1, -(M_PI_2 - M_PI_4/8));
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/2));
        lunarSurface.addLine(1, -(M_PI_2 - M_PI_4/8));
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/2));
        lunarSurface.addLine(1, -(M_PI_2 - M_PI_4/8));
        lunarSurface.addLine(2, -(M_PI_2 - M_PI_4/2));
        lunarSurface.addLine(2, 0);
        lunarSurface.addLine(3, M_PI_2 - M_PI_4/4);
        lunarSurface.addLine(1, M_PI_4);
        lunarSurface.addLine(1, -M_PI/6);
        lunarSurface.addLine(2, -(M_PI_4 + M_PI_4/4));
        lunarSurface.addLine(3, -(M_PI_2 - M_PI_4/6));
        lunarSurface.addLine(3, -M_PI/6);
        lunarSurface.addLine(5, -(M_PI_2 - M_PI_4/6));
        lunarSurface.addLine(5, -(M_PI_2 - M_PI_4/4));
        lunarSurface.addLine(1, -M_PI_2);
        lunarSurface.addLine(2, -(M_PI_4 - M_PI_4/4));
        lunarSurface.addLine(3, 0);
        lunarSurface.addLine(5, M_PI_4);
        lunarSurface.addLine(2, M_PI_4 + M_PI_4/3);
        lunarSurface.addLine(2, M_PI_4);
        lunarSurface.addLine(2, M_PI_4 + M_PI_4/3);
        lunarSurface.addLine(2, M_PI_4 - M_PI_4/4);
        lunarSurface.addLine(5, M_PI_2 - M_PI_4/6);
        lunarSurface.addLine(2, M_PI_4 - M_PI_4/4);




        for (const auto line: lunarSurface.getLines()) {
            scene.addObject(line.mesh);
        }
        scene.addObject(lunarLander.getShip().mesh);
    }

    void update(const float dt) {
        std::vector<float> movement = {2,0};

        if (keyInputs.searchCommands("LEFT")) {
            lunarLander.rotate(-1, dt);
        }
        if (keyInputs.searchCommands("RIGHT")) {
            lunarLander.rotate(1, dt);
        }
        if (keyInputs.searchCommands("FORWARD")) {
            rocektPhysics.calculateForce(lunarLander.getRotation());
        }
        if (keyInputs.searchCommands("RESET")) {
            lunarLander.reset();
            rocektPhysics.reset();
        }

        movement = rocektPhysics.calculateNextMovement(dt);


        bool collision = false;
        for (const auto line: lunarSurface.getLines()) {
            if (lunarLander.getShip().collisionBox.intersects(line.collisionBox)) {
                collision = true;
            }
        }

        if (!collision) {
            lunarLander.move(movement);
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
