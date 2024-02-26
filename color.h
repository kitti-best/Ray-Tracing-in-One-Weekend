#ifndef COLOR_H
#define COLOR_H

class color{
    public:
        vec3 c;
        color(){};
        color(vec3 rgb) : c(rgb) {};
        double r(){return c[0];}
        double g(){return c[1];}
        double b(){return c[2];}
};

inline color operator+(color u, color v){
    return u.c + u.c;
};

inline color operator*(color c, const double t){
    return color(vec3(c.r() * t, c.g() * t, c.b() * t));
};

#endif