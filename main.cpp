#include <iostream>
#include <fstream>
#include <cmath>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "camera.h"
#include "utils.h"
#include "material.h"

hittable_list generate_complicate_world(){
    hittable_list world;
    auto ground_material = make_shared<lambertian>(vec3(vec3(0.5, 0.5, 0.5)));
    world.add(make_shared<sphere>(vec3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0, b + 0.9*random_double());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material2 = make_shared<lambertian>(vec3(vec3(0.4, 0.2, 0.1)));
    world.add(make_shared<sphere>(vec3(-4, 0, 0), 1.0, material2));

    auto material3 = make_shared<metal>(vec3(vec3(0.7, 0.6, 0.5)), 0.0);
    world.add(make_shared<sphere>(vec3(4, 0, 0), 1.0, material3));
    
    return world;

}

int main(){
    // create world
    hittable_list world;

    // // create matterial
    // auto material_ground = make_shared<lambertian>(vec3(vec3(0.8, 0.8, 0.0)));
    // auto material_center = make_shared<lambertian>(vec3(vec3(0.1, 0.2, 0.5)));
    // auto material_left = make_shared<lambertian>(vec3(vec3(0.1, 0.2, 0.5)));
    // auto material_right  = make_shared<metal>(vec3(vec3(0.8, 0.6, 0.2)));

    // // add things to world
    // world.add(make_shared<sphere>(vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(make_shared<sphere>(vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.add(make_shared<sphere>(vec3(-1.2,    0.0, -1.0),   0.5, material_left));
    // world.add(make_shared<sphere>(vec3( 1.2,    0.0, -1.0),   0.5, material_right));


    auto ground_material = make_shared<lambertian>(vec3(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(vec3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            vec3 center2(center + vec3(0, random_double()/2, 0));

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_unit_vector() * random_unit_vector();
                    sphere_material = make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_unit_vector();
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                }
                if (random_double() < 0.7) world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
                else world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(vec3(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(vec3(4, 1, 0), 1.0, material3));

    camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.img_width       = 400;
    camera.sampling_number = 50;
    camera.max_depth         = 50;

    camera.vfov     = 20; 
    camera.lookfrom = vec3(13,2,3);
    camera.lookat   = vec3(0,0,0);
    camera.vup      = vec3(0,1,0);


    // cam.render(world, );

    /*
    // camera setup
    camera camera;
    camera.img_width = 400;
    camera.sampling_number = 10;
    camera.max_depth = 50;
    camera.aspect_ratio = 16.0/16.0;
    // camera.aspect_ratio = 1.0/1.0;


    camera.vfov     = 20;
    camera.lookfrom = vec3(-2,2,1);
    camera.lookat   = vec3(0,0,-1);
    camera.vup      = vec3(0,1,0);

    */
    std::ofstream image("image.ppm");
    camera.render(world, image);

    std::cout << "done!";
}
