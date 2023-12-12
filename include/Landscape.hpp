#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

//Line 17: Idea of using struct from chatGPT, getEnd() and getVertices() made by ourselves
//Line 171-174: Random number generation from chatGPT

#include "threepp/threepp.hpp"
#include "AABB.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

class Surface {
private:
    struct lineObject {
        std::shared_ptr<threepp::Mesh> mesh;
        AABB collisionBox;
        std::vector<float> position = {0,0,0};
        std::vector<float> scale = {0,0,0};
        float angle = 0;
        int multiplier = 0;

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
        void setMultiplier(int multiplier_) {
            auto newMaterial = threepp::MeshBasicMaterial::create();

            if (multiplier_ == 2) {
                newMaterial->color.setHex(0x00FFFF);
            } else if (multiplier_ == 4) {
                newMaterial->color.setHex(0x00FF00);
            } else if (multiplier_ == 5) {
                newMaterial->color.setHex(0xFFFF00);
            }
            this->mesh->setMaterial(newMaterial);
            this->scale[1] = 0.4;
            this->mesh->scale[1] = 0.4;
            this->multiplier = multiplier_;
        }
    };

    std::vector<lineObject> lines;
public:
    Surface(const int x, const int y) {
        newStartingPoint(x,y);
    }
    void addLine(float length, float angle) {
        std::shared_ptr<threepp::BoxGeometry> geometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;

        geometry = threepp::BoxGeometry::create();
        material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xb3b7bf);

        lineObject line;
        line.mesh = threepp::Mesh::create(geometry, material);

        std::vector<float> lastLineEnd = lines.back().getEnd();

        line.scale = {length,0.15,0};
        line.angle = angle;
        line.position = {lastLineEnd[0] + cos(line.angle)*line.scale[0] / 2,
                         lastLineEnd[1] + sin(line.angle)*line.scale[0] / 2};
        line.multiplier = 1;

        line.mesh->scale.set(line.scale[0], line.scale[1], line.scale[2]);
        line.mesh->position.x = line.position[0];
        line.mesh->position.y = line.position[1];
        line.mesh->rotation.z = line.angle;

        line.collisionBox.setSize(cos(line.angle)*line.scale[0], sin(line.angle)*line.scale[0]);
        line.collisionBox.setPosition(line.position[0],
                                      line.position[1]);
        lines.push_back(line);
    }

    std::vector<lineObject>& getLines() {
        return lines;
    }
    float closestHeightBelow(float x) {
        float y = 0;
        float closestX = lines.back().position[0];
        for (const auto line: lines) {
            if (abs(closestX-x) > abs(line.position[0]-x)) {
                y = line.position[1];
                break;
            }
            closestX = line.position[0];
        }
        return y;
    }
    std::vector<int> findPlateauIndexes(int startIndex, int endIndex) {
        std::vector<std::pair<int, float>> indexedHeights;
        for (int i = startIndex; i < endIndex; i++) {
            // Check if the line is flat and big enough
            if (lines[i].angle == 0 && lines[i].scale[0] >= 1) {
                //Add line and lineHeight to list
                indexedHeights.emplace_back(i, lines[i].position[1]);
            }
        }

        //rank order by height
        std::sort(indexedHeights.begin(), indexedHeights.end(),
                  [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
                      return a.second < b.second;
                  });

        std::vector<int> indexes;
        for (const auto& height : indexedHeights) {
            indexes.push_back(height.first);
        }

        return indexes;
    }
    float getLength() {
        return lines.back().getEnd()[0] - lines[0].getEnd()[0];
    }

    void newStartingPoint(const float x, const float y) {
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
    void setMultiplier(int multiplier, int numberOfMultipliers, std::vector<float> levelAsFractionOfPlateaus, std::vector<int> range) {
        int n = numberOfMultipliers;
        std::vector<int> plateaus = findPlateauIndexes(range[0], range[1]);
        int minIndex = static_cast<int>(levelAsFractionOfPlateaus[0]*(plateaus.size()-1));
        int maxIndex = static_cast<int>(levelAsFractionOfPlateaus[1]*(plateaus.size()-1));

        int randomIndex;
        int multiplierIndex;
        while (n > 0) {
            //Generating random number
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(minIndex, maxIndex);

            randomIndex = distribution(gen);
            multiplierIndex = plateaus[randomIndex];

            if (lines[multiplierIndex].multiplier == 1) {
                lines[multiplierIndex].setMultiplier(multiplier);
                n -= 1;
            }
        }
    }
    void reset() {
        int x = lines[0].position[0];
        int y = lines[0].position[1];
        lines.clear();

        newStartingPoint(x,y);

    }

};

#endif //MOONLANDER_LANDSCAPE_HPP
