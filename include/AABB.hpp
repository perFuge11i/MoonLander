#ifndef MOONLANDER_AABB_HPP
#define MOONLANDER_AABB_HPP

// Hele fra chatGPT(modifisert) utenom intersect
// AABB og intersect konsept fra video https://www.youtube.com/watch?v=oOEnWQZIePs

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

    bool intersects(const AABB &other) const {
        float right = x + width / 2;
        float rightOther = other.x + other.width / 2;
        float left = x - width / 2;
        float leftOther = other.x - other.width / 2;
        float bottom = y + height / 2;
        float bottomOther = other.y + other.height / 2;
        float top = y - height / 2;
        float topOther = other.y - other.height / 2;

        return (left < rightOther &&
                leftOther < right &&
                top < bottomOther &&
                topOther < bottom);
    }
};

#endif //MOONLANDER_AABB_HPP
