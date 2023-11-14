
//Utgangspunkt i "snake" eksempel fra "threepp"

#include "LunarLanderGame.hpp"
#include "UI.hpp"

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