#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <math.h>

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double min(auto a, auto b){
    return a < b ? a : b;
}

inline double deg2rad(double d){
    return d * M_PI / 180;
}

#endif