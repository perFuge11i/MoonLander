#ifndef MOONLANDER_MOONSCENE_HPP
#define MOONLANDER_MOONSCENE_HPP

//Camera configuration and 'camera()' function from the "snake" example in "threepp"
//reset() function, and all applications of the 'objects' vector, from chatGPT

#include "threepp/threepp.hpp"

class GameScene : public threepp::Scene {
private:
    std::vector<std::shared_ptr<threepp::Object3D>> objects;
    std::shared_ptr<threepp::OrthographicCamera> camera_;
    int canvasSize;
    bool zooming = false;
public:
    GameScene(int size) {
        this->canvasSize = size;
        camera_ = threepp::OrthographicCamera::create(-canvasSize/2, canvasSize/2, canvasSize/2, -canvasSize/2);
        camera_->position.set(static_cast<float>(canvasSize/2), static_cast<float>(canvasSize/2), static_cast<float>(canvasSize/2));
        add(camera_);
    }

    void addToScene(auto object) {
        if (!isInScene(object)) {
            add(object);
            objects.push_back(object);
        }
    }
    void removeFromScene(auto object) {
        if (isInScene(object)) {
            remove(*object);
            //remove object from 'objects'
            auto it = std::find(objects.begin(), objects.end(), object);

            if (it != objects.end()) {
                objects.erase(it);
            }
        }
    }

    void zoomIn() {
        zooming = true;
        camera_->scale = {0.3, 0.3, 1};
    }
    void zoomOut() {
        zooming = false;
        camera_->scale = {0.8, 0.8, 1};
    }
    void setCameraPosition(std::vector<float> position) {
        if (zooming) {
            camera_->position.set(static_cast<float>(position[0]), static_cast<float>(position[1]),
                                  static_cast<float>(canvasSize / 2));
        } else {
            camera_->position.set(static_cast<float>(position[0]), static_cast<float>(canvasSize / 2),
                                  static_cast<float>(canvasSize / 2));
        }
    }
    std::vector<float> getCameraPosition() {
        return {static_cast<float>(camera_->position.x), static_cast<float>(camera_->position.y)};
    }
    float getCameraScale() {
        return camera_->scale.x;
    }
    threepp::OrthographicCamera &camera() const {
        return *camera_;
    }
    bool isInScene(auto object) {
        int inScene = false;
        for (const auto obj: objects) {
            if (obj == object) {
                inScene = true;
            }
        }
        return inScene;
    }
    void reset() {
        for (auto& object : objects) {
            remove(*object);
        }
        objects.clear();
    }
};


#endif //MOONLANDER_MOONSCENE_HPP
