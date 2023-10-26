#ifndef MOONLANDER_AABB_HPP
#define MOONLANDER_AABB_HPP

// Hele fra chatGPT utenom intersect
class AABB {
private:
    float x, y, width, height;
public:
    AABB(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0) {
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
