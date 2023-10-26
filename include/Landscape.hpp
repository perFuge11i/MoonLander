#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

//Struct forsklag fra chatGPT
//check collisions fra chatGPT

#include "threepp/threepp.hpp"
#include "AABB.hpp"

class Landscape {
private:
    struct BoxObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::string name;
    };

    std::vector<BoxObject> boxes;
public:
    void addBox(const std::string &name, int xSize, int ySize, int xPos, int yPos) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        boxGeometry = threepp::BoxGeometry::create(xSize, ySize, 0);
        boxGeometry->translate(xPos, yPos, 0);
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        BoxObject box;
        box.mesh = threepp::Mesh::create(boxGeometry, material);
        box.collisionBox.setPosition(xPos - xSize / 2.0, yPos + ySize / 2.0);
        box.collisionBox.setSize(xSize, ySize);
        box.name = name;

        boxes.push_back(box);
    }


    bool checkCollision(const AABB &otherBox) const {
        for (const auto &box: boxes) {
            if (box.collisionBox.intersects(otherBox)) {
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<threepp::Mesh> getBoxMesh(const std::string &name) const {
        for (const auto &box: boxes) {
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
