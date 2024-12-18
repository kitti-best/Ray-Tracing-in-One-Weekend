#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    private:
        bool is_moving;
        vec3 origin_vec;
    public:
        vec3 origin1;
        vec3 origin2;
        double radius;
        shared_ptr<material> mat;
        sphere(vec3 _origin1, double _radius, shared_ptr<material> _mat) : origin1(_origin1), radius(_radius), mat(_mat), is_moving(false) {};
        sphere(vec3 _origin1, vec3 _origin2, double _radius, shared_ptr<material> _mat) : origin1(_origin1), origin2(_origin2), radius(_radius), mat(_mat), is_moving(true) {
            origin_vec = origin2 - origin1;
        };

        vec3 sphere_center(double time) const {
            return time >= 0 and time <= 1 ? origin1 + origin_vec * time : origin2;
        }

        bool hit(ray ray, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 origin = sphere_center(ray.get_time());
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
            rec.set_face_normal(ray, rec.p - origin1);
            rec.mat = mat;

            return true;
        }
};

#endif
