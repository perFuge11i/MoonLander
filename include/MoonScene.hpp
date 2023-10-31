#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

#include "Landscape.hpp"
#include <iostream>

//using namespace threepp;


class MoonScene : public threepp::Scene {
private:
    std::shared_ptr<threepp::OrthographicCamera> camera_;
    std::vector<std::shared_ptr<threepp::Mesh>> box_;
    std::shared_ptr<threepp::Mesh> rocket_;
public:
    MoonScene() {
        int size = 100;

        camera_ = threepp::OrthographicCamera::create(-size, size, -size, size);
        camera_->position.set(static_cast<float>(size), static_cast<float>(size), static_cast<float>(size));
        add(camera_);

        Landscape lunarSurface(0, 160);
        lunarSurface.addBox(30, "x");
        lunarSurface.addBox(50, "y");
        lunarSurface.addBox(10, "x");
        lunarSurface.addBox(-30, "y");
        lunarSurface.addBox(10, "x");
        lunarSurface.addBox(-20, "y");
        lunarSurface.addBox(150, "x");

        for (const auto &box: lunarSurface.getBoxes()) {
            if (lunarSurface.getBoxMesh(box.name) != nullptr) {
                add(lunarSurface.getBoxMesh(box.name));
            }
        }
        add(lunarSurface.getBoxMesh("1"));
        // Initialize the rocket
        auto rocketGeometry = threepp::BoxGeometry::create(10, 10, 10); // Adjust size
        auto rocketMaterial = threepp::MeshBasicMaterial::create();
        rocket_ = threepp::Mesh::create(rocketGeometry, rocketMaterial);
        add(rocket_); // Add rocket to the scene
    }
    // Method to set the position of the rocket
    void setRocketPosition(float x, float y, float z) {
        rocket_->position.set(x, y, z);
    }

    threepp::OrthographicCamera &camera() const {
        return *camera_;
    }
};


#endif //MOONLANDER_MOONSCENE_HPP
