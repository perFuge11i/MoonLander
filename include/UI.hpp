#ifndef MOONLANDER_UI_HPP
#define MOONLANDER_UI_HPP

class UI {
private:
public:
    void handleKeyPress(int key) {
        const float moveAmount = 1.0f;

        switch (key) {
            case Key::UP:
            case Key::W:
                rocketDirection_ = RocketDirection::UP;
                break;
            case Key::DOWN:
            case Key::S:
                rocketDirection_ = RocketDirection::DOWN;
                break;
            case Key::LEFT:
            case Key::A:
                rocketDirection_ = RocketDirection::LEFT;
                break;
            case Key::RIGHT:
            case Key::D:
                rocketDirection_ = RocketDirection::RIGHT;
                break;
            default:
                rocketDirection_ = RocketDirection::NONE;
                break;
        }
    }
};



#endif//MOONLANDER_UI_HPP
