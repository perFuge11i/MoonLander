#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

//Forslag om å bruke struct fra chatGPT, getEnd() og getVertices() laget selv

#include "threepp/threepp.hpp"
#include "AABB.hpp"
#include <cmath>
#include <iostream>

class Landscape {
private:
    struct lineObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::vector<float> position;
        std::vector<float> scale;
        float angle;

        std::vector<float> getEnd() {
            return {this->mesh->position.x + cos(this->angle)*this->scale[0]/2,
                    this->mesh->position.y + sin(this->angle)*this->scale[0]/2};
        }
        std::vector<std::vector<float>> getVertices() const {
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

    std::vector<lineObject> lines;
public:
    Landscape(const int x, const int y) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        line.scale = {0,0,0};
        line.position = {static_cast<float>(x),static_cast<float>(y)};

        line.mesh->scale.set(0, 0, 0);
        line.mesh->position.x = line.position[0];
        line.mesh->position.y = line.position[1];

        line.collisionBox.setPosition(line.position[0], line.position[1]);
        line.collisionBox.setSize(0, 0);

        lines.push_back(line);
    }

    void addLine(float length, float angle) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xFF0000);

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        std::vector<float> lastLineEnd = lines.back().getEnd();

        line.scale = {length,0.3,0};
        line.angle = angle;
        line.position = {lastLineEnd[0] + cos(line.angle)*line.scale[0] / 2,
                         lastLineEnd[1] + sin(line.angle)*line.scale[0] / 2};

        line.mesh->scale.set(line.scale[0], line.scale[1], line.scale[2]);
        line.mesh->position.x = line.position[0];
        line.mesh->position.y = line.position[1];
        line.mesh->rotation.z = line.angle;

        line.collisionBox.setSize(cos(line.angle)*line.scale[0], sin(line.angle)*line.scale[0]);
        line.collisionBox.setPosition(line.position[0],
                                      line.position[1]);
        lines.push_back(line);
    }

    std::vector<lineObject> getLines() {
        return lines;
    }

    float getLength() {
        return lines.back().getEnd()[0] - lines[0].getEnd()[0];
    }

    std::vector<float> newStartingPoint(const float x, const float y) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        line.scale = {0,0,0};
        line.position = {static_cast<float>(x),static_cast<float>(y)};

        line.mesh->scale.set(0, 0, 0);
        line.mesh->position.x = line.position[0];
        line.mesh->position.y = line.position[1];

        line.collisionBox.setPosition(line.position[0], line.position[1]);
        line.collisionBox.setSize(0, 0);

        std::vector<float> lastLineEnd = lines.back().getEnd();

        lines.push_back(line);

        return lastLineEnd;
    }
};

#endif //MOONLANDER_LANDSCAPE_HPP
