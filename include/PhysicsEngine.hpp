#ifndef MOONLANDER_PHYSICSENGINE_HPP
#define MOONLANDER_PHYSICSENGINE_HPP

#include <vector>
#include <cmath>

class PhysicsEngine {
private:
    std::vector<float> movement = {0,0};
    std::vector<float> previousMovement = {0,0};
    std::vector<float> force = {0,0};
    std::vector<float> gVector = {0, -9.81};
public:
    void calculateForce(float rotation) {
        float speedConstant = 1;
        force = {speedConstant*cos(rotation), speedConstant*sin(rotation)};
    }
    std::vector<float> calculateNextMovement(float time) {
        movement = {previousMovement[0] + force[0] + gVector[0], previousMovement[1] + force[1] + gVector[1]};
        return movement;
    }
};

#endif //MOONLANDER_PHYSICSENGINE_HPP
