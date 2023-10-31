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
        std::string xOrY;
        int sign;

        std::vector<float> getEnd() {
            std::vector<float> endDimensions;

            if (this->xOrY == "x") {
                endDimensions = {this->mesh->position.x + this->sign*this->mesh->scale.x/2,
                                 this->mesh->position.y};
            } else if (this->xOrY == "y") {
                endDimensions = {this->mesh->position.x,
                                 this->mesh->position.y + this->sign*this->mesh->scale.y/2};
            }

            std::cout << "lastEnd" << std::endl;
            std::cout << this->mesh->position.x  << " - " << this->mesh->position.y << std::endl;
            std::cout << this->mesh->scale.x  << " - " << this->mesh->scale.y << std::endl;
            std::cout << this->sign << std::endl;

            return endDimensions;
        }
    };

    std::vector<BoxObject> boxes;
public:
    Landscape(const int x, const int y) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        boxGeometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        BoxObject box;
        box.mesh = threepp::Mesh::create(boxGeometry, material);

        box.mesh->scale.set(0, 0, 0);
        box.mesh->position.x = x;
        box.mesh->position.y = y;

        box.collisionBox.setPosition(x - 1/2.0, y + 1/2.0);
        box.collisionBox.setSize(0, 0);
        box.name = std::to_string(boxes.size());
        box.xOrY = "x";
        box.sign = 1;
        std::cout << box.mesh->position.x << " - " << box.mesh->position.y << std::endl;
        std::cout << box.mesh->scale.x << " - " << box.mesh->scale.y << std::endl;

        boxes.push_back(box);
    }
    void addBox(int length, std::string xOrY) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        boxGeometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        std::vector<float> lastBoxPos = boxes.back().getEnd();
        BoxObject box;
        box.mesh = threepp::Mesh::create(boxGeometry, material);

        if (xOrY == "x") {
            box.mesh->scale.set(abs(length), 1, 0);
            box.mesh->position.x = lastBoxPos[0] + length/2.0;
            box.mesh->position.y = lastBoxPos[1];
            box.collisionBox.setSize(abs(length), 1);
            box.sign = length/abs(length);
        } else if (xOrY == "y"){
            box.mesh->scale.set(1, abs(length), 0);
            box.mesh->position.x = lastBoxPos[0];
            box.mesh->position.y = lastBoxPos[1] - length/2.0;
            box.collisionBox.setSize(1, abs(length));
            box.sign = -length/abs(length);
        }

        box.xOrY = xOrY;
        box.collisionBox.setPosition(lastBoxPos[0], lastBoxPos[1]);
        box.name = std::to_string(boxes.size());
        std::cout << "current" << std::endl;
        std::cout << box.mesh->position.x << " - " << box.mesh->position.y << std::endl;
        std::cout << box.mesh->scale.x << " - " << box.mesh->scale.y << std::endl;
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
