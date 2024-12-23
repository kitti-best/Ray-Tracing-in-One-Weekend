#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list {
    public:
        // make object have type of shared_ptr that point to hittable
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {};
        hittable_list(shared_ptr<hittable> object) {add(object);};

        void clear() {objects.clear();};

        void add(shared_ptr<hittable> object){
            objects.push_back(object);
        };

        bool hit(ray r, double ray_tmin, double ray_tmax, hit_record& rec){
            hit_record temp_rec;
            bool hit_anything = false;
            double closest_so_far = ray_tmax;
            for(const auto& object : objects){
                // object here is a pointer so the syntax of calling it function is -> not .
                if(object->hit(r, ray_tmin, closest_so_far, temp_rec)){
                    rec = temp_rec;
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                }
            }
            return hit_anything;

        }
        
};

#endif
