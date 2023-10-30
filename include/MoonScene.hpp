#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

#include "Landscape.hpp"
#include <iostream>

//using namespace threepp;


class MoonScene : public threepp::Scene {
private:
    std::shared_ptr<threepp::OrthographicCamera> camera_;
    std::vector<std::shared_ptr<threepp::Mesh>> box_;
    Landscape lunarSurface(10, 180);
public:
    MoonScene() {
        int size = 100;

        camera_ = threepp::OrthographicCamera::create(-size, size, -size, size);
        camera_->position.set(static_cast<float>(size), static_cast<float>(size), static_cast<float>(size));
        add(camera_);

        /*lunarSurface.addBox("box1", 100, 1, 100, 175);
        lunarSurface.addBox("box2", 10, 10, 200, 200);
        lunarSurface.addBox("otherBox", 10, 200, 100, 100);

        AABB otherBox(10, 100, 100, 100);
        if (lunarSurface.checkCollision(otherBox)) {
            std::cout << "Collision";
        } else {
            std::cout << "No Collision";
        }

        for (const auto &box: lunarSurface.getBoxes()) {
            if (lunarSurface.getBoxMesh(box.name) != nullptr) {
                add(lunarSurface.getBoxMesh(box.name));
            }
        }*/
    }

    threepp::OrthographicCamera &camera() const {
        return *camera_;
    }
};


#endif //MOONLANDER_MOONSCENE_HPP
