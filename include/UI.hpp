#ifndef MOONLANDER_UI_HPP
#define MOONLANDER_UI_HPP

#include "threepp/threepp.hpp"

//Based on threepp example "snake" and adapted for our use

class UI : public threepp::KeyListener {
private:
    std::vector<std::string> activeKeys;

public:
    void onKeyPressed(threepp::KeyEvent keyPress) override {

        switch (keyPress.key) {
            case threepp::Key::UP:
            case threepp::Key::W:
                activeKeys.push_back("UP");
                break;
            case threepp::Key::DOWN:
            case threepp::Key::S:
                activeKeys.push_back("DOWN");
                break;
            case threepp::Key::LEFT:
            case threepp::Key::A:
                activeKeys.push_back("LEFT");
                break;
            case threepp::Key::RIGHT:
            case threepp::Key::D:
                activeKeys.push_back("RIGHT");
                break;
        }
    }
    //Chat GPT
    std::vector<std::string> keySearcher() const {
        std::vector<std::string> foundKeys;
        for (const auto &key: activeKeys) {
            foundKeys.push_back(key);
        }
        return foundKeys;
    }
};
#endif//MOONLANDER_UI_HPP
