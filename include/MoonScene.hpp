#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

#include "Landscape.hpp"
#include <iostream>

//using namespace threepp;


class MoonScene : public threepp::Scene {
private:
    std::shared_ptr<threepp::OrthographicCamera> camera_;
    std::vector<std::shared_ptr<threepp::Mesh>> box_;
public:
    MoonScene() {
        int size = 100;

        camera_ = threepp::OrthographicCamera::create(-size, size, -size, size);
        camera_->position.set(static_cast<float>(size), static_cast<float>(size), static_cast<float>(size));
        add(camera_);

        Landscape lunarSurface(10, 180);
        lunarSurface.addBox(1, 10);
        lunarSurface.addBox(10, 1);

        for (const auto &box: lunarSurface.getBoxes()) {
            if (lunarSurface.getBoxMesh(box.name) != nullptr) {
                add(lunarSurface.getBoxMesh(box.name));
            }
        }
        add(lunarSurface.getBoxMesh("1"));
    }

    threepp::OrthographicCamera &camera() const {
        return *camera_;
    }
};


#endif //MOONLANDER_MOONSCENE_HPP
