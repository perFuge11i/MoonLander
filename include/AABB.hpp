#ifndef MOONLANDER_AABB_HPP
#define MOONLANDER_AABB_HPP

// Hele fra chatGPT(modifisert) utenom getEdges()

#include <iostream>

class AABB {
private:
    float x, y, width, height;
public:
    AABB(float x_ = 0, float y_ = 0, float width_ = 0, float height_ = 0) {
        this->x = x_;
        this->y = y_;
        this->width = width_;
        this->height = height_;
    }

    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }

    void setSize(float width, float height) {
        this->width = width;
        this->height = height;
    }

    std::vector<float> getEdges() const {
        float right = x + width / 2;
        float left = x - width / 2;
        float bottom = y + height / 2;
        float top = y - height / 2;

        return {right, left, bottom, top};
    }
};

#endif //MOONLANDER_AABB_HPP
