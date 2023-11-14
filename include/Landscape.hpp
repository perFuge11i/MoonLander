#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

//Forslag om å bruke struct fra chatGPT, "xOrY", "sign" og "getEnd()" funksjon lagt til selv


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
        float angle;
        int length;

        std::vector<float> getEnd() {
            std::vector<float> endDimensions;

            endDimensions = {this->mesh->position.x + cos(this->angle)*this->length/2,
                             this->mesh->position.y - sin(this->angle)*this->length/2};

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

        line.collisionBox.setPosition(x, y);
        line.collisionBox.setSize(0, 0);

        lines.push_back(line);
    }

    void addLine(int length, float angle) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        std::vector<float> lastLineEnd = lines.back().getEnd();

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        line.mesh->scale.set(length, 0.5, 0);
        line.mesh->position.x = lastLineEnd[0] + cos(angle)*length / 2;
        line.mesh->position.y = lastLineEnd[1] - sin(angle)*length / 2;
        line.mesh->rotation.z = -angle;
        line.length = length;
        line.angle = angle;

        line.collisionBox.setSize(cos(angle)*length, sin(angle)*length);
        line.collisionBox.setPosition(lastLineEnd[0] + cos(angle)*length / 2, lastLineEnd[1] - sin(angle)*length / 2);

        lines.push_back(line);
    }

    std::vector<lineObject> getLines() {
        return lines;
    }
};

#endif //MOONLANDER_LANDSCAPE_HPP
