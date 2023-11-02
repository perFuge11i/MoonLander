//FOR MOON LANDER

//Utgangspunkt i snake eksempel fra threepp
#include "Spaceship.hpp"
#include "MoonScene.hpp"
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

/*
//FOR SNAKE
#include "SnakeScene.hpp"

int main() {

    SnakeGame game(10);

    Canvas canvas("Snake");
    GLRenderer renderer(canvas.size());

    auto scene = SnakeScene(game);
    canvas.addKeyListener(&scene);

    canvas.onWindowResize([&](WindowSize size) {
        scene.camera().updateProjectionMatrix();
        renderer.setSize(size);
    });

    renderer.enableTextRendering();
    renderer.textHandle("Press \"r\" to reset");

    Clock clock;
    canvas.animate([&]() {
        float dt = clock.getDelta();

        if (game.isRunning()) {

            game.update(dt);
            scene.update();

        }
        renderer.render(scene, scene.camera());
    });
}
*/