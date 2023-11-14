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

class LunarLanderGame {
private:
    MoonScene scene;
    Spaceship lunarLander;
    Landscape lunarSurface;
    UI keyInputs;
    PhysicsEngine rocektPhysics;
public:

    LunarLanderGame() : lunarSurface(0, 160) {
        //test surface
        lunarSurface.addLine(30, "x");
        lunarSurface.addLine(50, "y");
        lunarSurface.addLine(10, "x");
        lunarSurface.addLine(-30, "y");
        lunarSurface.addLine(10, "x");
        lunarSurface.addLine(-20, "y");
        lunarSurface.addLine(150, "x");

        for (const auto line: lunarSurface.getLines()) {
            scene.addObject(line.mesh);
        }
        scene.addObject(lunarLander.getShip().mesh);
    }

    //test  funksjon for kollisjon og animasjon
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
