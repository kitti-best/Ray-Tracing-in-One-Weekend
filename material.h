#ifndef MATERIAL_H
#define MATERIAL_H

// #include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;

class hit_record;

class material{
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material{
    public:
        // rate of reflection (also attenuation means rate of light reduction)
        color albedo;
        lambertian(const color& a) : albedo(a) {};

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected_dir = rec.normal + random_unit_vector();
            if(reflected_dir.near_zero()) reflected_dir = rec.normal;
            scattered = ray(rec.p, reflected_dir);
            attenuation = albedo;
            return true;
        }
};

class metal : public material{
    public:
        // rate of reflection (also attenuation means rate of light reduction)
        color albedo;
        int fuzz;

        metal(const color& a) : albedo(a), fuzz(0) {};
        metal(const color& a, int _fuzz) : albedo(a), fuzz(fuzz < 1 ? fuzz : 1) {};

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected_dir = find_reflected_dir(unit_vector(r_in.direction), rec.normal);
            scattered = ray(rec.p, reflected_dir + random_unit_vector() * fuzz);
            attenuation = albedo;
            return (dot(scattered.direction, rec.normal) > 0);
        }
};

class dielectric : public material {
    public:
        double ir;
        dielectric(double index_of_refraction) : ir(index_of_refraction) {};

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            attenuation = color(vec3(1, 1, 1));
            double refraction_ratio = rec.front_face ? 1.0/ir : ir;

            vec3 unit_dir = unit_vector(r_in.direction);
            double cos_theta = min(dot(-unit_dir, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) 
            direction = find_reflected_dir(unit_dir, rec.normal);
            else direction = find_refracted_ray(unit_dir, rec.normal, refraction_ratio);

            scattered = ray(rec.p, direction);
            return true;
        }

        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};

#endif