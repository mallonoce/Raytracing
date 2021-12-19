#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <memory>

#include "header.h"
#include "ray.h"

class Material;

struct hit_record {
	point3 p = point3::Zero();
	vec3 normal = vec3::Zero();
	std::shared_ptr<Material> mat_ptr;
	double t = -1.0;
	bool front_face = true;

	inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
		front_face = r.direction().dot(outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable 
{
public:
	virtual bool hit(const Ray& ray, const double& t_min, const double& t_max, hit_record& rec) const = 0;
};

class hittable_list : hittable
{
public:
	hittable_list() {};
	hittable_list(std::shared_ptr<hittable> object) { add(object); };
	hittable_list(std::vector<std::shared_ptr<hittable>> objects) { _objects = objects; };

	void add(std::shared_ptr<hittable> object) { _objects.push_back(object); }
	void clear() { _objects.clear();};
	virtual bool hit(const Ray& ray, const double& t_min, const double& t_max, hit_record& rec) const;

private:
	std::vector<std::shared_ptr<hittable>> _objects;
};

class sphere : public hittable
{
public:
	sphere();
	sphere(const point3& center, double r, std::shared_ptr<Material> m) : _center(center), _r(r), _mat_ptr(m) {};
	virtual bool hit(const Ray& ray, const double& t_min, const double& t_max, hit_record& rec) const;

private:
	point3 _center;
	double _r;
	std::shared_ptr<Material> _mat_ptr;
};


// Implementatations

bool hittable_list::hit(const Ray& ray, const double& t_min, const double& t_max, hit_record& rec) const 
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : _objects) {
		if (object->hit(ray, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}


bool sphere::hit(const Ray& ray, const double& t_min, const double& t_max, hit_record& rec) const
{
	auto oc = ray.origin() - _center;
	auto a = ray.direction().dot(ray.direction());
	auto b_2 = ray.direction().dot(oc);
	auto c = oc.dot(oc) - _r * _r;
	
	// evaluate discriminant 
	auto discr = b_2 * b_2 - a * c;
	if (discr < 0) 
		return false;
	auto sqrtd = sqrt(discr);
	
	// Find the nearest root that lies in the acceptable range.
	double root = (-b_2 - sqrtd) / a;

	if (root < t_min || root > t_max)
	{
		// evaluate second solution 
		root = (-b_2 + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.p = ray.at(root);
	rec.set_face_normal(ray, (rec.p - _center) / _r);
	rec.mat_ptr = _mat_ptr;
	return true;
}




#endif // _HITTABLE_H_