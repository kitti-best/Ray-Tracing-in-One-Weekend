#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include <memory>
#include <vector>

using std::shared_ptr;

class material;

class hit_record {
    public:
        vec3 p;
        vec3 normal;
        double t;
        bool front_face;
        shared_ptr<material> mat;

        void set_face_normal(const ray& ray, vec3 outward_normal){
            front_face = dot(ray.direction, outward_normal) < 0;
            normal = front_face ? outward_normal : - outward_normal;
            normal = unit_vector(normal);
        }
};

class hittable
{
    public:
        virtual bool hit(ray r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
        ~hittable() = default;
};


#endif
