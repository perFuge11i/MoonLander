#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

#include "Landscape.hpp"
#include <iostream>
#include "threepp/canvas/Canvas.hpp"

// Define the movement directions
enum class RocketDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE  // No movement
};

class MoonScene : public threepp::Scene {
private:
    std::shared_ptr<threepp::OrthographicCamera> camera_;
    std::vector<std::shared_ptr<threepp::Mesh>> box_;
    std::shared_ptr<threepp::Mesh> rocket_; // Rocket mesh
    RocketDirection rocketDirection_ = RocketDirection::NONE;
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

    void handleKeyPress(int key) {
        const float moveAmount = 1.0f;

        switch (key) {
            case Key::UP:
            case Key::W:
                rocketDirection_ = RocketDirection::UP;
                break;
            case Key::DOWN:
            case Key::S:
                rocketDirection_ = RocketDirection::DOWN;
                break;
            case Key::LEFT:
            case Key::A:
                rocketDirection_ = RocketDirection::LEFT;
                break;
            case Key::RIGHT:
            case Key::D:
                rocketDirection_ = RocketDirection::RIGHT;
                break;
            default:
                rocketDirection_ = RocketDirection::NONE;
                break;
        }

        // Update the rocket's position based on the direction
        switch (rocketDirection_) {
            case RocketDirection::UP:
                rocket_->position.y += moveAmount;
                break;
            case RocketDirection::DOWN:
                rocket_->position.y -= moveAmount;
                break;
            case RocketDirection::LEFT:
                rocket_->position.x -= moveAmount;
                break;
            case RocketDirection::RIGHT:
                rocket_->position.x += moveAmount;
                break;
            case RocketDirection::NONE:
                // No movement
                break;
        }
    }

    threepp::OrthographicCamera &camera() const {
        return *camera_;
    }
};

#endif //MOONLANDER_MOONSCENE_HPP