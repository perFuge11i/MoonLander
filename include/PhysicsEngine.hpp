#ifndef MOONLANDER_PHYSICSENGINE_HPP
#define MOONLANDER_PHYSICSENGINE_HPP

// AABBcollision() konsept fra video https://www.youtube.com/watch?v=oOEnWQZIePs
// GJKcollision() konsept fra video https://www.youtube.com/watch?v=ajv46BSqcK4
// generateRandomNumber() fra chatGPT


#include "AABB.hpp"
#include "GJKcomputations.hpp"
#include <random>
#include <vector>

class PhysicsEngine {
private:
    std::vector<float> distanceToTravel = {0,0};
    std::vector<float> speed = {0,0};
    std::vector<float> initSpeed = {0,0};
    std::vector<float> force = {0,0};
    const std::vector<float> g = {0,-4};
    const float speedConstant = 0.2;
    GJKengine GJK;
public:
    PhysicsEngine(float initSpeedX, float initSpeedY) {
        this->initSpeed = {initSpeedX, initSpeedY};
        speed = initSpeed;
    }
    void calculateForce(float rotation) {
        force = {speedConstant*cos(rotation), speedConstant*sin(rotation)};
    }
    std::vector<float> calculateNextMovement(float time) {
        //Add vectors for speed force, and the gravitational pull
        speed = GJK.vectorAddition(GJK.vectorAddition(speed, force), GJK.scale(g, time));
        distanceToTravel = GJK.scale(speed,time);
        force = {0,0};
        return distanceToTravel;
    }
    void reset() {
        speed = initSpeed;
    }

    bool AABBcollision(auto &body1, auto &body2) {
        std::vector<float> edges1 = body1.collisionBox.getEdges();
        std::vector<float> edges2 = body2.collisionBox.getEdges();

        return (edges1[1] < edges2[0] &&
                edges2[1] < edges1[0] &&
                edges1[3] < edges2[2] &&
                edges2[3] < edges1[2]);
    }
    bool GJKcollision(auto &body1, auto &body2) {
        //Initial direction
        std::vector<float> direction = GJK.vector(body1.position, body2.position);
        //Finding first supportPoint
        auto supportPointBody1 = GJK.supportFunction(direction,
                                                     body1.getVertices(),
                                                     body1.position);
        auto oppositeDirection = GJK.oppositeVector(direction);
        auto supportPointBody2 = GJK.supportFunction(oppositeDirection,
                                                     body2.getVertices(),
                                                     body2.position);
        auto minkowskiSupportPointA = GJK.vectorSubtraction(supportPointBody1, supportPointBody2);
        //Determining direction of next supportPoint
        direction = GJK.vector(minkowskiSupportPointA, {0, 0});

        //Finding second supportPoint
        supportPointBody1 = GJK.supportFunction(direction,
                                                body1.getVertices(),
                                                body1.position);
        oppositeDirection = GJK.oppositeVector(direction);
        supportPointBody2 = GJK.supportFunction(oppositeDirection,
                                                body2.getVertices(),
                                                body2.position);
        auto minkowskiSupportPointB = GJK.vectorSubtraction(supportPointBody1, supportPointBody2);
        //Checking if point passed origo
        if (!GJK.passedOrigo(minkowskiSupportPointB, direction)) {
            return false;
        }

        //Determining direction of next supportPoint
        auto BA = GJK.vector(minkowskiSupportPointB, minkowskiSupportPointA);
        auto BO = GJK.vector(minkowskiSupportPointB, {0, 0});
        direction = GJK.crossProduct(GJK.crossProduct(BA, BO), BA);

        //Finding third supportPoint
        supportPointBody1 = GJK.supportFunction(direction,
                                                body1.getVertices(),
                                                body1.position);
        oppositeDirection = GJK.oppositeVector(direction);
        supportPointBody2 = GJK.supportFunction(oppositeDirection,
                                                body2.getVertices(),
                                                body2.position);
        auto minkowskiSupportPointC = GJK.vectorSubtraction(supportPointBody1, supportPointBody2);
        //Checking if point passed origo
        if (!GJK.passedOrigo(minkowskiSupportPointC, direction)) {
            return false;
        }

        bool bothPassed = false;
        while (!bothPassed) {
            bothPassed = true;
            //Checking if origo is contained in triangle ABC
            auto CA = GJK.vector(minkowskiSupportPointC, minkowskiSupportPointA);
            auto CB = GJK.vector(minkowskiSupportPointC, minkowskiSupportPointB);
            auto normalCB = GJK.crossProduct(GJK.crossProduct(CA, CB), CB);
            auto normalCA = GJK.crossProduct(GJK.crossProduct(CB, CA), CA);
            auto CO = GJK.vector(minkowskiSupportPointC, {0, 0});
            //Checking if origo is in sectorBC
            if (GJK.dotProduct(normalCB, CO) > 0) {
                bothPassed = false;
                //Update ABC points
                minkowskiSupportPointA = minkowskiSupportPointC;
                //Find new point C
                direction = normalCB;
                supportPointBody1 = GJK.supportFunction(direction,
                                                        body1.getVertices(),
                                                        body1.position);
                oppositeDirection = GJK.oppositeVector(direction);
                supportPointBody2 = GJK.supportFunction(oppositeDirection,
                                                        body2.getVertices(),
                                                        body2.position);
                minkowskiSupportPointC = GJK.vectorSubtraction(supportPointBody1, supportPointBody2);
            }

            //Checking if origo is in sectorAC
            if (GJK.dotProduct(normalCA, CO) > 0) {
                bothPassed = false;
                //Update ABC points
                minkowskiSupportPointB = minkowskiSupportPointC;
                //Find new point C
                direction = normalCA;
                supportPointBody1 = GJK.supportFunction(direction, body1.getVertices(),
                                                        body1.position);
                oppositeDirection = GJK.oppositeVector(direction);
                supportPointBody2 = GJK.supportFunction(oppositeDirection,
                                                        body2.getVertices(),
                                                        body2.position);
                minkowskiSupportPointC = GJK.vectorSubtraction(supportPointBody1, supportPointBody2);
            }
            //Check if any points overlap;
            if (minkowskiSupportPointC == minkowskiSupportPointB ||
                minkowskiSupportPointC == minkowskiSupportPointA) {
                return false;
            }
        }
        return true;
    }
    bool isSoftLanding(float angleOfShip, float angleOfSurface) {
        std::vector<float> speedLimit = {2, -4};
        float angleVarianceLimit = 0.2;
        //If speed and angle falls within limits and the line is flat, the landing is soft
        return (speed[0] < speedLimit[0] &&
                speed[1] > speedLimit[1] &&
                angleOfShip > M_PI_2-angleVarianceLimit &&
                angleOfShip < M_PI_2+angleVarianceLimit &&
                angleOfSurface == 0);
    }
};

#endif //MOONLANDER_PHYSICSENGINE_HPP
