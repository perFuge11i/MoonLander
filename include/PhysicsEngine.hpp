#ifndef MOONLANDER_PHYSICSENGINE_HPP
#define MOONLANDER_PHYSICSENGINE_HPP

#include <vector>
#include <cmath>

class PhysicsEngine {
private:
    std::vector<float> distanceToTravel = {0,0};
    std::vector<float> speed = {0,0};
    std::vector<float> initSpeed = {0,0};
    std::vector<float> force = {0,0};
    const std::vector<float> g = {0,9.81};
    const float rocketSpeedConstant = 0.2;
public:
    PhysicsEngine(float initSpeedX, float initSpeedY) {
        this->initSpeed = {initSpeedX, initSpeedY};
        speed = initSpeed;
    }
    void calculateForce(float rotation) {
        force = {rocketSpeedConstant*sin(rotation), -rocketSpeedConstant*cos(rotation)};
    }
    std::vector<float> calculateNextMovement(float time) {
        speed = {speed[0] + force[0] + g[0]*time, speed[1] + force[1] + g[1]*time};
        distanceToTravel = {speed[0]*time, speed[1]*time};
        force = {0,0};
        return distanceToTravel;
    }

    void reset() {
        speed = initSpeed;
    }
};

#endif //MOONLANDER_PHYSICSENGINE_HPP
