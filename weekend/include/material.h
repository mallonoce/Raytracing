#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <memory>

#include "header.h"
#include "ray.h"
#include "hittable.h"

class Material 
{
public:
	virtual bool scatter(const Ray& ray_in, const hit_record& rec, 
		color& attenuation, Ray& scattered) const = 0;

};

class Lambertian : public Material 
{
public: 
	Lambertian(const color& albedo) : _albedo(albedo) {}
	virtual bool scatter(const Ray& ray_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;
private:
	color _albedo;
};


class Metal : public Material {
public:
    Metal(const color& albedo) : _albedo(albedo) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;
private:
	color _albedo;

};

bool Lambertian::scatter(const Ray& ray_in, const hit_record& rec, color& attenuation, Ray& scattered) const 
{
	vec3 scatter_direction = rec.normal + random_unit_vector();
	if(scatter_direction.isZero(1e-8))
			scatter_direction = rec.normal;

	scattered = Ray(rec.p, scatter_direction);
	attenuation = _albedo;
	return true;
}

bool Metal::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
{
	vec3 reflected = reflect(r_in.direction().normalized(), rec.normal);
	scattered = Ray(rec.p, reflected);
	attenuation = _albedo;
	return (scattered.direction().dot(rec.normal) > 0);
}


#endif // _MATERIAL_H_