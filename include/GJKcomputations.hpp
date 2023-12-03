#ifndef MOONLANDER_GJKCOMPUTATIONS_HPP
#define MOONLANDER_GJKCOMPUTATIONS_HPP

//Should be a lib not a class

#include <vector>

class GJKengine {
public:
    std::vector<float> vector(std::vector<float> p1, std::vector<float> p2) {
        return {p2[0]-p1[0], p2[1]-p1[1]};
    }
    std::vector<float> vectorAddition(std::vector<float> v1, std::vector<float> v2) {
        return {v1[0]+v2[0], v1[1]+v2[1]};
    }
    std::vector<float> vectorSubtraction(std::vector<float> v1, std::vector<float> v2) {
        return {v1[0]-v2[0], v1[1]-v2[1]};
    }
    std::vector<float> scale(std::vector<float> v1, float scalar) {
        return {v1[0]*scalar, v1[1]*scalar};
    }
    std::vector<float> oppositeVector(std::vector<float> vector) {
        std::vector<float> oppositeVector;

        for (const auto value: vector) {
            oppositeVector.push_back(-value);
        }

        return oppositeVector;
    }
    float dotProduct(std::vector<float> v1, std::vector<float> v2) {
        return v1[0]*v2[0]+v1[1]*v2[1];
    }
    std::vector<float> crossProduct(std::vector<float> v1, std::vector<float> v2) {
        while (v1.size() < 3) {
            v1.push_back(0);
        }
        while (v2.size() < 3) {
            v2.push_back(0);
        }

        return {v1[1]*v2[2] - v1[2]*v2[1],
                v1[2]*v2[0] - v1[0]*v2[2],
                v1[0]*v2[1] - v1[1]*v2[0]};
    }
    std::vector<float> supportFunction(std::vector<float> direction,
                                        std::vector<std::vector<float>> vertices,
                                        std::vector<float> center) {
        float biggestDotProduct = 0;
        std::vector<float> supportPoint = {0,0};
        for (const auto vertex: vertices) {
            std::vector<float> CV = GJKengine::vector(center, vertex);
            auto dotProduct = GJKengine::dotProduct(CV, direction);

            if (dotProduct > biggestDotProduct) {
                biggestDotProduct = dotProduct;
                supportPoint = vertex;
            }
        }
        return supportPoint;
    }
    bool passedOrigo(std::vector<float> point, std::vector<float> direction) {
        auto dotProduct = GJKengine::dotProduct(point, direction);
        if (dotProduct >= 0) {
            return true;
        }
        return false;
    }
};

#endif //MOONLANDER_GJKCOMPUTATIONS_HPP