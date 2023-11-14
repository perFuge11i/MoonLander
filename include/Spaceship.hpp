#ifndef MOONLANDER_SPACESHIP_HPP
#define MOONLANDER_SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "AABB.hpp"
#include <vector>

//samme som i "Landscape.hpp", struct fra chatGPT

class Spaceship {
private:
    struct shipObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        float rotation = 0;
    };

    shipObject ship;
    const std::vector<int> initPosition = {30, 30};
public:
    Spaceship() {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        int size = 2;
        int x = 30;
        int y = 30;

        boxGeometry = threepp::BoxGeometry::create(size, size, 0);
        material = threepp::MeshBasicMaterial::create();
        ship.mesh = threepp::Mesh::create(boxGeometry, material);

        ship.mesh->position.x = initPosition[0];
        ship.mesh->position.y = initPosition[1];
        ship.collisionBox.setPosition(x, y);
        ship.collisionBox.setSize(size, size);
    }

    shipObject getShip() {
        return ship;
    }

    void move(std::vector<float> movement) {
        ship.mesh->position.x += movement[0];
        ship.mesh->position.y += movement[1];
        ship.collisionBox.setPosition(ship.mesh->position.x, ship.mesh->position.y);
    }
    void rotate(int direction, float time) {
        ship.mesh->rotation.z += direction*time;
        ship.rotation += direction*time;
    }
    auto getRotation() {
        return ship.rotation;
    }

    void reset() {
        ship.mesh->position.x = initPosition[0];
        ship.mesh->position.y = initPosition[1];
        ship.mesh->rotation.z = 0;
        ship.rotation = 0;
        ship.collisionBox.setPosition(initPosition[0], initPosition[1]);
    }
};

#endif //MOONLANDER_SPACESHIP_HPP
