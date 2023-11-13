#ifndef MOONLANDER_SPACESHIP_HPP
#define MOONLANDER_SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "AABB.hpp"

//samme som i "Landscape.hpp", struct fra chatGPT

class Spaceship {
private:
    struct boxObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        float rotation = 0;
    };

    boxObject ship;
public:
    Spaceship() {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        int size = 20;
        int x = 30;
        int y = 30;

        boxGeometry = threepp::BoxGeometry::create(size, size, 0);
        material = threepp::MeshBasicMaterial::create();
        ship.mesh = threepp::Mesh::create(boxGeometry, material);

        ship.mesh->position.x = x;
        ship.mesh->position.y = y;
        ship.collisionBox.setPosition(x, y);
        ship.collisionBox.setSize(size, size);
    }

    boxObject getShip() {
        return ship;
    }

    void move(std::vector<float> movement) {
        ship.mesh->position.x += movement[0];
        ship.mesh->position.y += movement[1];
        ship.collisionBox.setPosition(ship.mesh->position.x, ship.mesh->position.y);
    }
    void rotate(int direction, float time) {
        ship.mesh->rotation.z += direction*time;
        ship.rotation = direction*time;
    }
    auto getRotation() {
        return ship.rotation;
    }
};

#endif //MOONLANDER_SPACESHIP_HPP
