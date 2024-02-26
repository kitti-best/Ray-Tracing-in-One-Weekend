#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        vec3 origin;
        double radius;
        shared_ptr<material> mat;
        sphere(vec3 _origin, double _radius, shared_ptr<material> _mat) : origin(_origin), radius(_radius), mat(_mat) {};

        bool hit(ray ray, double ray_tmin, double ray_tmax, hit_record& rec) const override {
                vec3 oc = ray.origin - origin;
                double a = dot(ray.direction, ray.direction);
                double b = 2 * dot(ray.direction, oc);
                double half_b = dot(ray.direction, oc); // cuz there is 2 * infront;
                double c = dot(oc, oc) - radius * radius;
                // double discriminant = b * b - 4 * a * c;
                double discriminant = half_b * half_b - a * c;
                if(discriminant < 0) {
                    return false;
                };
                double t = (- half_b - sqrt(discriminant)) / a;
                // double t = (-b - sqrt(discriminant))/(2 * a);

                if(t <= ray_tmin || t >= ray_tmax) {
                    return false;
                };

                rec.t = t;
                rec.p = ray.at_t(t);
                rec.set_face_normal(ray, rec.p - origin);
                rec.mat = mat;

                return true;
        }
};

#endif
