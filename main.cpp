//Utgangspunkt i snake eksempel fra threepp
#include "LunarLanderGame.hpp"

int main() {
    threepp::Canvas canvas("MoonLander");
    threepp::GLRenderer renderer(canvas.size());
    LunarLanderGame game;

    threepp::Clock clock;
    canvas.animate([&]() {
        float dt = clock.getDelta();

        game.update(dt);
        renderer.render(game.getScene(), game.getCamera());
    });

}