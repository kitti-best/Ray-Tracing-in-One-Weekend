#ifndef RAY_H
#define RAY_H

class ray{
    public:
        vec3 origin;
        vec3 direction;
        ray() {};
        ray(vec3 o, vec3 dir) : origin(o), direction(dir) {};
        vec3 at_t(double t){ return origin + direction * t;};
};  

#endif
