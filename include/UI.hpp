#ifndef MOONLANDER_UI_HPP
#define MOONLANDER_UI_HPP

#include "threepp/threepp.hpp"
#include <string>

//Modified from 'snake' example in threepp

class UI : public threepp::KeyListener {
private:
    std::vector<std::string> commands;
public:
    void onKeyPressed(threepp::KeyEvent keyPress) override{
        switch (keyPress.key) {
            case threepp::Key::UP:
            case threepp::Key::W:
                commands.push_back("FORWARD");
                break;
            case threepp::Key::DOWN:
            case threepp::Key::S:
                commands.push_back("SPEEDUP");
                break;
            case threepp::Key::LEFT:
            case threepp::Key::A:
                commands.push_back("LEFT");
                break;
            case threepp::Key::RIGHT:
            case threepp::Key::D:
                commands.push_back("RIGHT");
                break;
            case threepp::Key::R:
                commands.push_back("RESET");
                break;
        }
    }
    void onKeyReleased(threepp::KeyEvent keyPress) override{
        commands.clear();
    }

    bool searchCommands(std::string command) const {
        for (const auto &element: commands) {
            if (element == command) {
                return true;
            }
        }
        return false;
    }

};
#endif//MOONLANDER_UI_HPP
