#ifndef MOONLANDER_AABB_HPP
#define MOONLANDER_AABB_HPP

#include <iostream>

// Hele fra chatGPT utenom intersect
// AABB og intersect konsept fra video https://www.youtube.com/watch?v=oOEnWQZIePs

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
        double right = x + width / 2;
        double rightOther = other.x + other.width / 2;
        double height = y + height / 2;
        double heightOther = other.y - other.height / 2;

        return (x < rightOther &&
                other.x < right &&
                y > heightOther &&
                other.y > height);
    }
};

#endif //MOONLANDER_AABB_HPP
