#ifndef MOONLANDER_SPACESHIP_HPP
#define MOONLANDER_SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "AABB.hpp"
// Define the movement directions

enum class RocketDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE  // No movement
};

class Spaceship {
private:
    struct boxObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
    };

    boxObject ship;
public:
    Spaceship() {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        int size = 50;
        int x = 30;
        int y = 30;

        boxGeometry = threepp::BoxGeometry::create(size, size, 0);
        boxGeometry->translate(x, y, 0);
        material = threepp::MeshBasicMaterial::create();


        ship.mesh = threepp::Mesh::create(boxGeometry, material);

        ship.collisionBox.setPosition(x - size/ 2, y + size/ 2);
        ship.collisionBox.setSize(size, size);
    }

    boxObject getShip() {
        return ship;
    }

    void move(std::vector<double> movement) {
        // Update the rocket's position based on the direction
        /*switch (rocketDirection_) {
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
        }*/
    }
};

#endif //MOONLANDER_SPACESHIP_HPP