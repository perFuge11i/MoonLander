#ifndef MOONLANDER_LANDSCAPE_HPP
#define MOONLANDER_LANDSCAPE_HPP

#include "threepp/threepp.hpp"

class Landscape: public threepp::Scene {
private:
public:
    void addBox(int xSize, int ySize, int xPos, int yPos) {
        std::shared_ptr<threepp::BoxGeometry> boxGeometry;
        std::shared_ptr<threepp::MeshBasicMaterial> material;
        std::vector<std::shared_ptr<threepp::Mesh>> box;

        boxGeometry = threepp::BoxGeometry::create(xSize, ySize, 0);
        boxGeometry->translate(xPos, yPos, 0);
        material = threepp::MeshBasicMaterial::create();
        box.emplace_back(threepp::Mesh::create(boxGeometry, material));
        add(box.back());
    }
};


#endif //MOONLANDER_LANDSCAPE_HPP
