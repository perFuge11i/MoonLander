#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

#include "Landscape.hpp"

using namespace threepp;


class MoonScene: public Scene {
public:
    MoonScene() {
        int size = 100;

        camera_ = OrthographicCamera::create(-size, size, -size, size);
        camera_->position.set(static_cast<float>(size), static_cast<float>(size), static_cast<float>(size));
        add(camera_);

        Landscape enBox;
        enBox.addBox(100, 100, 100, 175);
    }

    [[nodiscard]] OrthographicCamera& camera() const {
        return *camera_;
    }

private:
    std::shared_ptr<OrthographicCamera> camera_;
};


#endif //MOONLANDER_MOONSCENE_HPP
