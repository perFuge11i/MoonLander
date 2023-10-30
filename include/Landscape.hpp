#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

//Struct forsklag fra chatGPT
//check collisions fra chatGPT

#include "threepp/threepp.hpp"
#include "AABB.hpp"
#include <cmath>
#include <iostream>

class Landscape {
private:
    struct BoxObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::string name;
    };

    std::vector<BoxObject> boxes;
public:
    Landscape(const int x, const int y) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        boxGeometry = threepp::BoxGeometry::create(1, 1, 0);
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        BoxObject box;
        box.mesh = threepp::Mesh::create(boxGeometry, material);

        box.mesh->position.x = x;
        box.mesh->position.y = y;

        box.collisionBox.setPosition(x - 1/2.0, y + 1/2.0);
        box.collisionBox.setSize(1, 1);
        box.name = std::to_string(boxes.size());

        boxes.push_back(box);
    }
    void addBox(int length, int height) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        boxGeometry = threepp::BoxGeometry::create(length, height, 0);
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        std::vector<float> lastBoxPos = boxes[boxes.size()-1].collisionBox.getRightCorner();

        BoxObject box;
        box.mesh = threepp::Mesh::create(boxGeometry, material);

        box.mesh->position.x = lastBoxPos[0] + length/2.0;
        box.mesh->position.y = lastBoxPos[1] - height/2.0;
        std::cout << "" << std::endl;

        box.collisionBox.setPosition(lastBoxPos[0], lastBoxPos[1]);
        box.collisionBox.setSize(length, height);
        box.name = std::to_string(boxes.size());

        boxes.push_back(box);
    }


    bool checkCollision(const AABB &otherBox) const {
        for (const auto box: boxes) {
            if (box.collisionBox.intersects(otherBox)) {
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<threepp::Mesh> getBoxMesh(const std::string &name) const {
        for (const auto box: boxes) {
            if (box.name == name) {
                return box.mesh;
            }
        }
        return nullptr;
    }

    std::vector<BoxObject> getBoxes() {
        return boxes;
    }
};


#endif //MOONLANDER_LANDSCAPE_HPP
