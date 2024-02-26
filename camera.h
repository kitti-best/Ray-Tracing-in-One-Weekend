#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include "utils.h"
#include "vec3.h"
#include "material.h"

class camera {
    private:
        int max_color = 255;
        int img_height;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        vec3 pixel00_loc;
        vec3 u, v, w;

    public:
        double aspect_ratio = 1.0/1.0;
        double vfov = 90;
        int img_width = 200;
        int sampling_number = 1;
        int max_depth = 1;
        vec3 center;
        vec3 lookfrom = vec3(0,0,-1);  // Point camera is looking from
        vec3 lookat   = vec3(0,0,0);   // Point camera is looking at
        vec3 vup      = vec3(0,1,0);     // Camera-relative "up" direction


    void initialize() {
        img_height = static_cast<int>(img_width / aspect_ratio);
        center = lookfrom;

        double focal_length = (lookfrom - lookat).length();
        
        double theta = deg2rad(vfov);
        double h = tan(theta/2) * focal_length;
        double viewport_height = 2.0 * h;
        auto viewport_width = viewport_height * static_cast<double>(img_width)/img_height;
        
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = unit_vector(cross(w, u));

        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        pixel_delta_u = viewport_u / img_width; // how much is one step to the right
        pixel_delta_v = viewport_v / img_height; // how much is one step up

        // std::cout << pixel_delta_u << "\n";
        // std::cout << pixel_delta_v << "\n";

        auto viewport_upper_left = center - focal_length * w - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
    }

    void render(hittable_list& world, std::ofstream& image) {
        initialize();
        image << "P3\n" << img_width << " " << img_height << "\n" << max_color << "\n";
        for(int y = 0; y < img_height;y++){
            std::cout << static_cast<double>(y)/img_height*100 << "%\n";
            for(int x = 0; x < img_width;x++){
                color pixel_color = color(vec3(0,0,0));
                for(int sample = 0; sample < sampling_number; sample ++){
                    ray ray = get_ray(x, y);
                    int reached_depth = 0;
                    int* reached_depth_ptr = &reached_depth;
                    pixel_color.c += ray_color(ray, world, max_depth, reached_depth_ptr);
                    // if(reached_depth != 1 and reached_depth != 50) std::cout << reached_depth << "\n";
                }
                write_image(pixel_color, image);
            }   
        }
    }

    ray get_ray(int x, int y) const {
        vec3 pixel_center = pixel00_loc + (pixel_delta_u * x) + (pixel_delta_v * y);
        vec3 pixel_sample = pixel_center + pixel_sampling();

        vec3 ray_dir = pixel_sample - center;

        ray ray(center, ray_dir);
        return ray;
    }

    vec3 pixel_sampling() const {
        double px = -0.5 + random_double();
        double py = -0.5 + random_double();

        return pixel_delta_u * px + pixel_delta_v * py;
    }

    vec3 ray_color(const ray& r, hittable_list& world, int depth, int * const &reached_depth){
        if(depth <= 0) return vec3(0, 0, 0);
        
        hit_record rec;
        *reached_depth += 1;
        if(world.hit(r, 0.01, INFINITY, rec) && depth > 0){
            ray reflected_ray;
            color reflected_color;
            if(rec.mat->scatter(r, rec, reflected_color, reflected_ray)){
                // std::cout << &reflected_color.c << " at : " << depth << "\n";
                return reflected_color.c * ray_color(reflected_ray, world, depth - 1, reached_depth);

                // // working diffusion start
                // vec3 reflected_dir = rec.normal + random_unit_vector();
                // // std::cout << reflected_dir << "\n";
                // ray reflected_ray = ray(rec.p, reflected_dir);
                // return 0.5 * ray_color(reflected_ray, world, depth-1);
                // // woring diffusion stop

            }
            return vec3(1, 1, 1);
            // return when_hit_sphere(rec);
        }

        vec3 unit_ray_dir = unit_vector(r.direction);
        double a = (unit_ray_dir[1] + 1.0) * 0.5;
        vec3 compo_a = vec3(1.0, 1.0, 1.0) * (1.0 - a);
        vec3 compo_b = vec3(0.5, 0.7, 1.0) * a;
        return compo_a + compo_b;
    }

    double linear_to_gamma(double linear_component){
        return sqrt(linear_component);
    }

    void write_image(color pixel_color, std::ofstream& image){
        pixel_color.c /= sampling_number;
        
        double r = pixel_color.r() * max_color;
        double g = pixel_color.g() * max_color;
        double b = pixel_color.b() * max_color;

        // r = linear_to_gamma(r);
        // g = linear_to_gamma(g);
        // b = linear_to_gamma(b);

        image << r << " " << g << " " << b << "\n";
    }

    vec3 gradient_ball(hit_record& rec){
        return (rec.normal + vec3(1, 1, 1)) * 255 * 0.5;
    }

};

#endif