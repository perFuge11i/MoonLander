#ifndef MOONLANDER_SPACESHIP_HPP
#define MOONLANDER_SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "AABB.hpp"

class Spaceship {
private:
    struct BoxObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::string name;
    };
public:
    Spaceship() {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        BoxObject ship;

        int size = 50;
        int x = 30;
        int y = 30;

        boxGeometry = threepp::BoxGeometry::create(size, size, 0);
        boxGeometry->translate(x, y, 0);
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        ship.mesh = threepp::Mesh::create(boxGeometry, material);
        ship.collisionBox.setPosition(x - 50/ 2.0, y + 50/ 2.0);
        ship.collisionBox.setSize(50, 50);
    }
};

#endif //MOONLANDER_SPACESHIP_HPP