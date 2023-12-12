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
        std::vector<float> initPosition;
        std::vector<float> position;
        std::vector<float> scale;
        float angle = 0;
        float fuel = 0;

        std::vector<std::vector<float>> getVertices() {
            std::vector<float> xAxisVector = {cos(this->angle), sin(this->angle)};
            std::vector<float> yAxisVector = {-xAxisVector[1], xAxisVector[0]};
            std::vector<float> xVector = {xAxisVector[0]*this->scale[0]/2, xAxisVector[1]*this->scale[0]/2};
            std::vector<float> yVector = {yAxisVector[0]*this->scale[1]/2, yAxisVector[1]*this->scale[1]/2};

            std::vector<float> vertex1 = {this->position[0] + xVector[0] + yVector[0],
                                          this->position[1] + xVector[1] + yVector[1]};
            std::vector<float> vertex2 = {this->position[0] - xVector[0] + yVector[0],
                                          this->position[1] - xVector[1] + yVector[1]};
            std::vector<float> vertex3 = {this->position[0] + xVector[0] - yVector[0],
                                          this->position[1] + xVector[1] - yVector[1]};
            std::vector<float> vertex4 = {this->position[0] - xVector[0] - yVector[0],
                                          this->position[1] - xVector[1] - yVector[1]};

            return {vertex1, vertex2, vertex3, vertex4};
        }
    };

    std::shared_ptr<threepp::Mesh> explosionMesh;

    shipObject ship;
    threepp::TextureLoader textureLoader;
public:
    Spaceship(int x, int y) {
        ship.initPosition = {static_cast<float>(x), static_cast<float>(y)};
        ship.position = ship.initPosition;
        ship.scale = {1.5,1.5,0};
        ship.angle = M_PI_2;
        ship.fuel = 1000;

        auto shipGeometry = threepp::BoxGeometry::create(ship.scale[0], ship.scale[1], 0);
        auto shipMaterial = threepp::MeshBasicMaterial::create({{"map", textureLoader.load("../data/textures/spaceship.png")}});
        ship.mesh = threepp::Mesh::create(shipGeometry, shipMaterial);
        ship.mesh->rotation.z = M_PI_2;
        ship.mesh->position.x = ship.position[0];
        ship.mesh->position.y = ship.position[1];
        ship.collisionBox.setPosition(x, y);
        ship.collisionBox.setSize(ship.scale[0] + 20, ship.scale[1] + 20);

        auto explosionGeometry = threepp::BoxGeometry::create(ship.scale[0]*4, ship.scale[1]*4, 0);
        auto explosionMaterial = threepp::MeshBasicMaterial::create({{"map", textureLoader.load("../data/textures/explosion.png")}});
        explosionMesh = threepp::Mesh::create(explosionGeometry, explosionMaterial);
    }

    shipObject &getShip() {
        return ship;
    }

    void move(std::vector<float> movement) {
        ship.position[0] += movement[0];
        ship.position[1] += movement[1];
        ship.mesh->position.x = ship.position[0];
        ship.mesh->position.y = ship.position[1];
        ship.collisionBox.setPosition(ship.position[0], ship.position[1]);
    }
    void rotate(int direction, float time) {
        float rotation = direction*time;
        if (ship.angle+rotation >= 0 && ship.angle+rotation <= M_PI) {
            ship.angle += rotation;
        }
        ship.mesh->rotation.z = ship.angle;

    }
    float getRotation() {
        return ship.angle;
    }
    std::vector<float> getPosition() {
        return ship.position;
    }

    void useFuel() {
        ship.fuel -= 0.5;
    }
    float getFuel() {
        return ship.fuel;
    }
    void crash() {
        ship.mesh->position.x = ship.initPosition[0];
        ship.mesh->position.y = ship.initPosition[1];
        ship.position = ship.initPosition;
        ship.mesh->rotation.z = M_PI_2;
        ship.angle = M_PI_2;
        ship.collisionBox.setPosition(ship.initPosition[0], ship.initPosition[1]);
    }
    auto getExplosion() {
        explosionMesh->rotation.z = ship.angle;
        explosionMesh->position = {ship.position[0], ship.position[1], ship.position[2]};
        return explosionMesh;
    }
};

#endif //MOONLANDER_SPACESHIP_HPP
