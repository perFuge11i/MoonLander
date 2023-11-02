#ifndef MOONLANDER_SPACESHIP_HPP
#define MOONLANDER_SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "AABB.hpp"

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
    }
};

#endif //MOONLANDER_SPACESHIP_HPP