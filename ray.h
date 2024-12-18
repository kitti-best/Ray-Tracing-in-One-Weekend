#ifndef RAY_H
#define RAY_H

class ray{
    private:
        double tm;

    public:
        vec3 origin;
        vec3 direction;

        ray() {};
        ray(vec3 o, vec3 dir) : origin(o), direction(dir) {};
        ray(vec3 o, vec3 dir, double time) : origin(o), direction(dir), tm(time) {};
        vec3 at_t(double t){ return origin + direction * t;};
        double get_time(){return tm;};
};  

#endif
