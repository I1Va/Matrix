#pragma once

#include <random>
#include <vector>
#include <limits.h>

namespace test {

const int RAND_INT_MAX = INT_MAX / 2;
const int RAND_INT_MIN = INT_MIN / 2;

inline double randomDouble() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double randomInt(int min, int max) {
    return min + (int) ((max-min)*randomDouble());
}

inline double randomDouble(double min, double max) {
    return min + (max-min)*randomDouble();
}

} // namespace test
