#ifndef MOONLANDER_LUNARLANDERGAME_HPP
#define MOONLANDER_LUNARLANDERGAME_HPP

#include "MoonScene.hpp"
#include "Spaceship.hpp"
#include "Landscape.hpp"

class LunarLanderGame {
private:
    MoonScene scene;
    Spaceship lunarLander;
    const double g = -9.81;
public:
    LunarLanderGame() {
        Landscape lunarSurface(0, 160);
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

    void update(const double dt) {
        std::vector<double> movement {0,1,0};//= rocketPhsyics.getVector(dt);
        lunarLander.move(movement);
    }

    MoonScene& getScene() {
        return scene;
    }

    threepp::OrthographicCamera& getCamera() {
        return scene.camera();
    }


};

#endif //MOONLANDER_LUNARLANDERGAME_HPP
