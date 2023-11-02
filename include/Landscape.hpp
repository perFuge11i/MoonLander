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
    struct lineObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::string xOrY;
        int sign;

        std::vector<float> getEnd() {
            std::vector<float> endDimensions;

            if (this->xOrY == "x") {
                endDimensions = {this->mesh->position.x + this->sign * this->mesh->scale.x / 2,
                                 this->mesh->position.y};
            } else if (this->xOrY == "y") {
                endDimensions = {this->mesh->position.x,
                                 this->mesh->position.y + this->sign * this->mesh->scale.y / 2};
            }

            return endDimensions;
        }
    };

    std::vector<lineObject> lines;
public:
    Landscape(const int x, const int y) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        line.mesh->scale.set(0, 0, 0);
        line.mesh->position.x = x;
        line.mesh->position.y = y;

        line.collisionBox.setPosition(x - 1 / 2.0, y + 1 / 2.0);
        line.collisionBox.setSize(0, 0);
        line.xOrY = "x";
        line.sign = 1;

        lines.push_back(line);
    }

    void addLine(int length, std::string xOrY_) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        std::vector<float> lastLinePos = lines.back().getEnd();

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        if (xOrY_ == "x") {
            line.mesh->scale.set(abs(length), 1, 0);
            line.mesh->position.x = lastLinePos[0] + length / 2;
            line.mesh->position.y = lastLinePos[1];
            line.collisionBox.setSize(abs(length), 1);
            line.collisionBox.setPosition(lastLinePos[0], lastLinePos[1]);
            line.sign = length / abs(length);
        } else if (xOrY_ == "y") {
            line.mesh->scale.set(1, abs(length), 0);
            line.mesh->position.x = lastLinePos[0];
            line.mesh->position.y = lastLinePos[1] - length / 2;
            line.collisionBox.setSize(1, abs(length));
            line.sign = -length / abs(length);
        }

        line.xOrY = xOrY_;
        line.collisionBox.setPosition(lastLinePos[0] - 1/2, lastLinePos[1] + 1/2);

        lines.push_back(line);
    }

    std::vector<lineObject> getLines() {
        return lines;
    }
};


#endif //MOONLANDER_LANDSCAPE_HPP
