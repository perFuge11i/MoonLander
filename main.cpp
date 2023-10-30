//FOR MOON LANDER
#include "Spaceship.hpp"
#include "MoonScene.hpp"

int main() {
    threepp::Canvas canvas("MoonLander");
    threepp::GLRenderer renderer(canvas.size());
    auto scene = MoonScene();

    canvas.animate([&]() {
        renderer.render(scene, scene.camera());
    });

    std::cout << "AB";
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