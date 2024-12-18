#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include "utils.h"

class vec3{
    public:
        double e[3];

        vec3() : e{0, 0, 0} {};
        vec3(double e0,double  e1,double  e2){e[0] = e0;e[1] = e1;e[2] = e2;}
        
        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        void operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
        }

        void operator-=(const vec3 &v){
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
        }

        void operator*=(double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
        }

        void operator/=(double t){
            e[0] /= t;
            e[1] /= t;
            e[2] /= t;
        }
        
        double length(){
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        bool near_zero() const {
            double epsilon = 1e-8;
            return (fabs(e[0]) < epsilon) && (fabs(e[1]) < epsilon) && (fabs(e[2]) < epsilon);
        }
};

inline vec3 operator+(const vec3 u, const vec3 v){
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
};

inline vec3 operator-(const vec3 u, const vec3 v){
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
};

inline vec3 operator*(const vec3 u, const double t){
    return vec3(u[0] * t, u[1] * t, u[2] * t);
};

inline vec3 operator*(const double t, const vec3 u){
    return vec3(u[0] * t, u[1] * t, u[2] * t);
};

inline vec3 operator*(const vec3 u, const vec3 v){
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
};

inline vec3 operator/(const vec3 u, const double t){
    return vec3(u[0] / t, u[1] / t, u[2] / t);
};

inline std::ostream& operator<<(std::ostream &cout, const vec3 &v) {
    return cout << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline double dot(const vec3 u,const vec3 v){
    double dp = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
    // std::cout << "DP = " << dp << "\n";
    return dp;
}

inline vec3 cross(const vec3 u,const vec3 v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(vec3 u){
    double length = u.length();
    return u / length;
}

inline vec3 random(){
    return vec3(random_double(), random_double(), random_double());
}

inline vec3 random(double min, double max){
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline vec3 random_unit_vector() {
    while (true) {
        vec3 p = random(-1,1);
        if (p.length_squared() < 1)
            return unit_vector(p);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return - on_unit_sphere;
}

inline vec3 find_reflected_dir(vec3 p_dir, vec3 normal){
    vec3 reflected = p_dir - normal * 2 * dot(p_dir, normal);
    return reflected;
}

inline vec3 find_refracted_ray(const vec3 u, const vec3 normal, double etai_over_etat){
    double cos_theta = min(dot(-u, normal), 1.0);
    vec3 r_perp = etai_over_etat * (u + cos_theta * normal);
    vec3 r_parr = - sqrt(fabs(1 - r_perp.length_squared())) * normal;
    return r_perp + r_parr;
}

#endif