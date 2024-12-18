#include <iostream>
#include <cmath>


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
};

// clear
inline vec3 operator+(const vec3 u, const vec3 v){
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
};

inline vec3 operator-(const vec3 u, const vec3 v){
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
};

inline vec3 operator*(const vec3 u, const double t){
    return vec3(u[0] * t, u[1] * t, u[2] * t);
};

inline vec3 operator*(const vec3 u, const vec3 v){
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
};

inline vec3 operator/(const vec3 u, const double t){
    return vec3(u[0] / t, u[1] / t, u[2] / t);
};

class sphere{
    public:
        vec3 origin;
        double radius;
        sphere(vec3 o, double r) : origin(o), radius(r) {};

};

class ray{
    public:
        vec3 origin;
        vec3 direction;
        ray(vec3 o, vec3 dir) : origin(o), direction(dir) {};

        vec3 at_t(double t){ return origin + direction * t;};
};

class color{
    public:
        vec3 c;
        color(double r,double g,double b){c = vec3(r, g, b);}
        double r(){c[0];}
        double g(){c[1];}
        double b(){c[2];}
};

double dot(const vec3 u,const vec3 v){
    double dp = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
    std::cout << "DP = " << dp << "\n";
    return dp;
}

vec3 cross(const vec3 u,const vec3 v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

vec3 turn_to_unit(vec3 u){
    double length = u.length();
    u /= length;
}

inline std::ostream& operator<<(std::ostream &cout, const vec3 &v) {
    return cout << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

bool hit_sphere(ray ray, sphere sphere){
    vec3 oc = ray.origin - sphere.origin;
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, oc);
    double c = dot(oc, oc) - sphere.radius * sphere.radius;
    double ans = (b * b - 4 * a * c) >= 0;
    return ans;
}

bool hit_sphere2(const vec3 center, double radius, const ray r) {
    vec3 oc = r.origin - center;
    auto a = dot(r.direction, r.direction);
    auto b = 2.0 * dot(oc, r.direction);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    std::cout << "\n";
    return (discriminant >= 0);
}

int main(){
    vec3 u = vec3(1, 2, 5);
    vec3 v = vec3(2, 3, 4);

    std::cout << dot(u, v) << "\n";

    return 0;
}
