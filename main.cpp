
//Reworked from 'snake' example in "threepp"

#include "LunarLanderGame.hpp"

int main() {
    LunarLanderGame game;

    threepp::Canvas canvas("LunarLander");
    threepp::GLRenderer renderer(canvas.size());;
    canvas.addKeyListener(&game.getUI());
    threepp::Clock clock;
    canvas.animate([&]() {
        float dt = clock.getDelta();

        game.update(dt);
        renderer.render(game.getScene(), game.getCamera());
    });

}